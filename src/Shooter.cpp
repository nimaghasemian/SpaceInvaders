#include "Shooter.h"
#include "TextureHolder.h"
using namespace sf;

Shooter::Shooter(float startX, float startY) {
  m_Sprite.setTexture(
      TextureHolder::GetTexture("resorces/graphics/space-invaders(2).png"));
  m_Position.x = startX;
  m_Position.y = startY;
  m_Sprite.setOrigin(Vector2f(64, 64));
  m_Sprite.setPosition(m_Position);
}
void Shooter::spawn(float startX, float startY) {
  m_lives = 3;
  m_Sprite.setTexture(
      TextureHolder::GetTexture("resorces/graphics/space-invaders(2).png"));
  m_Position.x = startX;
  m_Position.y = startY;
  m_Sprite.setOrigin(Vector2f(64, 64));
  m_Sprite.setPosition(m_Position);
}
Vector2f Shooter::getCenter() { return m_Position; }
bool Shooter::hit() {
  m_lives--;
  return (m_lives > 0);
}
int Shooter::shootersLive() { return m_lives; }
void Shooter::moveLeft() { m_MovingLeft = true; }
void Shooter::moveRight() { m_MovingRight = true; }
void Shooter::stopLeft() { m_MovingLeft = false; }
void Shooter::stopRight() { m_MovingRight = false; }
FloatRect Shooter ::getPosition() { return m_Sprite.getGlobalBounds(); }
Sprite Shooter ::getShape() { return m_Sprite; }
bool Shooter::isAlive() {
  if (m_lives > 0) {
    return true;
  } else {
    return false;
  }
}
void Shooter ::update(float dt) {
  if (isAlive()) {
    if (m_MovingRight) {
      m_Position.x += dt * m_Speed;
    }
    if (m_MovingLeft) {
      m_Position.x -= dt * m_Speed;
    }
    if (m_Position.x - m_Sprite.getGlobalBounds().width / 2 < 0) {
      m_Position.x = 0 + m_Sprite.getGlobalBounds().width / 2;
    }
    if (m_Position.x + m_Sprite.getGlobalBounds().width / 2 > 1920) {
      m_Position.x = 1920 - m_Sprite.getGlobalBounds().width / 2;
    }
  } else {
    m_Sprite.setTexture(
        TextureHolder::GetTexture("resorces/graphics/burningShooter.png"));
  }

  m_Sprite.setPosition(m_Position);
}
