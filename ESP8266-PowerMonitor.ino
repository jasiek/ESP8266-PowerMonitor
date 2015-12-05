#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecure.h>
#include "settings.h"

volatile int counter;
volatile unsigned long pulseStartTime;
volatile unsigned long pulseWidth;

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
  pinMode(15, INPUT);
  attachInterrupt(15, pulse_CHANGE, CHANGE);
}

void loop() {
  delay(1000);
  Serial.print(counter);
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
    if (pulseWidth > 80) counter++;
  }
}

