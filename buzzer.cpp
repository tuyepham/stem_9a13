#include "buzzer.h"
#include "config.h"

void initBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, BUZZER_OFF);
}

void turnOnBuzzer() { digitalWrite(BUZZER_PIN, BUZZER_ON); }

void turnOffBuzzer() { digitalWrite(BUZZER_PIN, BUZZER_OFF); }

void beep(int durationMs) {
  turnOnBuzzer();
  delay(durationMs);
  turnOffBuzzer();
}

void alertBeep(int durationMs) {
  beep(durationMs);
}

// Hàm test Buzzer: kêu 3 tiếng bíp ngắt quãng rõ ràng
void testBuzzer() {
  Serial.println(F("\n=== BAT DAU TEST BUZZER (CHAN 7) ==="));
  for (int i = 1; i <= 3; i++) {
    Serial.print(F("--> Bip lan "));
    Serial.println(i);
    beep(5000);  // Kêu 200ms
    delay(2000); // Nghỉ 200ms giữa các tiếng
  }
  turnOffBuzzer();
  Serial.println(F("=== HOAN TAT TEST BUZZER ===\n"));
}
