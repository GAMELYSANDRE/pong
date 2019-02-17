#include <Gamebuino-Meta.h>
#include "Menu.h"

// Draw text
void displayText(uint8_t x, uint8_t y, const char text[], int8_t redValue, uint8_t greenValue, uint8_t blueValue)
{
  gb.display.setColor(redValue, greenValue, blueValue);
  gb.display.setCursor(x, y);
  gb.display.print(text);
}

int centerMenu (const char* text[],int sizeTab)
{
  int sizeText = 0;
  for (uint8_t i = 0; i < sizeTab; i++)
  {
    if ( sizeText < strlen(text[i]))
    {
      sizeText = strlen(text[i]);
    }
  }
  return ((20-sizeText)/2*4);
}


// Draw and move in the Menu
void drawMenu (const char* text[], int sizeTab, uint8_t delayFlashingText, uint8_t* timerCounter, uint8_t* positionMenu, const uint16_t Image[])
{
  int posHorizMenu = centerMenu(text, sizeTab);
  gb.display.drawImage(12, 2, Image);
  for (uint8_t i = 0; i < sizeTab; i++)
  {
    displayText(posHorizMenu, 24 + (i * 9), text[i], 255, 255, 255);
  }
  *timerCounter = *timerCounter + 1;
  if ( *timerCounter > 0 && *timerCounter < (delayFlashingText / 2) )
  {
    displayText(posHorizMenu, 24 + (*positionMenu * 9), text[*positionMenu], 82, 62, 255);
  }
  if ( *timerCounter > 4 && *timerCounter < delayFlashingText )
  {
    displayText(posHorizMenu, 24 + (*positionMenu * 9), text[*positionMenu], 255, 255, 255);
  }
  if ( *timerCounter > 8 )
  {
    *timerCounter = 0;
  }
  if (gb.buttons.pressed(BUTTON_DOWN))
  {
    if (*positionMenu >= (sizeTab - 1))
    {
      *positionMenu = (sizeTab - 1);
    }
    else
    {
      *positionMenu = *positionMenu + 1;
    }
    gb.sound.playOK();
  }
  if (gb.buttons.pressed(BUTTON_UP))
  {

    if (*positionMenu <= 0)
    {
      *positionMenu = 0;
    }
    else
    {
      *positionMenu = *positionMenu - 1;
    }
    gb.sound.playOK();
  }
}
