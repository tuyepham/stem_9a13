#include "pump_control.h"
#include "config.h"

// Biến lưu trạng thái hiện tại của 3 máy bơm và quạt (tránh in Serial lặp lại mỗi chu kỳ)
static bool pumpStates[3] = {false, false, false};
static bool fanState = false;

void initPumps() {
  pinMode(PUMP1_PIN, OUTPUT);
  pinMode(PUMP2_PIN, OUTPUT);
  pinMode(PUMP3_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Khởi tạo mức tắt
  digitalWrite(PUMP1_PIN, PUMP_OFF);
  digitalWrite(PUMP2_PIN, PUMP_OFF);
  digitalWrite(PUMP3_PIN, PUMP_OFF);
  digitalWrite(FAN_PIN, FAN_OFF);

  pumpStates[0] = false;
  pumpStates[1] = false;
  pumpStates[2] = false;
  fanState = false;
}

void controlPump(int pumpNum, bool turnOn) {
  if (pumpNum < 1 || pumpNum > 3) {
    Serial.println(F("Loi: So thu tu bom khong hop le (chi tu 1 den 3)!"));
    return;
  }

  // Chỉ kích hoạt và in Serial khi có sự thay đổi trạng thái
  if (pumpStates[pumpNum - 1] != turnOn) {
    pumpStates[pumpNum - 1] = turnOn;
    int pin = (pumpNum == 1) ? PUMP1_PIN : ((pumpNum == 2) ? PUMP2_PIN : PUMP3_PIN);
    digitalWrite(pin, turnOn ? PUMP_ON : PUMP_OFF);

    Serial.print(F(">>> May bom "));
    Serial.print(pumpNum);
    Serial.println(turnOn ? F(": [ON] DANG BAT") : F(": [OFF] DA TAT"));
  }
}

void turnOnPump(int pumpNum) {
  controlPump(pumpNum, true);
}

void turnOffPump(int pumpNum) {
  controlPump(pumpNum, false);
}

void stopAllPumps() {
  for (int i = 1; i <= 3; i++) {
    controlPump(i, false);
  }
  Serial.println(F("-> Da tat toan bo 3 may bom!"));
}

void controlFan(bool turnOn) {
  if (fanState != turnOn) {
    fanState = turnOn;
    digitalWrite(FAN_PIN, turnOn ? FAN_ON : FAN_OFF);
    Serial.print(F(">>> Quat lam mat: "));
    Serial.println(turnOn ? F("[ON] DANG BAT") : F("[OFF] DA TAT"));
  }
}

bool isPumpOn(int pumpNum) {
  if (pumpNum >= 1 && pumpNum <= 3) {
    return pumpStates[pumpNum - 1];
  }
  return false;
}

bool isFanOn() {
  return fanState;
}

void turnOnFan() {
  controlFan(true);
}

void turnOffFan() {
  controlFan(false);
}

// Hàm test riêng Quạt: Bật 1 giây rồi tắt
void testFan(int delayMs) {
  Serial.println(F("\n=== BAT DAU TEST QUAT ==="));
  Serial.println(F("--> Test Quạt: BẬT (ON)"));
  turnOnFan();
  delay(delayMs);

  Serial.println(F("--> Test Quạt: TẮT (OFF)"));
  turnOffFan();
  Serial.println(F("=== HOÀN TẤT TEST QUAT ===\n"));
}

// Hàm test lần lượt từng máy bơm: Bật 1 giây rồi tắt
void testPumps(int delayMs) {
  Serial.println(F("\n=== BAT DAU TEST 3 MAY BOM ==="));
  for (int i = 1; i <= 3; i++) {
    Serial.print(F("--> Test Bơm "));
    Serial.print(i);
    Serial.println(F(": BẬT (ON)"));
    turnOnPump(i);
    delay(delayMs); // Bật trong khoảng thời gian delayMs (mặc định 1000ms = 1 giây)

    Serial.print(F("--> Test Bơm "));
    Serial.print(i);
    Serial.println(F(": TẮT (OFF)"));
    turnOffPump(i);
    delay(500); // Nghỉ 0.5 giây trước khi chuyển sang bơm tiếp theo
  }
  stopAllPumps(); // Đảm bảo tất cả bơm đều đã tắt
  Serial.println(F("=== HOÀN TẤT TEST BƠM ===\n"));
}

// Hàm test toàn bộ thiết bị (3 máy bơm + 1 quạt, mỗi cái bật 1 giây)
void testAll(int delayMs) {
  Serial.println(F("\n=========================================="));
  Serial.println(F("  BAT DAU TEST TOAN BO HE THONG (BOM & QUAT)"));
  Serial.println(F("=========================================="));
  
  testPumps(delayMs); // Test lần lượt 3 máy bơm
  delay(500);
  testFan(delayMs);   // Test tiếp quạt làm mát

  Serial.println(F("-> KET THUC KIEM TRA TOAN BO THIET BI.\n"));
}

