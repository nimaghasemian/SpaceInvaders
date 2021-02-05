#include "SpaceInvaders.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Shooter.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace sf;

enum class GameState { Playing, Paused, GameOver, Starting };

int main() {
  Clock clock;
  Time gameTime;
  GameState gameState = GameState::Starting;
  TextureHolder holder;

  VideoMode vm(1920, 1080);
  RenderWindow window(vm, "Space Invader", Style::Fullscreen);
  Sprite background;
  background.setTexture(
      TextureHolder::GetTexture("resorces/graphics/backgroud.jpg"));

  /******Creating the Shooter*******/

  Shooter shooter(1920 / 2, 1080 - 100);

  /******Creating enemys**********/

  Enemy *enemies = nullptr;
  enemies = createEnemyLines(1920.0f);

  // create a Text object called HUD

  Text hud;
  Font font;
  Font digitalFont;
  font.loadFromFile("fonts/The Led Display St.ttf");
  digitalFont.loadFromFile("fonts/digital-7 (mono).ttf");
  hud.setFont(digitalFont);
  hud.setCharacterSize(50);
  hud.setFillColor(Color::Yellow);
  hud.setPosition(20, 20);

  // setting GAMEOVER text

  Text gameoverText;
  gameoverText.setFont(font);
  gameoverText.setCharacterSize(70);
  gameoverText.setFillColor(Color::Magenta);
  gameoverText.setString("Press Enter to Start the Game");
  FloatRect textRect = gameoverText.getLocalBounds();
  gameoverText.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top + textRect.height / 2.0f);
  gameoverText.setPosition(1920 / 2.0f, 1080 / 2.0f);
  Time dt;
  float moveDownTime;

  /*******creating shooter bullets*******/

  Bullet shooterBullets[100];
  for (int i = 0; i < 100; i++) {
    shooterBullets[i].setType(2);
  }
  int currentBullet = 0;
  int totallBullets = 200;
  int fireRate = 3;
  Time lastPressed;
  //enemy bomb
  Bullet bomb;
  bomb.setType(1);
  
  //*****************Adding sounds***********************
  SoundBuffer shooterDeathBuffer;
shooterDeathBuffer.loadFromFile("sound/shooter_death.wav");
Sound shooterDeathSound;
shooterDeathSound.setBuffer(shooterDeathBuffer);

SoundBuffer enemyDeathBuffer;
enemyDeathBuffer.loadFromFile("sound/invader_death.wav");
Sound enemyDeathSound;
enemyDeathSound.setBuffer(enemyDeathBuffer);

SoundBuffer shootBuffer;
shootBuffer.loadFromFile("sound/shoot_laser.wav");
Sound shootSound;
shootSound.setBuffer(shootBuffer);

SoundBuffer startBuffer;
startBuffer.loadFromFile("sound/start.wav");
Sound startSound;
startSound.setBuffer(startBuffer);
  //bunch of control variables
  
  int livingEnemies = 60;
  bool godown = false;    
  Time roundTime;
  float highScore = 0;

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
        if (event.key.code == Keyboard::Return &&
            gameState == GameState::Playing) {
          gameoverText.setString("Paused!");
          FloatRect textRect = gameoverText.getLocalBounds();
          gameoverText.setOrigin(textRect.left + textRect.width / 2.0f,
                                 textRect.top + textRect.height / 2.0f);
          gameoverText.setPosition(1920 / 2.0f, 1080 / 2.0f);
          gameState = GameState::Paused;
        } else if (event.key.code == Keyboard::Return &&
                   gameState == GameState::Paused) {
          gameState = GameState::Playing;
          clock.restart();
        } else if (event.key.code == Keyboard::Return &&
                   gameState == GameState::Starting) {
          roundTime = clock.restart();
          gameState = GameState::Playing;
          startSound.play();
        }
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }
    /**************restarting the Game***************/

    if (gameState == GameState::GameOver) {
      if (event.key.code == Keyboard::R) {
        gameState = GameState::Playing;
        startSound.play();
      }
      if (gameState == GameState::Playing) {
        shooter.spawn(1920 / 2, 1080 - 100);
        delete[] enemies;
        for (int i = 0; i < 100; i++) {
          shooterBullets[i].stop();
        }
        bomb.stop();
        livingEnemies = 60;
        totallBullets = 200;
        enemies = createEnemyLines(1920.0f);
        roundTime = clock.restart();
      }
    }

    if (gameState == GameState::Playing) {
      roundTime += dt;
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
      //***************************** handle bullets for shooter
      if (Keyboard::isKeyPressed(Keyboard::Space)) {
        if (totallBullets > 0) {
          if (gameTime.asMilliseconds() - lastPressed.asMilliseconds() >
              1000 / fireRate) {
            shooterBullets[currentBullet].shoot(shooter.getCenter().x,
                                                shooter.getCenter().y);
            currentBullet++;
            totallBullets--;
            shootSound.play();
            if (currentBullet > 99) {
              currentBullet = 0;
            }

            lastPressed = gameTime;
          }
        } else {
          gameState = GameState::GameOver;
          gameoverText.setCharacterSize(100);
          gameoverText.setFillColor(Color::Red);
          gameoverText.setString("Out of Ammo nigga");
          FloatRect textRect = gameoverText.getLocalBounds();
          gameoverText.setOrigin(textRect.left + textRect.width / 2.0f,
                                 textRect.top + textRect.height / 2.0f);
          gameoverText.setPosition(1920 / 2.0f, 1080 / 2.0f);
        }
      }

      srand(time(0));
      int randomBomber = rand() % 60;
      if (enemies[randomBomber].isAlive() && !bomb.isInFlight())
        bomb.shoot(enemies[randomBomber].getCenter().x,
                   enemies[randomBomber].getCenter().y);
    } // PlayingState
    /*
     *****************************
     * updating the game
     *****************************
     */
    float dtAsSeconds = dt.asSeconds();
    shooter.update(dt.asSeconds());
    if (gameState == GameState::Playing) {

      for (int i = 0; i < 60; i++) {
        if (godown == true)
          enemies[i].moveDown();
        
        enemies[i].update(dtAsSeconds);
      }
      if (godown == false) {
        for (int i = 0; i < 60; i++) {
          if (enemies[i].getCenter().x + enemies[i].getPosition().width / 2 +
                      5 >
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
          /**********************checking enemies collision with shooter*******/
          if (shooter.getPosition().top < enemies[j].getPosition().top + enemies[j].getPosition().height) {
            gameState = GameState ::GameOver;
            gameoverText.setFillColor(Color::Red);
            gameoverText.setString("GAME OVER!");
            shooterDeathSound.play();
            FloatRect textRect = gameoverText.getLocalBounds();
            gameoverText.setOrigin(textRect.left + textRect.width / 2.0f,
                                   textRect.top + textRect.height / 2.0f);
            gameoverText.setPosition(1920 / 2.0f, 1080 / 2.0f);
          }

          /*********************** Checking for enemy Hit *******************/
          if (shooterBullets[i].getPosition().intersects(
                  enemies[j].getPosition()) &&
              enemies[j].isAlive() && shooterBullets[i].isInFlight()) {
            enemies[j].hit();
            enemyDeathSound.play();
            livingEnemies--;
            shooterBullets[i].stop();
          }
        }
      }
      if (livingEnemies == 0) {
        gameState = GameState::GameOver;
        float score = roundTime.asSeconds()/10;
        if ( score < highScore)
          highScore = score;
        else if(highScore == 0)
          highScore = score;
        gameoverText.setFont(digitalFont);
        gameoverText.setCharacterSize(150);
        gameoverText.setFillColor(Color::Green);
        gameoverText.setString("You Win Nigga :) ");
        FloatRect textRect = gameoverText.getLocalBounds();
        gameoverText.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top + textRect.height / 2.0f);
        gameoverText.setPosition(1920 / 2.0f, 1080 / 2.0f);
      }

      // bombs

      bomb.update(dt.asSeconds());
      if (bomb.getPosition().top > 1080)
        bomb.stop();
      if (bomb.getPosition().intersects(shooter.getPosition())) {
        if (shooter.isAlive() && bomb.isInFlight()) {
          shooter.hit();
          bomb.stop();
        }
        if (!shooter.isAlive()) {
          gameoverText.setFillColor(Color::Red);
          gameoverText.setString("GAME OVER!");
          shooterDeathSound.play();
          FloatRect textRect = gameoverText.getLocalBounds();
          gameoverText.setOrigin(textRect.left + textRect.width / 2.0f,
                                 textRect.top + textRect.height / 2.0f);
          gameoverText.setPosition(1920 / 2.0f, 1080 / 2.0f);
          gameState = GameState::GameOver;
        }
      }
    }

    std::stringstream ss;

    ss << "High Score: " << highScore
       << "\n\nLives: " << shooter.shootersLive()
       << "\tAmmo : " << totallBullets
       << "\n\nTime : " << roundTime.asMilliseconds() / 1000.00;
    hud.setString(ss.str());

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
    if (gameState == GameState::GameOver || gameState == GameState::Starting ||
        gameState == GameState::Paused) {
      window.draw(gameoverText);
    }

    window.draw(hud);
    window.display();
  }
}