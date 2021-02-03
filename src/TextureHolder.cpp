#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder(){
    assert(m_s_Instance==nullptr);
    m_s_Instance = this;   
}

Texture& TextureHolder::GetTexture(string const& filename){
    auto& m = m_s_Instance->m_Texture;
    auto keyValuePair = m.find(filename);// auto is map<string,Texture>::iterator 
    if(keyValuePair != m.end()){
        return keyValuePair -> second;
    }else {
        Texture& texture = m[filename];
        texture.loadFromFile(filename);
        return texture;
    } 
    }

