#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ESP32 pins
const int meterSensorPin = 34;   // ADC pin for meter potentiometer
const int loadSensorPin  = 35;   // ADC pin for load potentiometer
const int ledPin          = 2;   // LED pin
const int buzzerPin       = 4;   // Buzzer pin

float tolerance = 0.5;           // Amps allowed difference

float meterCurrent = 0;
float loadCurrent = 0;

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Meter Bypass");
  display.display();
  delay(1500);
}

void loop() {
  meterCurrent = readCurrent(meterSensorPin);
  loadCurrent  = readCurrent(loadSensorPin);

  Serial.print("Meter: ");
  Serial.print(meterCurrent, 2);
  Serial.print(" A | Load: ");
  Serial.print(loadCurrent, 2);
  Serial.print(" A | Threshold: ");
  Serial.print(meterCurrent + tolerance, 2);

  // Check condition
  if (loadCurrent > (meterCurrent + tolerance)) {
    Serial.println(" --> ⚠️ BYPASS DETECTED!");
    triggerAlert();
    updateOLED("BYPASS DETECTED!", true);
  } else {
    Serial.println(" --> ✅ Normal");
    noAlert();
    updateOLED("Normal", false);
  }

  delay(1000);
}

// Simulate current (0-10A) from potentiometer voltage
float readCurrent(int pin) {
  int raw = analogRead(pin);
  float voltage = (raw / 4095.0) * 3.3;   // ADC to volts
  float current = (voltage / 3.3) * 10.0; // Map 0–3.3V → 0–10A
  return current;
}

void triggerAlert() {
  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, 1000); // play 1kHz tone
}

void noAlert() {
  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);     // stop tone
}

void updateOLED(String statusMsg, bool alert) {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.print("Meter: ");
  display.print(meterCurrent, 1);
  display.println(" A");

  display.print("Load: ");
  display.print(loadCurrent, 1);
  display.println(" A");

  display.print("Thresh: ");
  display.print(meterCurrent + tolerance, 1);
  display.println(" A");

  display.println("--------------------");

  if (alert) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // inverted
  } else {
    display.setTextColor(SSD1306_WHITE);
  }

  display.setCursor(0, 48);
  display.println(statusMsg);
  display.display();
}
