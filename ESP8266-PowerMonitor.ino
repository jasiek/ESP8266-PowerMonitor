#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "statsd.h"
#include "settings.h"
#include "string.h"

OneWire bus(4); // Use GPIO4 as it is not connected to any peripherals
DallasTemperature sensors(&bus);

int movementCounter;
int energyCounter;
int errorCount;
unsigned long pulseStartTime;
unsigned long pulseWidth;

char _metricLabel[64];

void recordPulse();
void recordMovement();
void report();
bool maybeReconnect();

StatsD sclient(STATSD_IP, STATSD_PORT, 31337);
String nodeName;

ADC_MODE(ADC_VCC);

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  maybeReconnect();
  determineNodeName();
  // When there's a pulse, increment the counter.
  pulseStartTime = millis();
  pinMode(5, INPUT);
  pinMode(15, INPUT);
  pinMode(16, OUTPUT); // Used for signalling errors
  attachInterrupt(15, pulseRise, RISING);
  attachInterrupt(5, recordMovement, RISING);
}

void error(int num) {
  int i = 0;
  digitalWrite(16, HIGH);
  while (1) {
    for (i = 0; i < num; i++) {
      digitalWrite(16, LOW);
      delay(100);
      digitalWrite(16, HIGH);
      delay(100);
    }

    delay(5000);
  }
}

void loop() {
  sensors.begin();
  if (sensors.getDeviceCount() < 1) {
    error(1);
  }
  
  sensors.requestTemperatures();
  delay(1000);
  report();
  delay(10000);
}

void recordMovement() {
  movementCounter++;
}

void pulseRise() {
  // are we rising or falling?
  unsigned long now = millis();
  pulseStartTime = now;
  attachInterrupt(15, pulseFall, FALLING);
}

void pulseFall() {
  unsigned long now = millis();
  pulseWidth = now - pulseStartTime;
  if (pulseWidth > 80 && pulseWidth < 100) {
    // workaround?
    energyCounter++;
  }
  attachInterrupt(15, pulseRise, RISING);
}

const char *metricLabel(const char *label) {
  memset(_metricLabel, 0, 64);
  strcpy(_metricLabel, nodeName.c_str());
  strcat(_metricLabel, ".");
  strcat(_metricLabel, label);
  return _metricLabel;
}

void reportTemperature() {
  float temp = sensors.getTempCByIndex(0);
  Serial.println("temperature: " + String(temp));
  sclient.gauge(metricLabel("temperature"), 0);
  sclient.gauge(metricLabel("temperature"), temp);
}

void reportPulses() {
  sclient.gauge(metricLabel("wattHour"), energyCounter);
  Serial.println("energy: " + String(energyCounter) + " Wh");
  energyCounter = 0;
}

void reportMovement() {
  Serial.print("Movements: ");
  Serial.println(movementCounter);
  sclient.gauge(metricLabel("movement"), movementCounter);
  movementCounter = 0;
}

void reportRSSI() {
  int rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.println(rssi);
  sclient.gauge(metricLabel("rssi"), 0);
  sclient.gauge(metricLabel("rssi"), rssi);
}

void reportVoltage() {
  float voltage = ESP.getVcc() / 1000.0;
  Serial.print("voltage: ");
  Serial.println(voltage);
  sclient.gauge(metricLabel("voltage"), voltage);
}

void incrementDataCounter() {
  sclient.increment(metricLabel("packets"));
}

void report() {
  if (maybeReconnect()) {
    Serial.println(millis());
    Serial.println("Sending data");
    reportTemperature();
    reportPulses();
    reportMovement();
    reportRSSI();
    reportVoltage();
    incrementDataCounter();
  }
}

bool maybeReconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("(Re)connecting to network: ");  
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    WiFi.mode(WIFI_STA);
  } else {
    Serial.println("Already connected to network");
    return true;
  }
  for (int i = 0; i < 30 && (WiFi.status() != WL_CONNECTED); i++) {
    Serial.print(".");
    delay(1000);
  }
  bool success = (WiFi.status() == WL_CONNECTED);
  if (success) {
    Serial.print("connected, got IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Could not connect");
  }
  return success;
}

void determineNodeName() {
  nodeName = WiFi.macAddress();
  for (int i = nodeName.indexOf(':'); i > -1; i = nodeName.indexOf(':')) nodeName.remove(i, 1);
  nodeName.toLowerCase();

  Serial.print("Node name: ");
  Serial.println(nodeName);

  MDNS.begin(nodeName.c_str());
  MDNS.addService("http", "tcp", 80);
}
