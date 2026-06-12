<h1 align="center">ESP32 Air Mouse Gloves</h1>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-brightgreen.svg" alt="ESP32">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue.svg" alt="C++">
  <img src="https://img.shields.io/badge/Framework-Arduino-00979D.svg" alt="Arduino">
  <img src="https://img.shields.io/badge/Sensor-MPU6050-orange.svg" alt="MPU6050">
  <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT">
</p>

<p align="center">
  A high-performance, wearable Bluetooth Air Mouse built with an ESP32 and MPU6050 gyroscope/accelerometer. Designed for seamless cursor control using hand gestures, it features click buttons, an absolute-center calibration system, and is optimized for both computer and mobile devices.
</p>

## 🎥 Demo Video

<p align="center">
  <a href="https://youtube.com/shorts/1UzFhFmE274">
    <img src="https://img.youtube.com/vi/1UzFhFmE274/maxresdefault.jpg" alt="ESP32 Air Mouse Gloves Demo" width="800">
  </a>
</p>

<p align="center">
  <b>🎥 Watch the Project Demo</b>
</p>

## 🛠 Features

- **Gesture Control:** Move your hand to control the cursor with zero lag.
- **Left & Right Click:** Physical buttons mapped directly to standard mouse clicks.
- **Smart Calibration:** Hold the calibration button for 3 seconds to cancel sensor drift and instantly snap the cursor to the center of the screen.
- **Universal Compatibility:** Works as a standard Bluetooth HID mouse on Windows, macOS, Linux, and Android.
- **Gaming Optimized:** Tuned sensitivity and deadzones for precise aiming and shooting in fast-paced mobile games.

## 📦 Repository Structure

- `AirMouseGloves.ino` - The main Arduino code for the ESP32.
- `README.md` - Documentation and instructions.
- `/library/ESP32-BLE-Mouse-master-(Modified by Rahat0764).zip` - A modified version of the standard BLE Mouse library (fixes string and BLE descriptor issues).
- `/res/demo_video.mp4` - Video demonstration of the gloves in action.

## 🔌 Hardware Requirements

To build this project, you will need the following components:

1. **ESP32 Development Board** (30-pin or 38-pin)
2. **MPU6050 Module** (Gyroscope + Accelerometer)
3. **TP4056 Module** (Lithium Battery Charging Board with Protection)
4. **3.7V Li-ion/Li-Po Battery**
5. **3x Push Buttons** (4-pin tact switches for Left, Right, and Calibration)
6. **1x Slide Switch** (3-position switch for Main Power)
7. **Jumper wires and a Glove**

## ⚙️ Circuit Connections

### 1. Power System (Battery & TP4056)
- Battery (+) ➔ TP4056 `B+`
- Battery (-) ➔ TP4056 `B-`
- TP4056 `OUT+` ➔ Main Switch (Center Pin)
- Main Switch (Side Pin) ➔ ESP32 `3V3` *(Avoid using VIN to prevent voltage drops from a 3.7V source)*

### 2. Common Ground (GND) Line
Connect all the following to a single common wire, and connect the end of that wire to the ESP32 `GND` pin:
- TP4056 `OUT-`
- MPU6050 `GND`
- MPU6050 `AD0`
- One diagonal pin of the Left button
- One diagonal pin of the Right button
- One diagonal pin of the Calibration button

### 3. Sensor (MPU6050)
- `VCC` ➔ ESP32 `3V3`
- `SCL` ➔ ESP32 `GPIO 22`
- `SDA` ➔ ESP32 `GPIO 21`

### 4. Action Buttons (Use diagonally opposite pins)
- **Left Click:** Remaining pin ➔ ESP32 `GPIO 18`
- **Right Click:** Remaining pin ➔ ESP32 `GPIO 19`
- **Calibration:** Remaining pin ➔ ESP32 `GPIO 5`

## 🚀 Installation & Setup

### Step 1: Install the Modified Library
The standard BLE Mouse library has known issues with certain string formats on modern ESP32 board managers. 
1. Go to the [Releases section](https://github.com/Rahat0764/ESP32AirMouseGloves/releases) of this repository.
2. Download `ESP32-BLE-Mouse-master-(Modified by Rahat0764).zip`.
3. In your Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...** and select the downloaded file.

### Step 2: Upload the Code
1. Open `AirMouseGloves.ino` in the Arduino IDE (or ArduinoDroid).
2. Ensure your ESP32 board is selected.
3. **Important:** Turn OFF the main battery switch of your glove before plugging the ESP32 into your PC/Phone via USB to avoid power conflicts.
4. Click Upload. (Press the BOOT button on the ESP32 when "Connecting..." appears if your board requires it).

## 🎮 How to Use

### Desktop / PC
1. Turn on the glove using the main switch.
2. Open Bluetooth settings on your PC and pair with **"Cyber Glove"**.
3. Hold your hand steady and press the **Calibration Button for 3 seconds**. The cursor will snap to the center of your screen.
4. Move your hand to move the cursor. Use the buttons to click.

### Mobile Gaming (e.g., PUBG on Android)
To use this glove for FPS games on your phone, you need a Keymapper app to map the mouse clicks to on-screen buttons.
1. Connect "Cyber Glove" via Bluetooth.
2. Install a Keymapper app that supports Mice (e.g., **Mantis Mouse Pro** or **Panda Mouse Pro**). *Note: Mantis Gamepad Pro will not work as it only detects gamepads.*
3. Open the Keymapper app and launch your game.
4. Map the **Left Click** to your Fire button, and **Right Click** to your Reload (or Scope) button.
5. Aim by moving your hand, shoot by clicking!

## 👨‍💻 Author

**Rahat Ahmed**
- LinkedIn: [RahatAhmedX](https://www.linkedin.com/in/RahatAhmedX)
- GitHub: [@Rahat0764](https://github.com/Rahat0764)

---
*If you find this project helpful, don't forget to give it a ⭐!*