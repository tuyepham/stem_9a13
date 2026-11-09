#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==========================================
// 1. CẢM BIẾN NHIỆT ĐỘ DS18B20
// ==========================================
#define ONE_WIRE_BUS 2

// ==========================================
// 2. CẢM BIẾN ĐỘ ẨM ĐẤT (ANALOG)
// ==========================================
#define SENSOR_MOISTURE_PIN A0
const int DRY_MV = 2189;  // Điện áp khi không có nước (0%)
const int WET_MV = 680;   // Điện áp khi ngập nước (100%)

// ==========================================
// 3. 2 CẢM BIẾN MỰC NƯỚC (DIGITAL INPUT)
// ==========================================
#define WATER_LEVEL_1_PIN 5  // Mức nước 1
#define WATER_LEVEL_2_PIN 6  // Mức nước 2

// ==========================================
// 4. CÒI BÁO ĐỘNG BUZZER (DIGITAL OUTPUT)
// ==========================================
#define BUZZER_PIN 7         // Còi buzzer gắn chân 7
#define BUZZER_ON  HIGH      // Mức kích BẬT còi (nếu buzzer kích mức Thấp thì đổi sang LOW)
#define BUZZER_OFF LOW       // Mức kích TẮT còi (nếu buzzer kích mức Thấp thì đổi sang HIGH)

// ==========================================
// 5. MÁY BƠM & QUẠT (DIGITAL OUTPUT)
// ==========================================
#define PUMP1_PIN 8   // Máy bơm 1
#define PUMP2_PIN 9   // Máy bơm 2
#define PUMP3_PIN 10  // Máy bơm 3
#define FAN_PIN   11  // Quạt làm mát

// Cấu hình mức kích Relay máy bơm & quạt:
// Nếu dùng Relay kích mức Thấp (Active LOW), đổi PUMP_ON/FAN_ON thành LOW và OFF thành HIGH
#define PUMP_ON  HIGH   // Mức kích BẬT bơm
#define PUMP_OFF LOW    // Mức kích TẮT bơm
#define FAN_ON   HIGH   // Mức kích BẬT quạt
#define FAN_OFF  LOW    // Mức kích TẮT quạt

#endif

