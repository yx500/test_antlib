#include "poligons.h"

#include <iostream>
#include <memory>
#include <ostream>
#include <utility>


//---------------------------------------------------------------------------
TSmartPoligon::TSmartPoligon(const fs::path& y) : Poligon(), ych(y)
{
}
//---------------------------------------------------------------------------
void TSmartPoligon::DrawBgiOn(void* , int s)
{
  try {
    //        WinBgiDC dc((TCanvas*)(Canvas), MyGDIPlusRegim);
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
bool TSmartPoligon::Open() {
  Close();
  MOD = RD;
  CurrentPicture = BG;
  CurrentStation = 0;

  try {
    if (Poligon::Open( ych.c_str() ) < 0)
      return false;
  } catch (const std::exception& e) {
    std::clog << "std::exception: " << e.what() << std::endl;
    return false;
  }
  _is_open = true;;
  return true;
}
//---------------------------------------------------------------------------
std::string TSmartPoligon::current_sta_id()
{
  std::string sta;
  Station *pStan = nullptr;
  if (this->CurrentPicture != BG)
    pStan = this->STB[this->CurrentStation];
  else
    pStan = this->ST[this->CurrentStation];

  if (pStan)
    sta = fs::path(pStan->filename).filename();
  return sta;
}
//---------------------------------------------------------------------------
void TSmartPoligon::Close()
{
  Poligon::Close();
  _is_open = false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TSmartPoligons::Close()
{
  for (auto & ych: ychs)
    ych.second.Close();
}

alib::string_list TSmartPoligons::keys()
{
  alib::string_list list;
  for (auto &ych: ychs)
    list.push_back(ych.first);
  return list;
}
//---------------------------------------------------------------------------
int TSmartPoligons::Open(const fs::path& dir){
  Close();
  path = dir;
  _open_ych_dir(dir);
  return size();
}
//---------------------------------------------------------------------------
void TSmartPoligons::_open_ych_dir(const fs::path& dir) {
  for (auto const& dir_entry : std::filesystem::directory_iterator{dir}) {
    if( dir_entry.is_regular_file() ){
      std::string ex = alib::to_lower( dir_entry.path().extension() );
      if ( ex == ".ych" || ex == ".yce" ){
        auto key = dir_entry.path().filename();
        ychs.emplace( std::make_pair( key, dir_entry.path() )  );
        std::cout << dir_entry << '\n';
      }
    }

  }
}
//---------------------------------------------------------------------------
TSmartPoligon* TSmartPoligons::Item(const std::string& key)
{
  auto iter = ychs.find(key);
  if(iter==ychs.end())
    return nullptr;

  if( !iter->second.is_open() ){
    if ( iter->second.Open() <= 0 ) {
      return nullptr;
    }
  }
  return & (iter->second);
}
//---------------------------------------------------------------------------

