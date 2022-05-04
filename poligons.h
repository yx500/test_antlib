#pragma once

#include <string>
#include <vector>
#include "Polig.h"
#include "Stan.h"




using  TName = std::string;
using  TPath = std::string;

//---------------------------------------------------------------------------
class TSmartPoligons;




class TSmartPoligon : public Poligon
{
  friend class TSmartPoligons;
  TSmartPoligons *Poligons;

public:
  int CurrentStation;
  int CurrentPicture;

  //    dtg::set_of_keys dtg_def;
  std::string      key_id;
  std::string      sta_id();

  TSmartPoligon();

  int Open(const char* i);
  void Close();

  void DrawBgiOn(void* Canvas, int x);
  const char* GetCanalNames();
};

//---------------------------------------------------------------------------
class TSmartPoligons
{
  friend class TSmartPoligon;

  std::vector<TSmartPoligon*> YCHS;

  int _open_ych_dir(const char* ini);

  std::string  IniName;
  std::vector<std::string> FNames;
  std::vector<std::string> FFiles;

public:
  TSmartPoligons() { Close(); }
  virtual ~TSmartPoligons() { Close(); }

  int Open(const char* i);
  int Open_v2(const char* i);
  void Close();

  int  size() { return FFiles.size(); }
  TSmartPoligon* Item(int y);

  const std::string& Name(int i){ return FNames.at(i); }
  const std::string& File(int i){ return FFiles.at(i); }
};








