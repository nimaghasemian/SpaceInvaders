#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Shooter {
private:
  Vector2f m_Position;
  Sprite m_Sprite;
  float m_Speed = 600.0f;
  bool m_MovingRight;
  bool m_MovingLeft;
  int m_lives = 3;

public:
  Shooter(float startX, float startY);
  void spawn(float startX, float startY);
  void moveLeft();
  Vector2f getCenter();
  void moveRight();
  void stopLeft();
  void stopRight();
  bool isAlive();
  void increaseHealth();
  void hit();
  int shootersLive();
  FloatRect getPosition();
  Sprite getShape();
  void update(float dt);
};