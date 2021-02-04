#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Bullet
{
private:
    Vector2f m_Position;
    float m_Speed;
    Sprite m_Sprite;
    bool m_MovingDown;
    bool m_MovingUp;
    bool inFlight;
    int m_type;//1 is dropper 2 is shhot
public:
    Bullet(string texture);
    void shoot(float startX, float startY,int type);
    bool isInFlight();
    FloatRect getPosition();
    Sprite getShape();
    void update(Time dt);
    
};

