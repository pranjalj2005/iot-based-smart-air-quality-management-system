# IoT-Based Smart Air Quality Management System

## Overview
This project is an IoT-based Smart Air Quality Management System developed using ESP32 for real-time air quality monitoring and automated air purification. The system monitors environmental parameters such as air quality, gas concentration, temperature, humidity, and dust levels using multiple sensors.

Based on AQI levels, the system automatically controls the purification system and provides live monitoring through LCD display and Blynk IoT platform.

---

## Features

- Real-time AQI monitoring
- Gas and dust detection
- Temperature and humidity monitoring
- Automated air purification control
- LCD live status display
- Blynk IoT cloud monitoring
- ESP32 WiFi connectivity
- LED air quality indication system

---

## Components Used

| Component | Description |
|---|---|
| ESP32 | Main microcontroller |
| MQ Gas Sensor | Gas detection |
| Dust Sensor | Dust monitoring |
| DHT11 | Temperature & humidity sensor |
| Relay Module | Controls purifier/fan |
| I2C LCD | Live data display |
| LEDs | AQI indication |
| Blynk IoT | Cloud monitoring |

---

## Working Principle

The ESP32 continuously reads data from gas, dust, and DHT11 sensors. Based on the detected AQI level, the system classifies air quality into Good, Moderate, or Poor categories.

When poor air quality is detected, the automated air purification system activates through relay-controlled fan operation. The sensor data is displayed on the LCD and simultaneously transmitted to the Blynk cloud platform for remote monitoring.

---

## AQI Classification

| AQI Range | Status |
|---|---|
| 0–99 | Good |
| 100–199 | Moderate |
| 200+ | Poor |

---

## Technologies Used

- Embedded C++
- Arduino IDE
- ESP32
- IoT
- Blynk Cloud
- Sensor Interfacing

---

## Project Images

### Prototype

![Prototype](images/prototype.jpg)

### LCD Output

![LCD](images/lcd_output.jpg)

### Blynk Dashboard

![Dashboard](images/blynk_dashboard.jpg)

---

## Future Improvements

- Real AQI calibration
- PCB design implementation
- Mobile app integration
- Data logging and analytics
- HEPA filter integration
- AI-based air quality prediction
- Low-power optimization

---

## GitHub Repository Structure

```text
iot-based-smart-air-quality-management-system/
│
├── README.md
├── air_quality_management_system.ino
├── images/
├── circuit_diagram.png
└── LICENSE
```

---

## Author

Pranjal Jawalkar 

---

## License

This project is licensed under the MIT License.
