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
      gb.display.setCursor(32, 2);
      gb.display.print(scorePlayerOne);
      gb.display.setColor(LIGHTGREEN);
      gb.display.setCursor(46, 2);
      gb.display.print(scorePlayerTwo);
      gb.display.setColor(GRAY);
      gb.display.drawLine(40, 0, 40 , 65);
      if (scorePlayerOne == 10 || scorePlayerTwo == 10  )
      {
        mode = 4;
      }

      // Movement of the ball according to the speed variables
      // check the condition of the ball
      switch (ballState)
      {
        case 0 :
          ballX = barLeftWidth;
          ballY = barLeftY + (barLeftHeight / 2 - ballSize / 2);
          gb.display.setCursor(0, 56);
          gb.display.setColor(RED);
          gb.display.print("PRESSE FLECHE DROITE");
          break;
        case 1 :
          ballX = ballX + ballSpeedX;
          ballY = ballY + ballSpeedY;
          if ( delayComputer != 0 )
          {
            delayComputer--;
          }
          break;
        case 2 :
          ballX = barRightX - barRightWidth;
          ballY = barRightY + (barRightHeight / 2 - ballSize / 2);
          if ( numberPlayer == 1 )
          {
            if ( delayComputer != 0 )
            {
              delayComputer--;
            }
            else
            {
              ballState = 1;
            }
            gb.display.setFontSize(3);
            gb.display.setCursor(35, 25);
            gb.display.setColor(RED);
            gb.display.print(delayComputer / 6);
          }
          else
          {
            gb.display.setCursor(0, 56);
            gb.display.setColor(RED);
            gb.display.print("PRESSE BOUTON A et B");
          }
          break;
      }


      // control the bar left
      // block the exit at the top of the screen
      if (gb.buttons.repeat(BUTTON_UP, 0) && barLeftY > barLeftSpeed)
      {
        barLeftY = barLeftY - barLeftSpeed;
      }
      // block the exit at the bottom of the screen
      if (gb.buttons.repeat(BUTTON_DOWN, 0) && barLeftY < gb.display.height() - barLeftHeight)
      {
        barLeftY = barLeftY + barLeftSpeed;
      }
      // control the bar right
      if ( numberPlayer == 2 )
      {
        // control of bar movements by a human
        // block the exit at the top of the screen
        if (gb.buttons.repeat(BUTTON_B, 0) && barRightY > barRightSpeed)
        {
          barRightY = barRightY - barRightSpeed;
        }
        // block the exit at the bottom of the screen
        if (gb.buttons.repeat(BUTTON_A, 0) && barRightY < gb.display.height() - barRightHeight)
        {
          barRightY = barRightY + barRightSpeed;
        }
      }
      else if ( numberPlayer == 1 )
      {
        // control of bar movements by a computer
        // movement of the bar during the game
        if ( ballState == 1 )
        {
          if ( delayComputer != 0 )
          {
            randomComputer = 1;
          }
          else
          {
            randomComputer = random(0, levelComputer);
          }
          if ( ballY < ( barRightY + barRightHeight / 2) && barRightY > barRightSpeed && randomComputer == 1 )
          {
            barRightY = barRightY - barRightSpeed;
          }
          if ( ballY > ( barRightY + barRightHeight / 2) && barRightY < gb.display.height() - barRightHeight && randomComputer == 1 )
          {
            barRightY = barRightY + barRightSpeed;
          }
        }
        // placement of the right bar following the left bar
        else
        {
          if ( barLeftY > 0 && barLeftY < gb.display.height() / 2 && barRightY < gb.display.height() - (gb.display.height() / 4 + barRightHeight / 2 ) )
          {
            barRightY = barRightY + barRightSpeed;
            if ( ballState == 0 )
            {
              delayComputer = 40;
            }
          }
          if ( barLeftY > gb.display.height() / 2 && barLeftY < gb.display.height() && barRightY > 0 + (gb.display.height() / 4 - barRightHeight / 2 ) )
          {
            barRightY = barRightY - barRightSpeed;
            if ( ballState == 0 )
            {
              delayComputer = 40;
            }
          }
        }
      }
      // verif ball screen
      // if the ball goes to the right of the screen
      if (ballX > gb.display.width() - ballSize  )
      {
        scorePlayerOne++;
        ballState = 2;
        delayComputer = 40;
        gb.sound.play("coins.wav");
      }
      // if the ball goes to the left of the screen
      if (ballX < 0 )
      {
        scorePlayerTwo++;
        ballState = 0;
        delayComputer = 40;
        gb.sound.play("coins.wav");
      }

      // bounces the ball at the top of the screen
      if (ballY > gb.display.height() - ballSize  )
      {
        ballSpeedY = -1 * ballSpeedY;
      }
      // bounces the ball at the bottom of the screen
      if (ballY < 0 )
      {
        ballSpeedY = -1 * ballSpeedY;
      }

      if ( ballState == 1 )
      {
        // tests the collisions with the ball and the left bar
        if (  ballX == barLeftWidth  )
        {
          if ( (ballY >= barLeftY) and (ballY <= barLeftY + barLeftHeight) )
          {
            ballSpeedX = -1 * ballSpeedX;
            gb.sound.play("bonk.wav");
          }
        }
        // tests the collisions with the ball and the right bar
        if (  ballX + ballSize >= barRightX and ballX + ballSize < gb.display.width()) 
        {
          if ( (ballY >= barRightY) and (ballY <= barRightY + barRightHeight) )
          {
            ballSpeedX = -1 * ballSpeedX;
            gb.sound.play("bonk.wav");
          }
        }
      }
      if ( gb.buttons.pressed(BUTTON_RIGHT) && ballState == 0)
      {
        ballState = 1;
        if ( ballSpeedX < 0 )
        {
          ballSpeedX = -1 * ballSpeedX;
        }
      }
      if ( gb.buttons.repeat(BUTTON_A,0) && gb.buttons.repeat(BUTTON_B,0) && ballState == 2)
      {
        ballState = 1;
        if ( ballSpeedX < 0 )
        {
          ballSpeedX = -1 * ballSpeedX;
        }
      }
      if ( gb.buttons.pressed(BUTTON_MENU) )
      {
        uint8_t quitMenu = gb.gui.menu("QUITTER LE JEU", quitMenuVariable);
        if (quitMenu == 0)
        {
          mode = 0;
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
      gb.display.print("GAGNE !");
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
            barLeftSpeed = 2;
            barRightSpeed = 2;
            mode = 2;
            break;
          case 1:
            positionMenu = 0;
            ballSpeedX = 2;
            ballSpeedY = 2;
            barLeftSpeed = 2;
            barRightSpeed = 2;
            mode = 2;
            break;
          case 2:
            positionMenu = 0;
            ballSpeedX = 3;
            ballSpeedY = 3;
            barLeftSpeed = 3;
            barRightSpeed = 3;
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
