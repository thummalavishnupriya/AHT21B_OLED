#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#include <Adafruit_AHTX0.h>
Adafruit_AHTX0 aht;

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT21B found");
  display.begin(i2c_Address, 0x3C); // Address 0x3C default
  display.clearDisplay();
}

void loop() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(" Air Quality Analyser");
  display.setCursor(65,25);
  display.println("Temp: ");
  display.setCursor(65,40);
  display.println("Hum : ");
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println("C");
  display.setCursor(95,25);
  display.println(temp.temperature);
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("%");
  display.setCursor(95,40);
  display.println(humidity.relative_humidity);
  display.display();
  delay(1000);
  display.clearDisplay();
}
