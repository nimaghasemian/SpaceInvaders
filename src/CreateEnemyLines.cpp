#include "SpaceInvaders.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Enemy* createEnemyLines(float width){
    Enemy* enemies = new Enemy[60];

    float minX = 500;
    float maxX = width - 400;
    float minY = 150;
    float gap = minX;
    int k = 0;
for (int j  = 0; j < 5; j++)
    {
        gap = 0;
    for (int i = 0; i < 12; i++)        
        {
            enemies[k].spawn(minX +(i*65), minY + j*45);
            
            k++;
        }
                if(k >= 60)
                    break;
    }
    
    return enemies;

}