#include "Enemy.h"
#include "TextureHolder.h"
using namespace sf;

Enemy::Enemy() {
  m_MovingDown = false;
  m_MovingHoriz = true;
  m_SpeedX = 200.0f;
}

void Enemy::spawn(float startX, float startY) {
  m_Position.x = startX;
  m_Position.y = startY;
  m_Sprite.setTexture(
      TextureHolder::GetTexture("resorces/graphics/enemy40-30.png"));

  m_Sprite.setOrigin(Vector2f(20, 15));
  m_Sprite.setPosition(m_Position);
}
void Enemy::moveDown() {

  m_MovingDown = true;
  m_MovingHoriz = false;
}
void Enemy ::stopDown() {
  if (m_MovingDown) {
    m_MovingDown = false;
    m_MovingHoriz = true;
    m_SpeedX *= -1;
  }
}
FloatRect Enemy ::getPosition() { return m_Sprite.getGlobalBounds(); }
Sprite Enemy ::getShape() { return m_Sprite; }
bool Enemy ::isAlive() { return m_Alive; }
bool Enemy ::hit() {
  if (m_Alive) {
    m_Alive = false;
    m_Sprite.setTexture(
        TextureHolder::GetTexture("resorces/graphics/explosion-40-30.png"));
  }
  return m_Alive;
}

void Enemy::changeDirection() { m_SpeedX *= -1; }
Vector2f Enemy::getCenter() { return m_Position; }
void Enemy ::update(float timePassed) {

  if (m_Alive) {
    if (m_MovingHoriz) {
      m_Position.x += timePassed * m_SpeedX;
    }

    else if (m_MovingDown) {
      m_Position.y += 10;
      m_MovingDown = false;
      m_MovingHoriz = true;
      m_SpeedX *= -1;
    }
  }

  m_Sprite.setPosition(m_Position);
}