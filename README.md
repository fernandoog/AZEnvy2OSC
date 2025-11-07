# AZEnvy2OSC

AZ-Envy Sensors to OSC converter for ESP8266/ESP32.

## Description

This project implements a sensor interface that reads data from AZ-Envy sensors (MQ2 gas sensor and SHT3x temperature/humidity sensor) and sends the data via OSC (Open Sound Control) protocol over WiFi.

## Features

- MQ2 gas sensor support (LPG, CO, smoke detection)
- SHT3x temperature and humidity sensor support
- WiFi connectivity (ESP8266/ESP32)
- OSC protocol communication
- Real-time sensor data transmission

## Hardware Requirements

- ESP8266 or ESP32 development board
- MQ2 gas sensor
- SHT3x temperature/humidity sensor
- WiFi network access

## Libraries Required

- ESP8266WiFi / WiFi (ESP32)
- WiFiUdp
- OSCMessage
- MQ2 library
- SHT3x library

## Installation

1. Install the required libraries in your Arduino IDE:
   - ESP8266WiFi (or WiFi for ESP32)
   - WiFiUdp
   - OSCMessage
   - MQ2 sensor library
   - SHT3x sensor library

2. Configure WiFi credentials in `AzEnvy2OSC.ino`:
```cpp
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
```

3. Configure OSC destination:
```cpp
const IPAddress outIp(192, 168, 43, 1);  // Your computer's IP
const unsigned int outPort = 8000;       // OSC receive port
```

4. Upload the sketch to your ESP8266/ESP32 board.

## Usage

1. Connect the sensors to the appropriate pins (configure `pin` variable for MQ2)
2. Power on the ESP8266/ESP32
3. The device will connect to WiFi and start sending sensor data via OSC
4. Receive OSC messages on your computer at the configured IP and port

## Project Structure

```
AZEnvy2OSC/
├── src/
│   ├── AzEnvy2OSC/          # Main sketch
│   ├── ESP8266sendMessage/   # Example OSC sender
│   ├── MQ2_sample/           # MQ2 sensor example
│   └── SHT3_sample/          # SHT3x sensor example
└── lib/                      # Additional libraries
```

## OSC Message Format

The sensor data is sent as OSC messages with the following format:
- `/sensor/mq2/lpg` - LPG gas level
- `/sensor/mq2/co` - CO gas level
- `/sensor/mq2/smoke` - Smoke level
- `/sensor/sht3x/temperature` - Temperature in Celsius
- `/sensor/sht3x/humidity` - Humidity percentage

## Author

Fernando Ortega Gorrita (@fernandoog)

## License

See LICENSE file for details.
