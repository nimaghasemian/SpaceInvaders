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

public:
  Enemy();
  bool movedDownOnce;
  void spawn(float startX, float startY);
  void moveDown();
  void stopDown();
  FloatRect getPosition();
  Sprite getShape();
  Vector2f getCenter();
  void changeDirection();
  void update(float timePassed);
  bool isAlive();
  bool hit();
};