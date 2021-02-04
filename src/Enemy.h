#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy
{
private:
    Vector2f m_Position;
    Sprite m_Sprite;
    float m_SpeedX= 200.0f; //speed when goint Right or Left
    float m_SpeedY= 1000.0f; //speed when going down
    bool m_Alive = true;
   static bool m_MovingHoriz;
   static bool m_MovingDown;
  
    
public:
    Enemy();
    void spawn(float startX, float startY);
    void moveDown(Time dt);
    void stopDown();
    FloatRect getPosition();
    Sprite getShape();
    void changeDirection();
    void update(Time dt);
    bool isAlive();
    bool hit();

};