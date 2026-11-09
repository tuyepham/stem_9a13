#include "temperature.h"
#include "config.h"
#include <OneWire.h>
#include <DallasTemperature.h>

static OneWire oneWire(ONE_WIRE_BUS);
static DallasTemperature sensors(&oneWire);

void initTemperature() {
  sensors.begin();
}

float readTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

