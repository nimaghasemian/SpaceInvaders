#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Bullet {
private:
  Vector2f m_Position;
  float m_Speed = 1000.0f;
  Sprite m_Sprite;
  bool m_MovingDown = false;
  bool m_MovingUp = false;
  bool m_InFlight = false;
  int m_type; // 1 is dropper 2 is shoot

public:
  void shoot(float startX, float startY);
  void setType(int type);
  bool isInFlight();
  FloatRect getPosition();
  Sprite getShape();
  void update(float timeAsSeconds);
  void stop();
};
