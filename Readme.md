
# 👶 Baby Care System with ESP32

An IoT-based smart baby monitoring and cradle control system using ESP32, Blynk, DHT22, MPU6050, and Servo motor.

---

## 📌 Features

- 🍼 Detects baby's **cry status** (via serial input for demo purposes).
- 🛏️ Detects **movement** using the MPU6050 (accelerometer + gyroscope).
- 🌡️ Monitors **temperature and humidity** using DHT22.
- 📱 Displays real-time status and environment data on **Blynk mobile app**.
- 🤖 Automatically swings the cradle when toggled via the app.

---

## 🛠️ Components Used

- ESP32 Dev Board  
- DHT22 (Temperature and Humidity sensor)  
- MPU6050 (Accelerometer + Gyroscope)  
- Servo Motor (for cradle swing)  
- Blynk App (ESP32 support)  
- USB Serial Monitor (for cry detection simulation)

---

## 📲 Blynk Configuration

- **Template ID**: `TMPL3Y2oN4mEB`  
- **Template Name**: `baby care`  
- **Auth Token**: Replace with your own token if deploying.

**Virtual Pins Used**:
- `V2` → Baby status (`Crying`, `Moving`, `Sleeping`)  
- `V6` → Swing toggle switch  
- `V7` → Temperature  
- `V8` → Humidity  

---

## 📶 Wi-Fi Settings

Update these credentials in your code:

```cpp
char ssid[] = "Your-WiFi-SSID";
char pass[] = "Your-WiFi-Password";
```

---

## 🧪 How to Simulate Baby Cry

Use Serial Monitor:
- Type `cry` → Status changes to “Crying”
- Type `sleep` → Status changes to “Sleeping”

---

## 🧠 Logic Summary

- Reads **accelerometer and gyroscope** data to detect motion.
- Uses **DHT22** to get environmental conditions.
- Swings the cradle using **Servo motor** if `V6` switch is ON in Blynk.
- Sends baby status to Blynk via `V2`.

---

## 🧾 Dependencies

Install these libraries via Arduino IDE Library Manager:
- `Blynk`
- `DHT sensor library`
- `Adafruit Unified Sensor`
- `ESP32Servo`
- `MPU6050` or `I2Cdevlib` MPU6050

---

## ✅ Future Improvements

- Replace Serial-based cry detection with **sound sensor** or **ML model**.
- Add notifications/alerts via **Blynk or email**.
- Enable **auto-swinging** when crying is detected.
