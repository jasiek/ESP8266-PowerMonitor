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
unsigned int errorCount;
unsigned long pulseStartTime;
unsigned long pulseWidth;

void recordPulse();
void recordMovement();
void report();

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
  attachInterrupt(15, recordPulse, CHANGE);
  attachInterrupt(5, recordMovement, RISING);
}

void loop() {
  sensors.requestTemperatures();
  delay(1000);
  report();
  delay(5 * 60 * 1000);
}

void recordMovement() {
  movementCounter++;
}

void recordPulse() {
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

void report() {
  float temp = sensors.getTempCByIndex(0);
  String url = String(DATA_PATH) + "&temp=" + String(temp) 
    + "&moves=" + String(movementCounter)
    + "&pulses=" + String(energyCounter) 
    + "&errors=" + String(errorCount);
  
  WiFiClientSecure client;
  if (client.connect(DATA_HOST, DATA_PORT)) {
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
      "Host: data.sparkfun.com\r\n" +
      "User-Agent: ESP8266-PowerMonitor\r\n" +
      "Connection: close\r\n\r\n");
       Serial.println("Sent request");
  
      bool success = false;
  
      while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line.startsWith("1 success")) {
          success = true;
          break;
        }
      }
      if (success) {
        energyCounter = 0;
        movementCounter = 0;
        errorCount = 0;
        Serial.println("Data sent successfully");
      } else {
        Serial.println("An error occured");
        errorCount++;
      }
    } else {
      Serial.println("Could not connect, will try later");
    }
}


