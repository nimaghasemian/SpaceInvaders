#pragma once
#include "Dropper.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Bullet {
private:
  Vector2f m_Position;
  Sprite m_Sprite;
  float m_Speed = 1000.0f;
  bool m_MovingDown = false;
  bool m_MovingUp = false;
  bool m_InFlight = false;
  Dropper m_type; // 1 is bomb 2 is shoot 3 is heartDropper 4 is ammoDropper

public:
  void shoot(float startX, float startY);
  void setType(Dropper type);
  bool isInFlight();
  FloatRect getPosition();
  Sprite getShape();
  void update(float timeAsSeconds);
  void stop();
};
