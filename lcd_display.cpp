#include "lcd_display.h"
#include "config.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

static LiquidCrystal_I2C lcd(0x27, 16, 2);

// Tạo ký tự biểu tượng độ ° (5x8 pixels)
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

void initLCD() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, degreeSymbol); // 0: ký tự độ °
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
  // Dòng 0: Nhiệt độ tiếng Việt không dấu (vừa khít 16 ô: "Nhiet do: 28.5°C")
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do: ");
  lcd.print(tempC, 1); // 1 chữ số thập phân
  lcd.write(byte(0));  // Ký tự độ °
  lcd.print("C");

  // Dòng 1: Độ ẩm đất tiếng Việt không dấu ("Do am: 65%      ")
  lcd.setCursor(0, 1);
  lcd.print("Do am: ");
  lcd.print(moisturePercent);
  lcd.print("%    ");
}
