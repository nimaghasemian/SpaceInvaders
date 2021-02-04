#include "SpaceInvaders.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Shooter.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main() {
  Clock clock;
  Time gameTime;
  TextureHolder holder;
  VideoMode vm(1920, 1080);
  RenderWindow window(vm, "Space Invader", Style::Fullscreen);
  Sprite background;
  background.setTexture(
      TextureHolder::GetTexture("resorces/graphics/backgroud.jpg"));
  /******Creating the Shooter*******/
  Shooter shooter(1920 / 2, 1080 - 130);

  /******Creating enemys**********/
  Enemy *enemies = nullptr;
  enemies = createEnemyLines(1920.0f);
  
  Time dt;
  float moveDownTime;
  /*******creating shooter bullets*******/
  Bullet shooterBullets[100];
  for(int i = 0; i < 100 ;i++){
    shooterBullets[i].setType(2);
  }
  int currentBullet = 0;
  int totallBullets = 100;
  int fireRate = 2;
  Time lastPressed;

bool godown;
  /*******MAIN GAME LOOP**********/
  while (window.isOpen()) {
        dt = clock.restart();
    gameTime+= dt;
    /*
     *****************************
     * handle the Player input
     *****************************
     */
    

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
      shooter.moveLeft();
    } else {
      shooter.stopLeft();
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
      shooter.moveRight();
    } else {
      shooter.stopRight();
    }
    // handle bullets for shooter
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
      if (gameTime.asMilliseconds() - lastPressed.asMilliseconds() > 1000/fireRate) {
        shooterBullets[currentBullet].shoot(shooter.getCenter().x,
                                            shooter.getCenter().y);
        currentBullet++;
        totallBullets--;
        if (currentBullet > 99) {
          currentBullet = 0;
        }

        lastPressed = gameTime;
      }
    }

    /*
     *****************************
     * updating the game
     *****************************
     */
    
    float dtAsSeconds = dt.asSeconds();
    shooter.update(dt);
    if (godown)
      Enemy::moveDown();
    else
    {
      Enemy::stopDown();
    }
    
    for (int i = 0; i < 60; i++) {
      enemies[i].update(dtAsSeconds);
    }
      
      
    if(godown == false){
    for (int i = 0; i < 60; i++) {
      if (enemies[i].getPosition().left + 100 > 1920 ||
          enemies[i].getPosition().left - 50 < 0) {
            godown = true;
      }
      }
    }else
    {
      godown = false;
    }
    
    // updating bullets in flight
    for (int i = 0; i < 100; i++) {
        shooterBullets[i].update(dtAsSeconds);
        for(int j = 0 ; j < 60 ;j++){
          if (shooterBullets[i].getPosition().intersects(enemies[j].getPosition()) && enemies[j].isAlive() && shooterBullets[i].isInFlight()){
                enemies[j].hit();
                shooterBullets[i].stop();
          }
        }
      }
   

     
   
   
    /*
     *****************************
     * drawing the Game
     *****************************
     */

    window.clear();
    window.draw(background);
    for (int i = 0; i < 60; i++) {
      window.draw(enemies[i].getShape());
    }
    for (int i = 0; i < 100; i++) {
      if (shooterBullets[i].isInFlight()) {
        window.draw(shooterBullets[i].getShape());
      }
    }

    window.draw(shooter.getShape());
    window.display();
  }
}