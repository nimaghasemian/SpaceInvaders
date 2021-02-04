#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "TextureHolder.h"
using namespace sf;
 

void Bullet::shoot(float startX,float startY){
        m_InFlight = true;
        m_Position.x = startX;
        m_Position.y = startY;
        m_Sprite.setPosition(m_Position);
}
bool Bullet::isInFlight(){
    return m_InFlight;
}
void Bullet::setType(int type){
    m_type = type;
    if (m_type == 2){
            m_Sprite.setTexture(TextureHolder::GetTexture("resorces/graphics/shooter-bullet-3-8.png"));
            m_MovingUp = true;
    }else if (m_type == 1){
            m_Sprite.setTexture(TextureHolder::GetTexture(""));
    }
}
void Bullet::stop(){
    m_InFlight = false;
    m_Sprite.setPosition(Vector2f(2000,2000));
}
FloatRect Bullet::getPosition(){
    return m_Sprite.getGlobalBounds();
}

Sprite Bullet::getShape(){
    return m_Sprite;
}
void Bullet::update(float time){
    if (m_InFlight)
    {
        if (m_MovingUp)
        {
            m_Position.y -= time * m_Speed;
        }
        if (m_MovingDown)
        {
            m_Position.y += time*m_Speed;
        }        
    }
    
        m_Sprite.setPosition(m_Position);
}