#define BLYNK_TEMPLATE_ID "TMPL3Y2oN4mEB"
#define BLYNK_TEMPLATE_NAME "baby care"
#define BLYNK_AUTH_TOKEN "LY36RWAyM2D9gFjvqb9I64jjHe46t-Cl"

#include <WiFi.h>
#include <Wire.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include "MPU6050.h"

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define DHTPIN 19       
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Servo cradleServo;
#define SERVOPIN 15

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

bool swing = false;
String cryStatus = "Sleeping";
String movementStatus = "Baby Sleeping";

BLYNK_WRITE(V6) {
  swing = param.asInt();
}

void swingCradle() {
  cradleServo.write(45);
  delay(100);
  cradleServo.write(135);
  delay(100);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  Wire.begin();
  mpu.initialize();
  cradleServo.setPeriodHertz(50);
  cradleServo.attach(SERVOPIN, 500, 2400);
}

void loop() {
  Blynk.run();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input == "cry") {
      cryStatus = "Crying";
      Serial.println("Baby is crying");
    } else if (input == "sleep") {
      cryStatus = "Sleeping";
      Serial.println("Baby is sleeping");
    } else {
      Serial.println("Unknown input. Type 'cry' or 'sleep'");
    }
  }

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  Blynk.virtualWrite(V7, temp);
  Blynk.virtualWrite(V8, hum);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C, Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  // Read sensor values
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  // Convert to units
  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  float gx_d = gx / 131.0;
  float gy_d = gy / 131.0;
  float gz_d = gz / 131.0;

  // Print raw values
  Serial.print("Accel (g): X=");
  Serial.print(ax_g);
  Serial.print(" Y=");
  Serial.print(ay_g);
  Serial.print(" Z=");
  Serial.println(az_g);

  Serial.print("Gyro (°/s): X=");
  Serial.print(gx_d);
  Serial.print(" Y=");
  Serial.print(gy_d);
  Serial.print(" Z=");
  Serial.println(gz_d);

  // ✅ Final fix: check only for actual movement
  bool accel_movement = abs(ax_g) > 0.6 || abs(ay_g) > 0.6 || abs(az_g) > 1.2;
  bool gyro_movement = abs(gx_d) > 30 || abs(gy_d) > 30 || abs(gz_d) > 30;

  if (accel_movement || gyro_movement) {
    movementStatus = "Baby Moving";
    Serial.println("Movement detected!");
  } else {
    movementStatus = "Baby Sleeping";
    Serial.println("No significant movement.");
  }

  String combinedStatus;
  if (cryStatus == "Crying") {
    combinedStatus = "Crying";
  } else if (movementStatus == "Baby Moving") {
    combinedStatus = "Baby Moving";
  } else {
    combinedStatus = "Sleeping";
  }

  Blynk.virtualWrite(V2, combinedStatus);

  if (swing) swingCradle();
  else cradleServo.write(90);

  delay(1000);
}
