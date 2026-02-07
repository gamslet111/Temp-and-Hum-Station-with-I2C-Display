#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define SLEEP_TIME 60 * 1000000ULL

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init();
  delay(1000);
  lcd.backlight();
  Serial.println(F("LCD initialized"));
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Fehler beim Lesen des DHT-Sensors!");
    return;
  }

  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.print(" °C, Feuchtigkeit: ");
  Serial.print(hum);
  Serial.println(" %");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.printf("Temp: %.1f C", temp);
  lcd.setCursor(0, 1);
  lcd.printf("Hume: %.1f %%", hum);

  esp_sleep_enable_timer_wakeup(SLEEP_TIME);
  esp_deep_sleep_start();
}
