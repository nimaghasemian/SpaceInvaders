#include "SpaceInvaders.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Shooter.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
using namespace sf;
enum class GameState { Playing, Paused, GameOver };
int main() {
  Clock clock;
  Time gameTime;
  GameState gameState = GameState::Paused;
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
// create a Text object called HUD
	Text hud;
	Font font;
	font.loadFromFile("fonts/The Led Display St.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20,20);
  Time dt;
  float moveDownTime;
  /*******creating shooter bullets*******/
  Bullet shooterBullets[100];
  for (int i = 0; i < 100; i++) {
    shooterBullets[i].setType(2);
  }
  int currentBullet = 0;
  int totallBullets = 100;
  int fireRate = 2;
  Time lastPressed;

  Bullet bomb;
  bomb.setType(1);
  bool godown = false;

  /*******MAIN GAME LOOP**********/
  while (window.isOpen()) {
    dt = clock.restart();
    gameTime += dt;
    /*
     *****************************
     * handle the Player input
     *****************************
     */
     Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Return && gameState == GameState::Playing) {
          gameState = GameState::Paused;
        } else if (event.key.code == Keyboard::Return &&
                   gameState == GameState::Paused) {
          gameState = GameState::Playing;
          clock.restart();
        }}}

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }
    
    if(gameState == GameState::Paused){

    }

    if (gameState == GameState::Playing) {

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
        if (gameTime.asMilliseconds() - lastPressed.asMilliseconds() >
            1000 / fireRate) {
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

      srand(time(0));
      int randomBomber = rand() % 60;
      if (enemies[randomBomber].isAlive() && !bomb.isInFlight())
        bomb.shoot(enemies[randomBomber].getCenter().x,
                   enemies[randomBomber].getCenter().y);
    }//PlayingState
    /*
     *****************************
     * updating the game
     *****************************
     */

if(gameState == GameState::Playing){
    float dtAsSeconds = dt.asSeconds();
    shooter.update(dt.asSeconds());

    for (int i = 0; i < 60; i++) {
      if (godown == true)
        enemies[i].moveDown();
      enemies[i].update(dtAsSeconds);
    }
    if (godown == false) {
      for (int i = 0; i < 60; i++) {
        if (enemies[i].getCenter().x + enemies[i].getPosition().width / 2 + 5 >
                1920 ||
            enemies[i].getPosition().left < 0) {
          godown = true;
          break;
        }
      }
    } else {
      godown = false;
    }

    // updating bullets in flight
    dtAsSeconds = dt.asSeconds();
    for (int i = 0; i < 100; i++) {
      shooterBullets[i].update(dtAsSeconds);
      for (int j = 0; j < 60; j++) {
        if (shooterBullets[i].getPosition().intersects(
                enemies[j].getPosition()) &&
            enemies[j].isAlive() && shooterBullets[i].isInFlight()) {
          enemies[j].hit();
          shooterBullets[i].stop();
        }
      }
    }

    // bombs

    bomb.update(dt.asSeconds());
    if (bomb.getPosition().top > 1080)
      bomb.stop();
    if (bomb.getPosition().intersects(shooter.getPosition())) {
      if (shooter.isAlive()) {
        shooter.hit();
        bomb.stop();
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
    if (bomb.isInFlight()) {
      window.draw(bomb.getShape());
    }
    window.draw(shooter.getShape());
    window.display();
  }
}