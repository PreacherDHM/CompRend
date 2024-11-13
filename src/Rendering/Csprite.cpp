#include "Csprite.h"
#include <wchar.h>
#include <Entity.h>
#include <cstring>
#include <filesystem>
#include <sstream>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <lua.hpp>
#include <string>
#include <io.h>
#include <fcntl.h>

csprite sprite_create() {
  csprite s;
  s.bounds.x = 0;
  s.bounds.y = 0;
  s.position.x = 0;
  s.position.y = 0;
  //s.data[] = L"hii there";
  s.data_size = s.bounds.x * s.bounds.y;
  //s.shader = L"ni";
  return s;
}

csprite sprite_create(int boundsX, int boundsY, const char *data) {
  csprite s;
  s.bounds.x = boundsX;
  s.bounds.y = boundsY;
  s.bounds.x = 0;
  s.bounds.y = 0;
  s.position.x = 0;
  s.position.y = 0;
  mbstowcs(s.data, data, strlen(data));
  s.data_size = s.bounds.x * s.bounds.y;
  //s.shader = L"ni";
  return csprite();
}

csprite sprite_create(int boundsX, int boundsY, int positionX, int positionY,
                      const char *data) {
  csprite s;
  s.bounds.x = boundsX;
  s.bounds.y = boundsY;
  s.bounds.x = 0;
  s.bounds.y = 0;
  s.position.x = positionX;
  s.position.y = positionY;
  mbstowcs(s.data, data, strlen(data));
  s.data_size = s.bounds.x * s.bounds.y;
  //s.shader = L"ni";
  return csprite();
}

int lua_csprite_create(lua_State *L) {
  csprite *cs = (csprite *)lua_newuserdata(L, sizeof(csprite));
  lua_gettable(L, -1);
  lua_pushstring(L, "data");
  lua_gettable(L, -2);
  if (lua_istable(L, -1)) {
    int data_size = lua_rawlen(L, -1);
    for (int i = 1; i <= data_size; i++) {
      lua_pushnumber(L, 1);
      lua_gettable(L, -2);

      lua_pushstring(L, "id");
      lua_gettable(L, -1);
      if (lua_isnumber(L, -1)) {
      }
    }
  }
  return 0;
}

int lua_csprite_get_from_file(lua_State *L) {
  std::string cpath = "";

  if (!lua_isuserdata(L, -2)) {
    lua_pushstring(L, "not a userdata");
    lua_error(L);
    return 0;
  }
  entity *e = (entity *)lua_touserdata(L, -2);

  if (!lua_isstring(L, -1)) {
    lua_pushstring(L, "not a string");
    lua_error(L);
    return 0;
  }
  cpath = lua_tostring(L, -1);

  std::filesystem::path path(cpath);
  path = std::filesystem::path(std::filesystem::current_path() / path);
  std::cout << "\ncpath" << cpath << "\n path" << path;
  int width = 0;
  int height = 0;
  int line_number = 0;
  std::wstring data;
  std::wstring csprite;
  std::wstring shader;
  if (std::filesystem::exists(path)) {
    std::wifstream f(path);
//      f.imbue(
//        std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
      std::wstringstream data_stream;
      data_stream << f.rdbuf();
      data = data_stream.str();
      f.close();
      int end_of_shader = data.find_first_of(L'\n');
	  std::wcout << L"\ndata: " << data << L"\n";
      int end_of_data = data.length();
	  for (int i = end_of_shader; i < data.length(); i++) {
		  if (data.at(i) == L'\n') {
			data.erase(i, 1);
            height++;
            i = end_of_shader;
		  }
	  }
      height--;
      width = (data.length())/height;



      e->sprite.shader = new wchar_t[end_of_shader + 1];
      for (int i = 0; i < end_of_shader; i++) {
          e->sprite.shader[i] = data.at(i);
      }
      e->sprite.shader[end_of_shader] = L'\0';
      e->sprite.data = new wchar_t[data.length() - end_of_shader + 1];
      for (int i = 0; i < data.length() - end_of_shader; i++) {
          e->sprite.data[i] = data.at(i + end_of_shader);
      }
      e->sprite.data[data.length() - end_of_shader] = L'\0';
      e->sprite.bounds.x = width;
      e->sprite.bounds.y = height;


      std::wcout << "\npath :" << path << L"\nEnd of Shader :" << end_of_shader << L"\nShader :" << e->sprite.shader << L"\nsprite |" << e->sprite.data << "|\nwidth and height :" << width << ';' << height << '\n';
	return 0;
    }
  lua_pushstring(L, "Not a valid path");
  lua_error(L);
    return 0;
  }

void csprite_init_lua(lua_State *L) {
  lua_getglobal(L, "CompRend");
  lua_pushstring(L, "CSprite");
  lua_newtable(L);

  lua_pushstring(L, "Get");
  lua_pushcfunction(L, lua_csprite_get_from_file);
  lua_settable(L, -3);

  lua_settable(L, -3);
  lua_pop(L, 1);
}
