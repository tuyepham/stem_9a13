#ifndef PUMP_CONTROL_H
#define PUMP_CONTROL_H

#include <Arduino.h>

void initPumps();
void controlPump(int pumpNum, bool turnOn);
void turnOnPump(int pumpNum);
void turnOffPump(int pumpNum);
void stopAllPumps();

// Điều khiển Quạt (Fan)
void controlFan(bool turnOn);
void turnOnFan();
void turnOffFan();

// Trạng thái thiết bị
bool isPumpOn(int pumpNum);
bool isFanOn();

// Các hàm kiểm tra (Test)
void testPumps(int delayMs = 1000);
void testFan(int delayMs = 1000);
void testAll(int delayMs = 1000); // Test cả 3 máy bơm và quạt

#endif

