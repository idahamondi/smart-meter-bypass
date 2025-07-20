# Smart Meter Bypass Detection System

This project simulates a **Smart Electricity Meter Bypass Detection System** using an **ESP32**, **OLED display**, **buzzer**, **LED**, and **potentiometers**.  
It was designed and tested entirely on [Wokwi](https://wokwi.com/), an online microcontroller simulator.

---

## 🚀 Features
- 📟 Detects when **load current** exceeds **meter current + tolerance**.
- 🔴 Visual alert: LED lights up.
- 🔊 Audible alert: Buzzer sounds.
- 📋 OLED screen displays meter, load, threshold & status.
- 🖥 Logs real-time data to Serial Monitor.
- 🛠 Fully simulated with potentiometers substituting for current sensors.

---

## 📝 Files in this Repository
| File | Description |
|------|-------------|
| `sketch.ino` | Arduino code for ESP32 |
| `diagram.json` | Wokwi circuit diagram |
| `.wokwi/` | Wokwi metadata |

---

## 🔷 How to Run on Wokwi
✅ Download or clone this repository.  
✅ Open [https://wokwi.com](https://wokwi.com).  
✅ Click **Open Project**.  
✅ Select the `diagram.json` file from this repo.  
✅ Click **Start Simulation**.  
✅ Watch the Serial Monitor and OLED, adjust potentiometers to trigger alerts.

---

## 📚 Components Simulated
- ESP32 Dev Module
- 2x Potentiometers (simulate current sensors)
- LED
- Buzzer
- SSD1306 OLED display

---

## 👤 Author
Idah Amondi  
Project: Final Year Project Idea — Embedded Systems & Digital Electronics  
Date: 2025

---
