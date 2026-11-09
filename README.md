# DỰ ÁN STEM: HỆ THỐNG GIÁM SÁT & ĐIỀU KHIỂN NÔNG NGHIỆP THÔNG MINH
**Lớp:** 9/13  
**Học sinh / Nhóm thực hiện:** Nguyễn Văn Bá  
**Mã nguồn:** [`stem_9A13.ino`](stem_9A13.ino)  
**Lưu đồ hoạt động:** Chi tiết xem tại [`WORKFLOW.md`](WORKFLOW.md)  
**Sơ đồ khối hệ thống:** Chi tiết xem tại [`BLOCK_DIAGRAM.md`](BLOCK_DIAGRAM.md)

---

## 1. Giới thiệu dự án
Dự án ứng dụng vi điều khiển Arduino để tự động thu thập thông số môi trường và điều khiển các cơ cấu chấp hành:
- **Cảm biến nhiệt độ (DS18B20):** Đo nhiệt độ môi trường (không đo nước).
- **Cảm biến độ ẩm đất:** Đo độ ẩm đất, chuyển đổi điện áp mV sang % độ ẩm ($0 - 100\%$).
- **2 Cảm biến mực nước:** Theo dõi mức nước trong 2 bồn chứa.
- **3 Máy bơm & 1 Quạt:** Điều khiển bơm tưới tiêu, cấp thoát nước và quạt thông gió làm mát.
- **Còi báo động (Buzzer):** Cảnh báo âm thanh khi quá nhiệt, cạn nước bồn hoặc đất quá khô.
- **Giao diện hiển thị:** Màn hình LCD 16x2 (I2C) và cổng Serial Monitor (9600 baud).

---

## 2. Danh sách linh kiện phần cứng

| STT | Thiết bị | Số lượng | Vai trò | Ghi chú |
|:---:|:---|:---:|:---|:---|
| 1 | Arduino Uno / Nano | 1 | Vi điều khiển trung tâm | |
| 2 | Cảm biến nhiệt độ DS18B20 | 1 | Đo nhiệt độ | Cần trở kéo 4.7kΩ |
| 3 | Cảm biến độ ẩm đất | 1 | Đo độ ẩm đất | Ngõ ra Analog A0 |
| 4 | Cảm biến mực nước | 2 | Báo mức nước bồn 1, 2 | Ngõ vào Digital (D5, D6) |
| 5 | Còi báo động (Buzzer) | 1 | Cảnh báo âm thanh | Ngõ ra Digital (D7) |
| 6 | Module Relay / Máy bơm | 3 | Bơm tưới, cấp nước | Ngõ ra Digital (D8, D9, D10) |
| 7 | Quạt làm mát (Fan) | 1 | Thông gió, tản nhiệt | Ngõ ra Digital (D11) |
| 8 | Màn hình LCD 1602 + I2C | 1 | Hiển thị thông số | Địa chỉ `0x27` |
| 9 | Điện trở 4.7kΩ | 1 | Trở kéo DS18B20 | Nối giữa DATA và 5V |

---

## 3. Sơ đồ kết nối chân (Wiring Diagram)

### 3.1. Thiết bị điều khiển (Output)
| Thiết bị | Chân Arduino Uno | Chế độ | Trạng thái ban đầu |
|:---|:---:|:---:|:---:|
| **Còi Buzzer** | **D7** | `OUTPUT` | `LOW` (Tắt) |
| **Máy bơm 1** | **D8** | `OUTPUT` | `LOW` (Tắt) |
| **Máy bơm 2** | **D9** | `OUTPUT` | `LOW` (Tắt) |
| **Máy bơm 3** | **D10** | `OUTPUT` | `LOW` (Tắt) |
| **Quạt** | **D11** | `OUTPUT` | `LOW` (Tắt) |

### 3.2. Cảm biến đầu vào (Input)
| Cảm biến | Chân Arduino Uno | Chế độ | Ghi chú |
|:---|:---:|:---:|:---|
| **Cảm biến nhiệt độ DS18B20** | **D2** | 1-Wire | Có trở kéo 4.7kΩ lên 5V |
| **Cảm biến mực nước 1** | **D5** | `INPUT` | Đọc mức nước bồn 1 |
| **Cảm biến mực nước 2** | **D6** | `INPUT` | Đọc mức nước bồn 2 |
| **Cảm biến độ ẩm đất** | **A0** | `INPUT` (Analog) | Đọc dải điện áp $680 - 2189\text{ mV}$ |

### 3.3. Màn hình LCD 16x2 (I2C)
| Chân Module I2C | Chân Arduino Uno |
|:---|:---|
| `GND` | `GND` |
| `VCC` | `5V` |
| `SDA` | `A4` |
| `SCL` | `A5` |

---

## 4. Nguyên lý tính toán & Hiệu chuẩn độ ẩm

- **Chuyển đổi ADC sang mV:**
  $$\text{Điện áp (mV)} = \frac{\text{val} \times 5000}{1023}$$
- **Hiệu chuẩn độ ẩm (%):**
  - Khô (không có nước): $2189\text{ mV} \rightarrow 0\%$
  - Ngập nước hoàn toàn: $680\text{ mV} \rightarrow 100\%$
  - Ánh xạ: `percent = constrain(map(voltage_mV, 2189, 680, 0, 100), 0, 100)`

---

## 5. Tùy chỉnh thông số hệ thống (`setting.h`)
Các ngưỡng điều khiển tự động được đặt trong file [`setting.h`](setting.h) để dễ dàng thay đổi:
- `TEMP_FAN_ON = 35.0` (°C): Ngưỡng nhiệt độ bật quạt.
- `TEMP_FAN_OFF = 30.0` (°C): Ngưỡng nhiệt độ tắt quạt.
- `MOISTURE_PUMP3_ON = 10` (%): Ngưỡng độ ẩm đất bật bơm 3 tưới.
- `MOISTURE_PUMP3_OFF = 50` (%): Ngưỡng độ ẩm đất dừng bơm 3.

---

## 6. Thư viện cần cài đặt
Cài đặt qua Arduino IDE Library Manager:
1. `DallasTemperature`
2. `OneWire`
3. `LiquidCrystal_I2C`

