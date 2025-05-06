#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// --- Definitions ---
#define DHTPIN 2           // DHT22 data pin connected to digital pin 2
#define DHTTYPE DHT22      // We're using a DHT22 sensor

// Initialize the LCD: I2C address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start LCD and sensor
  lcd.begin(16, 2);      // Set up LCD with 16 columns and 2 rows
  lcd.backlight();       // Turn on LCD backlight
  dht.begin();           // Start DHT22 sensor

  // Intro message
  lcd.setCursor(0, 0);
  lcd.print("Reading Sensor");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read temperature and humidity
  float tempC = dht.readTemperature();     // Temperature in Celsius
  float humidity = dht.readHumidity();     // Relative humidity

  // Error checking
  if (isnan(tempC) || isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  // Display temperature on first line
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1); // One decimal place
  lcd.print(" C");

  // Display humidity on second line
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 1);
  lcd.print(" %");

  delay(2000); // Refresh every 2 seconds
}
