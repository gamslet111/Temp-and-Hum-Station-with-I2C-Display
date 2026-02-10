#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#include "config.h"

// Pins and configuration
#define DHTPIN 4
#define DHTTYPE DHT11
#define SLEEP_TIME 60 * 1000000ULL
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init();
  delay(1000);
  lcd.backlight();
  Serial.println(F("LCD initialized"));

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("WiFi connected");

  // Configure Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failure with DHT11!");
    return;
  }

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.printf("Temp: %.1f C", temp);
  lcd.setCursor(0, 1);
  lcd.printf("Hum: %.1f %%", hum);

  // Send to Firebase
  if (Firebase.setFloat(firebaseData, "/sensor/temp", temp) &&
      Firebase.setFloat(firebaseData, "/sensor/hum", hum)) {
    Serial.println("Data sent to Firebase");
  } else {
    Serial.println("Error sending: " + firebaseData.errorReason());
  }

  // Deep Sleep
  esp_sleep_enable_timer_wakeup(SLEEP_TIME);
  esp_deep_sleep_start();
}
