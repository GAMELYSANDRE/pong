#include <Gamebuino-Meta.h>
#include "Variables.h"
#include "Graphics.h"
#include "Menu.h"



void setup() {
  // initialisation gamebuino
  gb.begin();

}

void loop()
{
  while (!gb.update());
  gb.display.clear();
  switch (mode)
  {
    case 0:
      drawMenu(startMenu, 4, 10, &iniTimerCounter, &positionMenu, Pong_MetaData);
      music = 0;
      if (gb.buttons.pressed(BUTTON_A))
      {
        switch (positionMenu) {
          case 0:
            mode = 1;
            numberPlayer = 1;
            break;
          case 1:
            mode = 1;
            numberPlayer = 2;
            break;
          case 2:
            positionMenu = 0;
            mode = 2;
            break;
          case 3:
            positionMenu = 0;
            mode = 7;
            break;  
        }
        gb.sound.playTick();
      }
      break;
    case 1:

      // show score
      gb.display.setColor(BLUE);
      gb.display.setCursorX(32);
      gb.display.print(scorePlayerOne);
      gb.display.setColor(LIGHTGREEN);
      gb.display.setCursorX(46);
      gb.display.print(scorePlayerTwo);
      gb.display.setColor(GRAY);
      gb.display.drawLine(40, 0, 40 , 65);
      if (scorePlayerOne == 10 || scorePlayerTwo == 10  )
      {
        mode = 4;
      }

      // Movement of the ball according to the speed variables
      ballX = ballX + ballSpeedX;
      ballY = ballY + ballSpeedY;

      // control the bar left
      // block the exit at the top of the screen
      if (gb.buttons.repeat(BUTTON_UP, 0))
      {
        if (barLeftY > 0) {
          barLeftY = barLeftY - barLeftSpeed;
        }
      }
      // block the exit at the bottom of the screen
      if (gb.buttons.repeat(BUTTON_DOWN, 0))
      {
        if (barLeftY < gb.display.height() - barLeftHeight) {
          barLeftY = barLeftY + barLeftSpeed;
        }
      }
      // control the bar right
      if ( numberPlayer == 2 ) {
        // control of bar movements by a human
        // block the exit at the top of the screen
        if (gb.buttons.repeat(BUTTON_B, 0)) {
          if (barRightY > 0) {
            barRightY = barRightY - barRightSpeed;
          }
        }
        // block the exit at the bottom of the screen
        if (gb.buttons.repeat(BUTTON_A, 0)) {
          if (barRightY < gb.display.height() - barRightHeight) {
            barRightY = barRightY + barRightSpeed;
          }
        }
      }
      else if ( numberPlayer == 1 ) {
        // control of bar movements by a computer
        if ( ballY < ( barRightY + barRightHeight / 2) && random (0, levelComputer) == 1 ) {
          if (barRightY > 0) {
            barRightY = barRightY - barRightSpeed;
          }
        }
        // control of bar movements by a computer
        if ( ballY > ( barRightY + barRightHeight / 2) && random (0, levelComputer) == 1 ) {
          if (barRightY < gb.display.height() - barRightHeight) {
            barRightY = barRightY + barRightSpeed;
          }
        }
      }
      // verif ball screen
      // if the ball goes to the right of the screen
      if (ballX > gb.display.width() - ballSize  ) {
        scorePlayerOne++;
        ballX = 40;
        ballY = 40;
        Number_random = random(0, 2);
        Number_random == 0 ? ballSpeedX *= -1 : ballSpeedX *= 1;
        Number_random = random(0, 2);
        Number_random == 0 ? ballSpeedY *= -1 : ballSpeedY *= 1;
        gb.sound.play("coins.wav");
      }
      // if the ball goes to the left of the screen
      if (ballX < 0 ) {
        scorePlayerTwo++;
        ballX = 40;
        ballY = 40;
        Number_random = random(0, 2);
        Number_random == 0 ? ballSpeedX *= -1 : ballSpeedX *= 1;
        Number_random = random(0, 2);
        Number_random == 0 ? ballSpeedY *= -1 : ballSpeedY *= 1;
        gb.sound.play("coins.wav");
      }

      // bounces the ball at the top of the screen
      if (ballY > gb.display.height() - ballSize  ) {
        ballSpeedY = -1 * ballSpeedY;
      }
      // bounces the ball at the bottom of the screen
      if (ballY < 0 ) {
        ballSpeedY = -1 * ballSpeedY;
      }

      // tests the collisions with the ball and the left bar
      if (  ballX <= barLeftX + barLeftWidth  ) {
        if ( (ballY >= barLeftY) and (ballY <= barLeftY + barLeftHeight) ) {
          ballSpeedX = -1 * ballSpeedX;
          gb.sound.play("bonk.wav");
        }
      }
      // tests the collisions with the ball and the right bar
      if (  ballX + ballSize >= barRightX  ) {
        if ( (ballY >= barRightY) and (ballY <= barRightY + barRightHeight) ) {
          ballSpeedX = -1 * ballSpeedX;
          gb.sound.play("bonk.wav");
        }
      }

      // Draw the ball
      gb.display.setColor(YELLOW);
      gb.display.fillRect(ballX, ballY, ballSize, ballSize);
      // Draw the bar at the Left of the screen
      gb.display.drawImage(barLeftX, barLeftY, IMG_BarBlue);
      // Draw the bar at the Right of the screen
      gb.display.drawImage(barRightX, barRightY, IMG_BarGreen);
      break;
    //-------------------------------------/
    //                                     /
    //  menu for choose the option game    /
    //                                     /
    //-------------------------------------/
    case 2:
      drawMenu(optionMenu, 3, 10, &iniTimerCounter, &positionMenu, Pong_MetaData);
      if (gb.buttons.pressed(BUTTON_A))
      {
        switch (positionMenu)
        {
          case 0:
            positionMenu = 0;
            mode = 5;
            break;
          case 1:
            positionMenu = 0;
            mode = 6;
            break;
          case 2:
            positionMenu = 0;
            mode = 0;
            break;
          case 3:
            positionMenu = 0;
            mode = 0;
            break;
        }
        gb.sound.playTick();
      }
      break;
    case 4:
      gb.display.setFontSize(2);
      gb.display.setCursor(10, 15);
      if (scorePlayerOne == 10 ) {
        gb.display.print("JOUEUR 1");
      }
      else {
        gb.display.print("JOUEUR 2");
      }
      gb.display.setCursor(15, 35);
      gb.display.print("GAGNE !...");
      if ( music == 0 ) {
        gb.sound.play("winning.wav");
        music = 1;
      }
      if (gb.buttons.repeat(BUTTON_A, 0)) {
        mode = 0;
        scorePlayerOne = 0;
        scorePlayerTwo = 0;
      }
      break;
    //-----------------------------------------/
    //                                         /
    //  menu for choose the speed of the ball  /
    //                                         /
    //-----------------------------------------/
    case 5:
      drawMenu(optionMenuSpeedBall, 3, 10, &iniTimerCounter, &positionMenu, Pong_MetaData);
      if (gb.buttons.pressed(BUTTON_A))
      {
        switch (positionMenu)
        {
          case 0:
            positionMenu = 0;
            ballSpeedX = 1;
            ballSpeedY = 1;
            mode = 2;
            break;
          case 1:
            positionMenu = 0;
            ballSpeedX = 1.5;
            ballSpeedY = 1.5;
            mode = 2;
            break;
          case 2:
            positionMenu = 0;
            ballSpeedX = 2;
            ballSpeedY = 2;
            mode = 2;
            break;
        }
        gb.sound.playTick();
      }
      break;
    //-----------------------------------------/
    //                                         /
    //  menu for choose the level of the game  /
    //                                         /
    //-----------------------------------------/
    case 6:
      drawMenu(optionMenuLevelGame, 3, 10, &iniTimerCounter, &positionMenu, Pong_MetaData);
      if (gb.buttons.pressed(BUTTON_A))
      {
        switch (positionMenu)
        {
          case 0:
            positionMenu = 1;
            levelComputer = 6;
            mode = 2;
            break;
          case 1:
            positionMenu = 1;
            levelComputer = 3;
            mode = 2;
            break;
          case 2:
            positionMenu = 1;
            levelComputer = 2;
            mode = 2;
            break;
        }
        gb.sound.playTick();
      }
      break;
    case 7:
      gb.display.drawImage(20, 0, IMG_LOGO);
      gb.display.setColor(154, 205, 50);
      gb.display.setCursor(8, 30);
      gb.display.println("CODE et GRAPHISME");
      gb.display.setCursor(15, 40);
      gb.display.println("- LYSANDRE -");
      gb.display.setCursor(0, 50);
      gb.display.println("gamelysandre@gmail.com");
      if (gb.buttons.pressed(BUTTON_A))
      {
        mode = 0;
        gb.sound.playTick();
      }
      break;
  }
}
