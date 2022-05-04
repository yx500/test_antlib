#include "poligons.h"

#include <memory>
#include <ostream>
#include <utility>



//---------------------------------------------------------------------------
TSmartPoligon::TSmartPoligon()
        : Poligon(), Poligons(0)
{
    MOD = RD;
    CurrentPicture = BG;
    CurrentStation = 0;
    key_id = "none";
}
//---------------------------------------------------------------------------
void TSmartPoligon::DrawBgiOn(void* Canvas, int s)
{
    try {
        WinBgiDC dc((TCanvas*)(Canvas), MyGDIPlusRegim);

        ::CurrentPicture = this->CurrentPicture;
        ::CurrentStation = this->CurrentStation;

        if (this->CurrentPicture == BG) {

            if (s == -1) {
                this->Go();
                return;
            }

            if (s) {
                this->Clear();
                this->Show();
            } else {
                this->Clear();
                this->Go();
            }
        } else {
            Station *pStan = this->STB[this->CurrentStation];
            if (pStan == 0) return;

            if (s == -1) {
                pStan->Go();
                return;
            }

            if (s) {
                pStan->Clear();
                pStan->Show();
            } else {
                pStan->Clear();
                pStan->Go();
            }
        }

    }  catch (...)  {
      std::clog << "ERROR on TSmartPoligon::DrawBgiOn." << std::endl;
    }
}
//---------------------------------------------------------------------------
static TSmartPoligon *tmppol = 0;
static int _item_chanal_list(int type, const char* name, int WantNamber)
{
    tmppol->dtg_def.insert(make_pair(type, name));
    return 0;
}
int TSmartPoligon::Open(const char* fn)
{
    Close();
    CurrentUCH = 0;
    MOD = RD;
    String FP = ExtractFilePath(fn); // путь файла участка
    if (FP.IsEmpty()) {// для поддержки старых конфигов, где без пути файла
        FP = String("cfg\\") + FP;
    }
    strcpy(Sta_Dir, (FP + "..\\sta\\").c_str());

    int r = -1;
    try {
        r = Poligon::Open(fn);
        if (r < 0) return r;

        key_id = ChangeFileExt(ExtractFileName(fn), "").LowerCase().c_str();//todo: cp1251_to_lover
        //незабудем активировать приемные буфера каналов всех типов
        tmppol = this;
        for (int j = 0; j < this->Count(); j++) {
            this->Item(j)->for_each_chanel(_item_chanal_list);
        }
        tmppol = 0;
    } catch (const char* e) {
        clog << fn << " error: " << e << endl;
    } catch (...) {
        clog << fn << " error." << endl;
    }
    return r;
}
//---------------------------------------------------------------------------
string TSmartPoligon::sta_id()
{
    string sta;
    if (this->CurrentPicture != BG) {
        Station *pStan = this->STB[this->CurrentStation];
        if (pStan)
            sta = ChangeFileExt(ExtractFileName(pStan->filename), "").LowerCase().c_str();
    }
    return sta;
}
//---------------------------------------------------------------------------
void TSmartPoligon::Close()
{
    Poligon::Close();
    CurrentPicture = BG;
    CurrentStation = 0;
}
//---------------------------------------------------------------------------
const char* TSmartPoligon::GetCanalNames()
{
    static String cn;
    cn = "";
    auto_ptr<TStringList> sl(new TStringList());
    sl->Delimiter = ';';
    for (int i = 0; i < this->Count(); ++i) {
        for (int k = 0; k < ARRAYSIZE(this->Item(i)->ChanelNames); ++k)
            if (this->Item(i)->ChanelNames[k][0]) {
                String ss = String(this->Item(i)->ChanelNames[k]).Trim();
                if (sl->IndexOf(ss) < 0)
                    sl->Add(ss);
            }
    }

    cn = sl->DelimitedText;
    return cn.c_str();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TSmartPoligons::Close()
{
    for (int i = 0; i < YCHS.size(); ++i)  DEL_(YCHS[i]);
    YCHS.clear();
    FNames.clear();
    FFiles.clear();
}
//---------------------------------------------------------------------------
int TSmartPoligons::Open_v2(const char* ini)
{
    Close();
    IniName = ini;
    _open_db(ini);
    YCHS.resize(FFiles.size(), NULL);
    return FFiles.size();
}
//---------------------------------------------------------------------------
int TSmartPoligons::Open(const char* ini)
{
    Close();
    IniName = ini;
    _open_txt(ini);
    // пытаемся заполнить имя
    for (int i = 0; i < YCHS.size(); ++i) {
        if (String(Names(i)).IsEmpty()) {
            FNames[i] = ExtractFileName(FFiles[i].c_str()).c_str();
        }
    }
    return FFiles.size();
}
//---------------------------------------------------------------------------
int TSmartPoligons::_open_db(const char* dbname)
{
    StderrLog log;
    Database db(dbname, &log);
    Query q(db);

    q.get_result(
        "select count(*) "
        "from sqlite_master "
        "where name='ychdef';"
    );
    long count =   q.fetch_row() ?  q.getval() : 0;
    q.free_result();

    if (count == 0)
        cerr << "!!! Отсутствует таблица конфигурации ychdef." << endl;

    string d = IncludeTrailingBackslash(ExtractFileDir(IniName.c_str())).c_str();
    q.get_result("select ych, ext, name from ychdef;");
    clog << "Ychs: " << endl;
    while (q.fetch_row()) {
        string y = SqliteToLocal(q.getstr("ych"));
        string e = SqliteToLocal(q.getstr("ext"));
        string n = SqliteToLocal(q.getstr("name"));
        FFiles.push_back(trim(d + "cfg\\" + y + e).c_str());
        FNames.push_back(trim(n).c_str());
        clog << FFiles.back().c_str() << ";" << FNames.back().c_str() << endl;
    }
    q.free_result();

    return 1;
}
//---------------------------------------------------------------------------
int TSmartPoligons::_open_txt(const char* ini)
{
    string d = IncludeTrailingBackslash(ExtractFileDir(IniName.c_str())).c_str();
    ifstream inif(ini);
    const string STDSpliters("\t;,");
    int l = 0;
    while (inif.good()) {
        string line;
        ws(inif);
        getline(inif, line, '\n');
        l++;
        if (line.size() > 2 &&
                (line[0] == '/' && line[1] == '/')
           ) continue;

        stringvector wordsline;
        string_splitex(line, STDSpliters, wordsline);

        if (wordsline.size() > 0) {
            string ffile = trim(wordsline[0]);
            FFiles.push_back(d + "cfg\\" + ffile);
            FNames.push_back(wordsline.size() > 1 ? trim(wordsline[1]).c_str() : ffile.c_str());
        }
    }
    return 1;
}
//---------------------------------------------------------------------------
int TSmartPoligons::_open_ini(const char* ini)
{
    auto_ptr<TMemIniFile> pif(new TMemIniFile(IniName.c_str()));
    for (int i = 0; i < 255; i++) {
        String ych = "ych" + IntToStr(i);
        if (pif->SectionExists(ych)) {
            String f = pif->ReadString(ych, "file", "");
            if (f.IsEmpty()) continue;
            String n = pif->ReadString(ych, "name", "");
            FFiles.push_back(f.c_str());
            FNames.push_back(n.c_str());
        }
    }
    auto_ptr<TStringList> yl(new TStringList());
    pif->ReadSectionValues("PoligonList", yl.get());
    for (int i = 0; i < yl->Count; i++) {
        String f = yl->Names[i];
        String s = yl->Strings[i];
        if (f.IsEmpty()) continue;
        FFiles.push_back(f.c_str());
        FNames.push_back(yl->Values[yl->Names[i]].c_str());
    }
    return 1;
}
//---------------------------------------------------------------------------
TSmartPoligon* TSmartPoligons::Item(int y)
{
    if (YCHS.size() < FFiles.size())
        YCHS.resize(FFiles.size(), NULL);

    if (y >= YCHS.size() || y < 0) return &TSmartPoligon::Null;
    if (!YCHS[y]) {
        TSmartPoligon* P = new TSmartPoligon();
        CurrentUCH = y;
        String t = FFiles[y].c_str();
        String FP = ExtractFilePath(t.c_str());
        if (FP.IsEmpty()) {// для поддержки старых конфигов, где без пути файла
            t = String("cfg\\") + t;
        }
        if (P->Open(t.c_str()) <= 0) {
            ::MessageBox(NULL, (FFiles[y] + " - " + FNames[y]).c_str(), "Проблема загрузки участка.",
                         MB_OK);
            DEL_(P);
            YCHS[y] = &TSmartPoligon::Null;
            return YCHS[y];
        }

        if (P) {
            if (String(P->name).IsEmpty())
                strncpy(P->name, FNames[y].c_str(), sizeof(P->name) - 1);
            YCHS[y] = P;
            P->Clear();
        }
    }
    return YCHS[y];
}
//---------------------------------------------------------------------------

