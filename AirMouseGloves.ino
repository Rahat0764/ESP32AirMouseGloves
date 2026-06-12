#include <Wire.h>
#include <BleMouse.h>

BleMouse bleMouse("AirMouse", "ESP32", 100);

const int MPU_ADDR = 0x68;
const int SCREEN_W = 1920;
const int SCREEN_H = 1080;
const float SENSITIVITY = 1200.0;
const float SMOOTHING = 0.85;
const float DEADZONE = 0.30;

long gyroOffsetX = 0, gyroOffsetY = 0, gyroOffsetZ = 0;
float smoothVX = 0, smoothVY = 0;
float remX = 0, remY = 0;

const int LEFT_BTN = 18;
const int RIGHT_BTN = 19;
const int CALIB_BTN = 5;

bool leftState = false, rightState = false;
unsigned long calibStartTime = 0;
bool isCalibPressing = false, calibTriggered = false;

void readGyro(int16_t &gx, int16_t &gy, int16_t &gz) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  gx = (int16_t)(Wire.read() << 8 | Wire.read());
  gy = (int16_t)(Wire.read() << 8 | Wire.read());
  gz = (int16_t)(Wire.read() << 8 | Wire.read());
}

void calibrateSensor() {
  long sx = 0, sy = 0, sz = 0;
  int16_t gx, gy, gz;
  for (int i = 0; i < 300; i++) {
    readGyro(gx, gy, gz);
    sx += gx; sy += gy; sz += gz;
    delay(2);
  }
  gyroOffsetX = sx / 300;
  gyroOffsetY = sy / 300;
  gyroOffsetZ = sz / 300;
  smoothVX = smoothVY = 0;
  remX = remY = 0;
}

void moveCursorToCenter() {
  for (int i = 0; i < 60; i++) {
    bleMouse.move(-127, -127);
    delay(8);
  }
  delay(100);
  int cx = SCREEN_W / 2, cy = SCREEN_H / 2;
  while (cx > 0 || cy > 0) {
    int mx = min(cx, 100), my = min(cy, 100);
    bleMouse.move(mx, my);
    cx -= mx; cy -= my;
    delay(8);
  }
}

void setup() {
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  pinMode(CALIB_BTN, INPUT_PULLUP);
  Wire.begin(21, 22);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  delay(500);
  calibrateSensor();
  bleMouse.begin();
}

void loop() {
  if (bleMouse.isConnected()) {
    int16_t GyX, GyY, GyZ;
    readGyro(GyX, GyY, GyZ);
    float rotX = GyX - gyroOffsetX;
    float rotY = GyY - gyroOffsetY;
    float rotZ = GyZ - gyroOffsetZ;
    float vx_raw = (rotX - rotZ) / SENSITIVITY;
    float vy_raw = rotY / SENSITIVITY;
    smoothVX = smoothVX * SMOOTHING + vx_raw * (1.0 - SMOOTHING);
    smoothVY = smoothVY * SMOOTHING + vy_raw * (1.0 - SMOOTHING);
    float ox = (abs(smoothVX) < DEADZONE) ? 0 : smoothVX;
    float oy = (abs(smoothVY) < DEADZONE) ? 0 : smoothVY;
    if (ox == 0 && oy == 0) {
      remX = remY = 0;
    } else {
      remX += ox; remY += oy;
      int mx = (int)remX, my = (int)remY;
      remX -= mx; remY -= my;
      if (mx != 0 || my != 0) {
        bleMouse.move(constrain(mx, -127, 127), constrain(my, -127, 127));
      }
    }
    if (digitalRead(LEFT_BTN) == LOW) {
      if (!leftState) { bleMouse.press(MOUSE_LEFT); leftState = true; }
    } else if (leftState) { bleMouse.release(MOUSE_LEFT); leftState = false; }
    if (digitalRead(RIGHT_BTN) == LOW) {
      if (!rightState) { bleMouse.press(MOUSE_RIGHT); rightState = true; }
    } else if (rightState) { bleMouse.release(MOUSE_RIGHT); rightState = false; }
    if (digitalRead(CALIB_BTN) == LOW) {
      if (!isCalibPressing) {
        isCalibPressing = true;
        calibStartTime = millis();
        calibTriggered = false;
      } else if (millis() - calibStartTime > 3000 && !calibTriggered) {
        calibrateSensor();
        moveCursorToCenter();
        calibTriggered = true;
      }
    } else {
      isCalibPressing = false;
    }
  }
  delay(10);
}