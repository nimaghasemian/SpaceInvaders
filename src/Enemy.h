#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy {
private:
  Vector2f m_Position;
  Sprite m_Sprite;
  float m_SpeedX;           // speed when goint Right or Left
  float m_SpeedY = 1000.0f; // speed when going down
  bool m_Alive = true;
  bool m_MovingHoriz;
  bool m_MovingDown;
  bool m_Exploding = false;
  Time m_ExplodingTime;
  Clock m_Clock;
  

public:
  Enemy();
  bool isAlive();
  bool hit();
  void spawn(float startX, float startY);
  void moveDown();
  void stopDown();
  FloatRect getPosition();
  Sprite getShape();
  Vector2f getCenter();
  void update(float timePassed);

};