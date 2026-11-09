#include "lcd_display.h"
#include "config.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

static LiquidCrystal_I2C lcd(0x27, 16, 2);

// ==========================================
// TẠO BỘ KÝ TỰ TIẾNG VIỆT CÓ DẤU TRÊN LCD 1602
// ==========================================
// 0: Ký tự độ °
static byte degreeSymbol[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

// 1: Chữ 'Đ'
static byte char_D[8] = {
  B01110,
  B01001,
  B11110, // Dấu gạch ngang chữ Đ
  B01001,
  B01001,
  B01001,
  B01110,
  B00000
};

// 2: Chữ 'ệ'
static byte char_e_nang[8] = {
  B00100, // Dấu mũ ^
  B01110,
  B10001,
  B11111,
  B10000,
  B01110,
  B00000,
  B00100  // Dấu nặng .
};

// 3: Chữ 'ộ'
static byte char_o_nang[8] = {
  B00100, // Dấu mũ ^
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
  B00100  // Dấu nặng .
};

// 4: Chữ 'ẩ'
static byte char_a_hoi[8] = {
  B01100, // Dấu hỏi/mũ
  B00000,
  B01110,
  B00001,
  B01111,
  B10001,
  B01111,
  B00000
};

void initLCD() {
  lcd.init();
  lcd.backlight();
  // Nạp 5 ký tự tự tạo vào bộ nhớ CGRAM của LCD
  lcd.createChar(0, degreeSymbol); // 0: °
  lcd.createChar(1, char_D);        // 1: Đ
  lcd.createChar(2, char_e_nang);   // 2: ệ
  lcd.createChar(3, char_o_nang);   // 3: ộ
  lcd.createChar(4, char_a_hoi);    // 4: ẩ
}

void showSplashScreen() {
  lcd.setCursor(0, 0);
  lcd.print("====Lop 9/13====");
  lcd.setCursor(0, 1);
  lcd.print(" Nguyen Van Ba ");
  delay(5000);
  lcd.clear();
}

void updateLCD(float tempC, int moisturePercent) {
  // Dòng 0: Hiển thị tiếng Việt có dấu "Nhiệt Độ: XX.X°C" (vừa khít 16 ký tự)
  lcd.setCursor(0, 0);
  lcd.print("Nhi");
  lcd.write(byte(2)); // ệ
  lcd.print("t ");
  lcd.write(byte(1)); // Đ
  lcd.write(byte(3)); // ộ
  lcd.print(": ");
  lcd.print(tempC, 1);
  lcd.write(byte(0)); // °
  lcd.print("C");

  // Dòng 1: Hiển thị tiếng Việt có dấu "Độ ẩm: YY%"
  lcd.setCursor(0, 1);
  lcd.write(byte(1)); // Đ
  lcd.write(byte(3)); // ộ
  lcd.print(" ");
  lcd.write(byte(4)); // ẩ
  lcd.print("m: ");
  lcd.print(moisturePercent);
  lcd.print("%    ");
}
