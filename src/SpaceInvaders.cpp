#include "SpaceInvaders.h"
#include "Bullet.h"
#include "Dropper.h"
#include "Enemy.h"
#include "Shooter.h"
#include "TextureHolder.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace sf;

enum GameState { Playing, Paused, GameOver, Starting };

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
  enemies = createEnemyLines();

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

  Text messageText;
  messageText.setFont(font);
  messageText.setCharacterSize(70);
  messageText.setFillColor(Color::Magenta);
  messageText.setString("Press Enter to Start the Game");
  FloatRect textRect = messageText.getLocalBounds();
  messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                        textRect.top + textRect.height / 2.0f);
  messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

  /*******creating shooter bullets*******/

  Bullet shooterBullets[100];
  for (int i = 0; i < 100; i++) {
    shooterBullets[i].setType(Dropper::BULLET);
  }
  int currentBullet = 0;
  int totallBullets = 100;
  int fireRate = 3;
  Time lastPressed; // bullets keyPressed timing

  // enemy bomb
  Bullet bomb;
  bomb.setType(Dropper::BOMB);

  /* ****heart dropper***** */
  Bullet heartDropper;
  heartDropper.setType(Dropper::HEART);
  srand(time(0));
  int randomDropper = rand() % 60;

  /****** ammo dropper****** */
  Bullet ammoDropper;
  ammoDropper.setType(Dropper::AMMO);
  srand(time(0) * 100);
  int randomDropper2 = rand() % 60;

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

  SoundBuffer extraBulletBuffer;
  extraBulletBuffer.loadFromFile("sound/reload.wav");
  Sound extraBulletSound;
  extraBulletSound.setBuffer(extraBulletBuffer);

  SoundBuffer extraHeartBuffer;
  extraHeartBuffer.loadFromFile("sound/hearthit.wav");
  Sound extraHeartSound;
  extraHeartSound.setBuffer(extraHeartBuffer);

  SoundBuffer bombHitBuffer;
  bombHitBuffer.loadFromFile("sound/hit.wav");
  Sound bombHitSound;
  bombHitSound.setBuffer(bombHitBuffer);

  // bunch of control variables
  Time dt;
  Time roundTime;
  int livingEnemies = 60;
  bool godown = false;
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
          messageText.setString("Paused!");
          FloatRect textRect = messageText.getLocalBounds();
          messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                textRect.top + textRect.height / 2.0f);
          messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
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
        heartDropper.stop();
        ammoDropper.stop();

        livingEnemies = 60;
        totallBullets = 100;
        enemies = createEnemyLines();
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
      //************* handle bullets for shooter******************

      if (Keyboard::isKeyPressed(Keyboard::Space)) {
        if (totallBullets > 0) {
          if (gameTime.asMilliseconds() - lastPressed.asMilliseconds() >
              1000 / fireRate) {
            shooterBullets[currentBullet].shoot(shooter.getCenter().x,
                                                shooter.getCenter().y);
            currentBullet++; // array of bullets index++
            totallBullets--;
            shootSound.play();
            if (currentBullet > 99) {
              currentBullet = 0;
            }

            lastPressed = gameTime;
          }
        } else {
          gameState = GameState::GameOver;
          messageText.setCharacterSize(100);
          messageText.setFillColor(Color::Red);
          messageText.setString("Out of Ammo nigga");
          FloatRect textRect = messageText.getLocalBounds();
          messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                textRect.top + textRect.height / 2.0f);
          messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
        }
      }

      // drop the bomb
      srand(time(0));
      int randomBomber = rand() % 60;
      if (enemies[randomBomber].isAlive() && !bomb.isInFlight())
        bomb.shoot(enemies[randomBomber].getCenter().x,
                   enemies[randomBomber].getCenter().y);
    } // END of PlayingState
    /*
     *****************************
     * updating the game
     *****************************
     */
    float dtAsSeconds = dt.asSeconds();

    shooter.update(dt.asSeconds());
    if (gameState == GameState::Playing) {
      // updating all enemies
      for (int i = 0; i < 60; i++) {
        if (godown == true)
          enemies[i].moveDown();

        enemies[i].update(dtAsSeconds);
      }
      // checking if enemies get to the edge of screen
      if (godown == false) {
        for (int i = 0; i < 60; i++) {
          if (enemies[i].getCenter().x + enemies[i].getPosition().width / 2 +
                      10 >
                  1920 ||
              enemies[i].getPosition().left - 10 < 0) {
            godown = true;
            break;
          }
        }
      } else {
        godown = false;
      }

      //********* updating bullets in flight*************

      dtAsSeconds = dt.asSeconds();
      for (int i = 0; i < 100; i++) {
        shooterBullets[i].update(dtAsSeconds);

        for (int j = 0; j < 60; j++) {

          /**********************checking enemies collision with shooter*******/
          if (shooter.getPosition().top <
              enemies[j].getPosition().top + enemies[j].getPosition().height) {
            gameState = GameState ::GameOver;
            messageText.setCharacterSize(150);
            messageText.setFillColor(Color::Red);
            messageText.setString("GAME OVER!");
            shooterDeathSound.play();
            FloatRect textRect = messageText.getLocalBounds();
            messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                  textRect.top + textRect.height / 2.0f);
            messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
          }

          /*********************** Checking for enemy Hit *******************/
          if (shooterBullets[i].getPosition().intersects(
                  enemies[j].getPosition()) &&
              enemies[j].isAlive() && shooterBullets[i].isInFlight()) {
            enemies[j].hit();
            shooterBullets[i].stop();
            enemyDeathSound.play();
            livingEnemies--;
            // releasing heart
            if (j == randomDropper) {
              heartDropper.shoot(enemies[j].getCenter().x,
                                 enemies[j].getCenter().y);
            }
            // releasing ammo
            if (j == randomDropper2) {
              ammoDropper.shoot(enemies[j].getCenter().x,
                                enemies[j].getCenter().y);
            }
          }
        }
      }
      // ************wining state**************
      if (livingEnemies == 0) {
        gameState = GameState::GameOver;
        float score = roundTime.asSeconds();
        // holding highest score
        if (score < highScore)
          highScore = score;
        else if (highScore == 0)
          highScore = score;
        messageText.setFont(digitalFont);
        messageText.setCharacterSize(150);
        messageText.setFillColor(Color::Green);
        messageText.setString("You Win Nigga :) ");
        FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                              textRect.top + textRect.height / 2.0f);
        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
      }

      //************bombs******************

      bomb.update(dt.asSeconds());
      if (bomb.getPosition().top > 1080)
        bomb.stop();
      // bomb hits the shooter
      if (bomb.getPosition().intersects(shooter.getPosition())) {
        if (shooter.isAlive() && bomb.isInFlight()) {
          shooter.hit();
          bombHitSound.play();
          bomb.stop();
        }
        if (!shooter.isAlive()) {
          messageText.setFillColor(Color::Red);
          messageText.setCharacterSize(150);
          messageText.setString("GAME OVER!");
          shooterDeathSound.play();
          FloatRect textRect = messageText.getLocalBounds();
          messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                textRect.top + textRect.height / 2.0f);
          messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
          gameState = GameState::GameOver;
        }
      }
    }

    /**update heart dropper**/
    if (heartDropper.getPosition().intersects(shooter.getPosition())) {
      heartDropper.stop();
      extraHeartSound.play();
      shooter.increaseHealth();
    }
    if (heartDropper.isInFlight())
      heartDropper.update(dt.asSeconds());

    //**update ammo dropper**/
    if (ammoDropper.getPosition().intersects(shooter.getPosition())) {
      ammoDropper.stop();
      extraBulletSound.play();
      totallBullets += 50;
    }
    if (ammoDropper.isInFlight())
      ammoDropper.update(dt.asSeconds());

    stringstream ss;
    ss << "High Score: " << setprecision(2) << fixed << highScore
       << "\n\nLives: " << shooter.shootersLive()
       << "\tAmmo : " << totallBullets << "\n\nTime : " << setprecision(2)
       << fixed << roundTime.asMilliseconds() / 1000.00;

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
      window.draw(messageText);
    }
    if (heartDropper.isInFlight())
      window.draw(heartDropper.getShape());
    if (ammoDropper.isInFlight())
      window.draw(ammoDropper.getShape());
    window.draw(hud);
    window.display();
  }
}