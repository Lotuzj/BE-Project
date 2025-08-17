#include <TFT_eSPI.h>
#include <SPI.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

TFT_eSPI tft = TFT_eSPI();

// Pin Definitions
const int buttonPin = 25;
const int mq2Pin = 34;     // Analog pin for MQ2
const int pulsePin = 36;   // Analog pin for X58C Pulse Sensor

HardwareSerial GPS(2);     // Use UART2 for GPS (Neo6M)
TinyGPSPlus gps;

bool alertShown = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  analogReadResolution(12); // ESP32 ADC resolution
  GPS.begin(9600, SERIAL_8N1, 16, 17); // RX = GPIO16, TX = GPIO17

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Kaho krejaa!", tft.width()/2, 20, 4);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    delay(50);
    if (!alertShown) {
      showAlert();
      alertShown = true;
    }
  } else {
    if (alertShown) {
      alertShown = false;
    }
    showSensorData();
  }

  // Read GPS data continuously
  while (GPS.available()) {
    gps.encode(GPS.read());
  }
}

void showAlert() {
  tft.fillScreen(TFT_RED);
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("ALERT TRIGGERED!", tft.width()/2, tft.height()/2, 4);
}

void showSensorData() {
  int mq2Value = analogRead(mq2Pin);
  int pulseValue = analogRead(pulsePin);

  String lat = gps.location.isValid() ? String(gps.location.lat(), 6) : "No Fix";
  String lng = gps.location.isValid() ? String(gps.location.lng(), 6) : "No Fix";

  tft.fillRect(0, 40, 320, 200, TFT_WHITE); // Clear sensor area
  tft.setTextDatum(TL_DATUM); // Top-left alignment
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  tft.drawString("Gas (MQ2): " + String(mq2Value), 10, 50, 2);
  tft.drawString("Pulse (X58C): " + String(pulseValue), 10, 80, 2);
  tft.drawString("GPS Lat: " + lat, 10, 110, 2);
  tft.drawString("GPS Lng: " + lng, 10, 140, 2);

  delay(500); // Update interval
}
