#ifndef SETTING_H
#define SETTING_H

// ================================================================
// CÀI ĐẶT CÁC NGƯỠNG ĐIỀU KHIỂN TỰ ĐỘNG CHO HỆ THỐNG
// Người dùng có thể dễ dàng thay đổi các giá trị ở đây
// ================================================================

// 1. Cấu hình ngưỡng Nhiệt độ điều khiển Quạt (°C)
const float TEMP_FAN_ON  = 35.0;  // Nhiệt độ vượt quá mức này (> 35°C) sẽ BẬT quạt
const float TEMP_FAN_OFF = 30.0;  // Nhiệt độ giảm dưới mức này (< 30°C) sẽ TẮT quạt

// 2. Cấu hình ngưỡng Độ ẩm đất điều khiển Bơm 3 (%)
const int MOISTURE_PUMP3_ON  = 10; // Độ ẩm đất dưới mức này (< 10%) sẽ BẬT Bơm 3
const int MOISTURE_PUMP3_OFF = 50; // Độ ẩm đất đạt mức này trở lên (>= 50%) sẽ TẮT Bơm 3

// 3. Cấu hình Còi cảnh báo (Buzzer)
const int BEEP_ALERT_DURATION_MS = 100; // Thời lượng mỗi tiếng bíp cảnh báo (100ms)

#endif

