#include <iostream>
#include <SFML/Graphics.hpp>
#include "Shooter.h"
#include "TextureHolder.h"
#include "SpaceInvaders.h"
#include "Enemy.h"
using namespace sf;

int main()
{
    TextureHolder holder;
    VideoMode vm(1920,1080);
    RenderWindow window(vm,"Space Invader",Style::Fullscreen);
    Sprite background;
    background.setTexture(TextureHolder::GetTexture("resorces/graphics/backgroud.jpg"));
    /******Creating the Shooter*******/
    Shooter shooter(1920/2,1080 - 130);
    
    /******Creating enemys**********/
    Enemy* enemies = nullptr;
    enemies = createEnemyLines(1920.0f);
    Clock clock;
    Time dt;
    float moveDownTime;
    
    Clock moveDownClock;
    /*******MAIN GAME LOOP**********/
    while (window.isOpen())
    {
        /*
         *****************************
         * reading the Player input
         *****************************
        */

       if (Keyboard::isKeyPressed(Keyboard::Escape))
       {
           window.close();
       }
       if (Keyboard::isKeyPressed(Keyboard::Left))
       {
           shooter.moveLeft();
       }
       else
       {
           shooter.stopLeft();
       }
         if (Keyboard::isKeyPressed(Keyboard::Right))
       {
           shooter.moveRight();
       }
       else
       {
           shooter.stopRight();
       }

       

        /*
         *****************************
         * updating the game
         *****************************
        */
        dt=clock.restart();
        shooter.update(dt);
        for (int i = 0; i < 60; i++)
        {
            enemies[i].update(dt);
        }

        for (int i = 0; i < 60 ; i++){
            if(enemies[i].getPosition().left + 50 >1920 || enemies[i].getPosition().left-10 <0){
                for(int i = 0; i < 60 ; i++)
                enemies[i].moveDown(dt);
                }
        }
    


        /*
         *****************************
         * drawing the Game
         *****************************
        */

        window.clear();
        window.draw(background);
        for (int  i = 0; i < 60; i++)
        {
            window.draw(enemies[i].getShape());
        }
        
        window.draw(shooter.getShape());
        window.display();       

   }
    

}