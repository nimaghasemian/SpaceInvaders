#pragma once
#ifndef TEXTUE_HOLDER_H
#define TEXTURE_HOLDER_H
#include <SFML/Graphics.hpp>
#include <map>
using namespace sf;
using namespace std;

class TextureHolder {
private:
  // a map container from STL
  // holds ralated pairs of string and texture
  map<string, Texture> m_Texture;
  static TextureHolder *m_s_Instance;
  // points to the only object created from TextureHolder
public:
  TextureHolder();
  static Texture &GetTexture(string const &filename);
};

#endif