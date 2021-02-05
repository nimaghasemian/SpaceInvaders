#include "Bullet.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void Bullet::shoot(float startX, float startY) {
  m_InFlight = true;
  m_Position.x = startX;
  m_Position.y = startY;
  m_Sprite.setPosition(m_Position);
}
bool Bullet::isInFlight() { return m_InFlight; }
void Bullet::setType(Dropper type) {
  m_type = type;
  if (m_type == AMMO) {
    m_Sprite.setTexture(
        TextureHolder::GetTexture("resorces/graphics/ammo.png"));
    m_MovingUp = false;
    m_MovingDown = true;
    m_Speed = 100.0f;
  } else if (m_type == HEART) {
    m_Sprite.setTexture(
        TextureHolder::GetTexture("resorces/graphics/heart.png"));
    m_MovingUp = false;
    m_MovingDown = true;
    m_Speed = 100.0f;
  } else if (m_type == BULLET) {
    m_Sprite.setTexture(
        TextureHolder::GetTexture("resorces/graphics/shooter-bullet-3-8.png"));
    m_MovingUp = true;
    m_MovingDown = false;
  } else if (m_type == BOMB) {
    m_Sprite.setTexture(
        TextureHolder::GetTexture("resorces/graphics/bomb-20-37.png"));
    m_MovingDown = true;
    m_MovingUp = false;
    m_Speed = 200.0f;
  }
}
void Bullet::stop() {
  m_Sprite.setPosition(-2000, -2000);
  m_InFlight = false;
}
FloatRect Bullet::getPosition() { return m_Sprite.getGlobalBounds(); }
Sprite Bullet::getShape() { return m_Sprite; }

void Bullet::update(float time) {
  if (m_InFlight) {
    if (m_MovingUp) {
      m_Position.y -= time * m_Speed;
    } else if (m_MovingDown) {
      m_Position.y += m_Speed * time;
    }
  }

  m_Sprite.setPosition(m_Position);
}