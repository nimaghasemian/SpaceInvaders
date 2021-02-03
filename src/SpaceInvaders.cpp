#include <iostream>
#include <SFML/Graphics.hpp>
#include "Shooter.h"
#include "TextureHolder.h"
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
    


    Clock clock;
    Time dt;


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


        /*
         *****************************
         * drawing the Game
         *****************************
        */

        window.clear();
        window.draw(background);
        window.draw(shooter.getShape());
        window.display();       

   }
    

}