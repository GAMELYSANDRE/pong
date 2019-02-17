#ifndef __VARIABLES_H__
#define __VARIABLES_H__

// Variables Ball
int8_t ballX = 10;
int8_t ballY = 10;
uint8_t ballSize = 3;
uint8_t ballSpeedX = 1.5;
uint8_t ballSpeedY = 1.5;

// Variables Bar Left
uint8_t barLeftX = 1;
uint8_t barLeftY = 20;
uint8_t barLeftWidth = 4;
uint8_t barLeftHeight = 12;
uint8_t barLeftSpeed = 2;

// Variables Bar Right
uint8_t barRightX = 76;
uint8_t barRightY = 20;
uint8_t barRightWidth = 4;
uint8_t barRightHeight = 12;
uint8_t barRightSpeed = 2;

// Variables score player
uint8_t scorePlayerOne = 0;
uint8_t scorePlayerTwo = 0;
uint8_t Number_random = 0;
uint8_t numberPlayer = 0;

// Variables menu
uint8_t mode = 0;
uint8_t iniTimerCounter = 0;
uint8_t positionMenu = 0;

// Variable music
bool music = 0;

// Variable Game
int levelComputer = 3;

// Menu table variables
const char* startMenu[] = 
{
  "1 JOUEUR",
  "2 JOUEURS",
  "OPTIONS",
  "CREDITS",
};

const char* optionMenu[] = 
{
  "VITESSE BALLE",
  "NIVEAU DU JEU",
  "SORTIR"
};
const char* optionMenuSpeedBall[] = 
{
  "BALLE LENTE",
  "BALLE NORMALE",
  "BALLE RAPIDE"
};
const char* optionMenuLevelGame[] = 
{
  "FACILE",
  "NORMAL",
  "DIFFICILE"
};
#endif
