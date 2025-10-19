# 🌿 Soil Monitoring for Smart Irrigation

This project presents a **smart irrigation system** based on the **ESP32 microcontroller** and **Blynk IoT platform**.  
It automatically monitors soil moisture levels and controls a water pump to maintain optimal soil hydration, promoting efficient water usage in agriculture.

---

## 📘 Overview

Traditional irrigation systems often waste water due to manual operation or overwatering.  
This project introduces an **IoT-enabled soil monitoring system** that:
- Measures soil moisture in real time.  
- Controls a water pump automatically or manually through the **Blynk mobile application**.  
- Sends alerts when the soil becomes too dry.

---

## ⚙️ System Features

- 🌱 **Real-Time Soil Moisture Monitoring**  
  Continuously measures soil moisture using an analog sensor.

- ⚡ **Automatic Pump Control**  
  Activates the water pump when moisture drops below a predefined threshold.

- 🧭 **Dual Operation Modes**  
  - **Auto Mode:** The pump operates automatically based on soil readings.  
  - **Manual Mode:** The user can control the pump remotely using the Blynk app.

- 📱 **IoT Integration**  
  Uses the **Blynk IoT platform** to visualize sensor data and control the pump from anywhere.

- 🔔 **Smart Notifications**  
  Sends alerts when moisture levels fall below the safe threshold.

---

## 🧰 Components Required

| Component | Specification / Function |
|------------|--------------------------|
| **ESP32** | Microcontroller with built-in Wi-Fi |
| **Soil Moisture Sensor** | Detects soil humidity |
| **2-Channel Relay Module** | Controls the water pump |
| **DC Water Pump** | Pumps water to the plants |
| **Connecting Wires** | For circuit connections |
| **Power Supply (5V)** | Provides stable power to ESP32 and sensors |

---

## 🔌 Circuit Connections

| ESP32 Pin | Component | Description |
|------------|------------|-------------|
| GPIO 34 | Soil Moisture Sensor (Analog Output) | Sensor reading input |
| GPIO 25 | Relay IN1 | Controls the water pump |
| 3.3V | Sensor VCC | Power supply for sensor |
| GND | Common Ground | Shared for all components |

⚠️ **Note:** Avoid using a 9V battery. Use a USB cable or 5V adapter for stable operation.

---

## 💡 Working Principle

1. The soil moisture sensor provides an analog output proportional to soil humidity.  
2. The ESP32 converts this reading to a percentage using calibration values.  
3. If the moisture percentage falls below the threshold (e.g., 40%), the system activates the pump automatically.  
4. In **manual mode**, users can toggle the pump directly from the Blynk app.  
5. The Blynk dashboard displays real-time moisture data and system status.

---

## 📱 Blynk IoT Setup

1. Open [Blynk Cloud](https://blynk.cloud/) and create a new template:  
   - **Template Name:** Soil Monitoring for Smart Irrigation  
   - **Device Type:** ESP32  

2. Add the following **Data Streams (Virtual Pins):**
   | Function | Virtual Pin |
   |-----------|--------------|
   | Mode Switch (Auto/Manual) | V4 |
   | Soil Moisture (%) | V5 |
   | Pump Control | V6 |

3. Copy the following from your Blynk template:
   - **Template ID**
   - **Auth Token**

4. Paste these values into the Arduino code before uploading.

---

## 🧾 Code Summary

The main program performs the following:
- Reads soil moisture values using the ADC pin.
- Converts raw readings into percentage.
- Operates in either **Auto** or **Manual** mode.
- Sends live data to the Blynk dashboard every 3 seconds.
- Controls the relay for pump activation.
- Generates Blynk notifications for low moisture alerts.

---

## 🔋 Power Requirements

- Recommended: **5V USB** or **5V 1A DC adapter**  
- Avoid 9V rectangular batteries (insufficient current for Wi-Fi operations)

---

## 🧠 Future Improvements

- Integration of **temperature and humidity sensors** (DHT11/DHT22).  
- **Data logging** on cloud platforms like ThingSpeak.  
- **Mobile app automation** for irrigation schedules.  
- Solar-powered operation for sustainable farming.

---

## 👩‍💻 Contributers

**Pooja S Nair**
**Nidhi T Aneesh**
**Anvi Elsa Vijo**
Electronics and Computer Engineering
Smart IoT Project – Soil Monitoring for Smart Irrigation  

---



Would you like me to include a **diagram section (block or circuit diagram placeholders)** for your GitHub page too? It makes it look more complete for academic or competition submissions.
