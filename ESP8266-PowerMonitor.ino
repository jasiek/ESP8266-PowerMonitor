#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecure.h>
#include "settings.h"

OneWire bus(0);
DallasTemperature sensors(&bus);

unsigned int movementCounter;
unsigned int energyCounter;
unsigned long pulseStartTime;
unsigned long pulseWidth;

void pulse_CHANGE();
void recordMovement();

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to network: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(WiFi.localIP());

  // When there's a pulse, increment the counter.
  pulseStartTime = millis();
  pinMode(5, INPUT);
  pinMode(15, INPUT);
  attachInterrupt(15, pulse_CHANGE, CHANGE);
  attachInterrupt(5, recordMovement, RISING);
}

void loop() {
  Serial.println(millis());
  Serial.println(energyCounter);
  Serial.println(movementCounter);
  sensors.requestTemperatures();
  delay(1000);
  Serial.println(sensors.getTempCByIndex(0));
  Serial.println();
}

void recordMovement() {
  movementCounter++;
}

void pulse_CHANGE() {
  // are we rising or falling?
  unsigned long now = millis();
  if (digitalRead(15) == 1) {
    // rising
    pulseStartTime = now;
  } else {
    // falling
    pulseWidth = now - pulseStartTime;
    if (pulseWidth > 80 && pulseWidth < 100) {
      // workaround?
      pulseStartTime = now;
      energyCounter++;
    }
  }
}

float readTemperature() {
}

