#pragma once

#include "Polig.h"
#include "Stan.h"

#include <string>
#include <string_view>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


//---------------------------------------------------------------------------
class TSmartPoligon : public Poligon
{
  fs::path ych;
  bool _is_open = false;

public:
  int CurrentStation=0;
  int CurrentPicture=BG;

  //    dtg::set_of_keys dtg_def;
  std::string  current_sta_id();
  const fs::path& path() { return ych; }
  std::string key() { return ych.filename(); }

  TSmartPoligon(const fs::path& ych);

  bool Open();
  void Close();
  bool is_open() {return _is_open; }

  void DrawBgiOn(void*, int x);
};

//---------------------------------------------------------------------------
class TSmartPoligons
{
  std::map< std::string, TSmartPoligon > ychs;
  fs::path  path;

  void _open_ych_dir(const fs::path& dir);

public:
  TSmartPoligons() {}
  virtual ~TSmartPoligons() { Close(); }

  int Open(const fs::path& dir);
  void Close();

  int  size() { return ychs.size(); }
  alib::string_list  keys();
  TSmartPoligon* Item(const std::string& key);
};








