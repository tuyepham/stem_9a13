#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>

void initLCD();
void showSplashScreen();
void updateLCD(float tempC, int moisturePercent);

#endif

