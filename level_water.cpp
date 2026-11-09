#include "level_water.h"
#include "config.h"

void initWaterLevel() {
  pinMode(WATER_LEVEL_1_PIN, INPUT);
  pinMode(WATER_LEVEL_2_PIN, INPUT);
}

int readWaterLevel(int sensorNum) {
  switch (sensorNum) {
  case 1:
    return digitalRead(WATER_LEVEL_1_PIN);
  case 2:
    return digitalRead(WATER_LEVEL_2_PIN);
  default:
    Serial.println(
        F("Loi: So thu tu cam bien muc nuoc khong hop le (chi co 1 va 2)!"));
    return -1;
  }
}
