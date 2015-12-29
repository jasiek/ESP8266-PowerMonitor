#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "statsd.h"
#include "settings.h"
#include "string.h"

OneWire bus(0);
DallasTemperature sensors(&bus);

unsigned int movementCounter;
unsigned int energyCounter;
unsigned int errorCount;
unsigned long pulseStartTime;
unsigned long pulseWidth;

char _metricLabel[64];

void recordPulse();
void recordMovement();
void report();

StatsD sclient(STATSD_IP, STATSD_PORT, 31337);

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
  delay(10000);
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

const char *metricLabel(const char *label) {
  memset(_metricLabel, 0, 64);
  strcpy(_metricLabel, NODE_NAME);
  strcat(_metricLabel, ".");
  strcat(_metricLabel, label);
  return _metricLabel;
}

void reportTemperature() {
  float temp = sensors.getTempCByIndex(0);
  Serial.println("temperature: " + String(temp));
  sclient.gauge(metricLabel("temperature"), temp);
}

void reportPulses() {
  sclient.gauge(metricLabel("wattHour"), energyCounter);
  Serial.println("energy: " + String(energyCounter) + " Wh");
  energyCounter = 0;
}

void reportMovement() {
  if (movementCounter > 0) {
    Serial.println("movement detected");
    sclient.increment(metricLabel("movementIncrement"));
  }
  movementCounter = 0;
}

void report() {
  Serial.println(millis());
  Serial.println("Sending data");
  reportTemperature();
  reportPulses();
  reportMovement();
}
