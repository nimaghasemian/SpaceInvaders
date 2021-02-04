#include "Enemy.h"
#include "TextureHolder.h"
using namespace sf;

bool Enemy::m_MovingDown = false;
bool Enemy::m_MovingHoriz = true;


Enemy::Enemy(){
    m_MovingDown = false;
    m_MovingHoriz = true;
}

void Enemy::spawn(float startX, float startY) {
  m_Position.x = startX;
  m_Position.y = startY;
  m_Sprite.setTexture(
      TextureHolder::GetTexture("resorces/graphics/enemy40-30.png"));
  
  m_Sprite.setOrigin(Vector2f(20, 15));
  m_Sprite.setPosition(m_Position);
}
void Enemy::moveDown(Time dt) {
  m_Position.y += dt.asSeconds() * m_SpeedY;
  m_SpeedX *= -1;
  }
void Enemy ::stopDown() { m_MovingDown = false; }
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

void Enemy::changeDirection(){m_SpeedX *= -1;}

void Enemy ::update(Time dt) {

if(m_Alive){
  if (Enemy::m_MovingHoriz) {
    m_Position.x += dt.asSeconds() * m_SpeedX;
  }
 
  else if (m_MovingDown) {
    
    m_Position.y += dt.asSeconds() * m_SpeedY;
    
  }
}
  m_Sprite.setPosition(m_Position);
}