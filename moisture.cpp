#include "moisture.h"
#include "config.h"

int readMoistureVoltageMV() {
  int val = analogRead(SENSOR_MOISTURE_PIN);
  int voltage_mV = (long)val * 5000 / 1023;
  return voltage_mV;
}

int readMoisturePercent() {
  int val = analogRead(SENSOR_MOISTURE_PIN);
  int voltage_mV = (long)val * 5000 / 1023;

  int percent = map(voltage_mV, DRY_MV, WET_MV, 0, 100);
  percent = constrain(percent, 0, 100);

  Serial.print(F("ADC: "));
  Serial.print(val);
  Serial.print(F(" | Dien ap: "));
  Serial.print(voltage_mV);
  Serial.print(F(" mV | Do am: "));
  Serial.print(percent);
  Serial.println(F("%"));

  return percent;
}

