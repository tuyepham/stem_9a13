#include "config.h"
#include "setting.h"
#include "lcd_display.h"
#include "temperature.h"
#include "moisture.h"
#include "pump_control.h"
#include "level_water.h"
#include "buzzer.h"

void setup() {
  // 1. Mở giao tiếp Serial với máy tính
  Serial.begin(9600);

  // 2. Khởi tạo các module phần cứng
  initPumps();        // Cấu hình chân & tắt toàn bộ bơm, quạt
  initWaterLevel();   // Cấu hình chân 2 cảm biến mực nước (D5, D6)
  initBuzzer();       // Cấu hình chân còi Buzzer (D7)
  initTemperature();  // Khởi động cảm biến DS18B20
  initLCD();          // Khởi động màn hình LCD 16x2

  // 3. Hiển thị màn hình chào trong 5 giây
  showSplashScreen();

  // 4. Kiểm tra (Test) thiết bị
  //testBuzzer(); // Test còi kêu 3 tiếng bíp lúc khởi động
  //testAll();  // hoặc gọi testPumps(); và testFan(); riêng nếu muốn
}

// ================================================================
// HÀM ĐIỀU KHIỂN TỰ ĐỘNG THEO LƯU ĐỒ (AUTO CONTROL FLOW)
// ================================================================
void handleAutoControl(float tempC, int moisture) {
  // 1. Điều khiển Bơm 1 & Cảm biến mực nước 1 (0: có nước, 1: hết nước)
  // Nếu hết nước (1) -> Bật bơm 1 cho đến khi đầy nước (0) thì dừng
  int level1 = readWaterLevel(1);
  if (level1 == 1) {
    turnOnPump(1);
  } else if (level1 == 0) {
    turnOffPump(1);
  }

  // 2. Điều khiển Bơm 2 & Cảm biến mực nước 2 (0: có nước, 1: hết nước)
  // Nếu hết nước (1) -> Bật bơm 2 cho đến khi đầy nước (0) thì dừng
  int level2 = readWaterLevel(2);
  if (level2 == 1) {
    turnOnPump(2);
  } else if (level2 == 0) {
    turnOffPump(2);
  }

  // 3. Điều khiển Quạt theo Nhiệt độ
  // Nếu Nhiệt độ > TEMP_FAN_ON -> Bật quạt cho đến khi Nhiệt độ < TEMP_FAN_OFF thì dừng
  if (tempC > TEMP_FAN_ON) {
    turnOnFan();
  } else if (tempC < TEMP_FAN_OFF) {
    turnOffFan();
  }

  // 4. Điều khiển Bơm 3 theo Độ ẩm đất
  // Nếu Độ ẩm < MOISTURE_PUMP3_ON -> Bật bơm 3 cho đến khi Độ ẩm >= MOISTURE_PUMP3_OFF thì dừng
  if (moisture < MOISTURE_PUMP3_ON) {
    turnOnPump(3);
  } else if (moisture >= MOISTURE_PUMP3_OFF) {
    turnOffPump(3);
  }

  // 5. CẢNH BÁO BẰNG TIẾNG BÍP (CÒI BUZZER)
  // Kêu bíp khi: Quá nhiệt độ, Mực nước bể cạn (level 1 hoặc 2), hoặc Độ ẩm đất thấp
  bool isOverTemp    = (tempC > TEMP_FAN_ON);
  bool isWaterEmpty  = (level1 == 1 || level2 == 1);
  bool isLowMoisture = (moisture < MOISTURE_PUMP3_ON);

  if (isOverTemp || isWaterEmpty || isLowMoisture) {
    alertBeep(BEEP_ALERT_DURATION_MS);
  }
}

void loop() {
  // 1. Đọc dữ liệu từ các cảm biến
  float tempC = readTemperature();
  int moisture = readMoisturePercent();

  // 2. Cập nhật dữ liệu hiển thị lên LCD
  updateLCD(tempC, moisture);

  // 3. Thực thi logic điều khiển tự động theo Flow mới
  handleAutoControl(tempC, moisture);

  // 4. Nghỉ giữa các chu kỳ đo
  delay(500);
}
