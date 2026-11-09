#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

void initBuzzer();
void turnOnBuzzer();
void turnOffBuzzer();
void beep(int durationMs = 150);
void alertBeep(int durationMs = 100);
void testBuzzer();

#endif

