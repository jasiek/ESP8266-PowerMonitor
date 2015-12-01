#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecure.h>
#include "settings.h"

int counter;

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
  pinMode(16, INPUT_PULLUP);
  attachInterrupt(16, pulse_ISR, RISING);
}

void loop() {
  noInterrupts();

  counter = 0;
  interrupts();
  delay(5 * 60 * 1000); // every 5 minutes
}

void pulse_ISR(void) {
  counter++;
}

