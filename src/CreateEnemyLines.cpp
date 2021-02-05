#include "Enemy.h"
#include "SpaceInvaders.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Enemy* createEnemyLines() {
  Enemy* enemies = new Enemy[60];

  // setting enemies starting place
  float minX = 500;
  float minY = 150;
  int k = 0;
  for (int j = 0; j < 5; j++) {

    for (int i = 0; i < 12; i++) {
      enemies[k].spawn(minX + (i * 65), minY +(j * 45));

      k++;
    }
    if (k >= 60)
      break;
  }

  return enemies;
}