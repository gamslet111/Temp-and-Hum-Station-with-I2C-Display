# ESP32 Temperature and Humidity Monitor

![Front](Docs/Pictures/front.jpg)
![Front](Docs/Pictures/back.jpg)

## Parts

- ESP32 Dev Kit (e.g., AZ-Delivery DevKit V4) - [Link to ESP32]
- DHT11 Sensor - [Link to DHT11]
- 16x2 I2C LCD (Address 0x27) - [Link to I2C LCD]
- Resistors and Wires - [Link to Resistors/Wires]
- Breadboard - [Link to Breadboard]
- Power Supply (5V) - [Link to Power Supply]

## 3D Prints

Case and other 3D printed parts are located in `Docs/3D-Prints/`.

## Features
- Reads temperature and humidity from DHT11 sensor.
- Displays data on a 16x2 I2C LCD (address 0x27).
- Enters deep sleep mode for 60 seconds after each measurement.
- Outputs data to serial monitor for debugging.

## Hardware Requirements
- ESP32 Dev Kit (e.g., AZ-Delivery DevKit V4).
- DHT11 sensor connected to GPIO 4.
- 16x2 I2C LCD connected to SDA (GPIO 21) and SCL (GPIO 22).
- Power supply: 5V via VIN pin or USB.

## Wiring
- **DHT11 Sensor**:
  - Data pin → GPIO 4 (ESP32)
  - VCC → 3.3V (ESP32)
  - GND → GND (ESP32)
- **16x2 I2C LCD**:
  - SDA → GPIO 21 (ESP32)
  - SCL → GPIO 22 (ESP32)
  - VCC → 3.3V (ESP32)
  - GND → GND (ESP32)
- **ESP32 Power Supply**:
  - Connect 5V from a lab power supply to VIN pin (ESP32) for external power.

## Software Requirements
- PlatformIO with Arduino framework.
- Libraries: DHT sensor library, LiquidCrystal_I2C.

## Setup
1. Clone the repository.
2. Open in PlatformIO.
3. Upload the code to the ESP32.
4. Monitor serial output for data.

## Usage
The ESP32 wakes up every 60 seconds, measures data, displays it on the LCD, and sleeps again.
