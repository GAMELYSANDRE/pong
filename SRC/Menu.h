#ifndef __MENU_H__
#define __MENU_H__


// Draw text
void displayText (uint8_t x, uint8_t y, const char text[], int8_t redValue, uint8_t greenValue, uint8_t blueValue);

void drawMenu (const char* text[], int sizeTab, uint8_t delayFlashingText, uint8_t* timerCounter, uint8_t* positionMenu,const uint16_t Image[]);

#endif
