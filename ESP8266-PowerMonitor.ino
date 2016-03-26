#include <ArduinoJson.h>
#include <Ticker.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include "IPAddress.h"
#include "settings.h"
#include "string.h"

#define PULSE_PIN 2
#define ONEWIRE_PIN 4
#define PIR_PIN 5
#define LED_PIN 16
// Report frequency is in seconds
#define REPORT_FREQUENCY 300

ADC_MODE(ADC_VCC);

OneWire bus(ONEWIRE_PIN); // Use GPIO4 as it is not connected to any peripherals
DallasTemperature sensors(&bus);
Ticker readAndReport;
ESP8266WiFiMulti WiFiMulti;

String nodeName;
int movementCounter;
int energyCounter;
int errorCounter;
unsigned long pulseStartTime;
unsigned long pulseWidth;
unsigned long packetsSent;
float voltage;
float temperature;
int rssi;

void pulseStart();
void pulseEnd();
void determineNodeName();
void recordMovement();
void report();
void attemptSensorReadAndReport();
void maybeReconnect();

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASS);

  maybeReconnect();
  determineNodeName();
  // When there's a pulse, increment the counter.
  pulseStartTime = millis();
  pinMode(PIR_PIN, INPUT);
  pinMode(PULSE_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); // Used for signalling errors
  digitalWrite(LED_PIN, HIGH);
  attachInterrupt(PULSE_PIN, pulseStart, FALLING);
  attachInterrupt(PIR_PIN, recordMovement, RISING);
  attemptSensorReadAndReport();
}

void error(int num) {
  int i = 0;
  digitalWrite(LED_PIN, HIGH);
  for (i = 0; i < num; i++) {
    digitalWrite(LED_PIN, LOW);
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
  }
}

void loop() {
}

void recordMovement() {
  movementCounter++;
}

void pulseStart() {
  // are we rising or falling?
  unsigned long now = millis();
  pulseStartTime = now;
  attachInterrupt(PULSE_PIN, pulseEnd, RISING);
}

void pulseEnd() {
  unsigned long now = millis();
  pulseWidth = now - pulseStartTime;
  if (pulseWidth > METER_PULSE_WIDTH - 15 && pulseWidth < METER_PULSE_WIDTH + 15) {
    // workaround?
    energyCounter++;
  }
  attachInterrupt(PULSE_PIN, pulseStart, FALLING);
}

void report() {
  maybeReconnect();
  Serial.println(millis());
  Serial.println("Sending data");

  voltage = ESP.getVcc() / 1000.0;
  rssi = WiFi.RSSI();
  temperature = sensors.getTempCByIndex(0);

  HTTPClient http;
  http.begin(String(API_ENDPOINT) + nodeName);
  String stream;
  StaticJsonBuffer<200> buffer;
  JsonObject& root = buffer.createObject();
  root["temperature"] = temperature;
  root["movementCounter"] = movementCounter;
  root["energyCounter"] = 1.0f * energyCounter / PULSE_PER_WH;
  root["errorCounter"] = errorCounter;
  root["voltage"] = voltage;
  root["rssi"] = rssi;
  root["packetsSent"] = packetsSent;
  root["uptime"] = millis();
  root.printTo(stream);

  int status = http.POST(stream);
  if (status == 200) {
    Serial.println("...success!");
    packetsSent++;
    movementCounter = 0;
    energyCounter = 0;
  } else {
    Serial.println(status);
    Serial.println(http.getString());
    errorCounter++;
  }
  Serial.println("end");
  
  http.end();
}

void maybeReconnect() {
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("(Re)connecting...");
    delay(1000);
  }
  Serial.print("connected, got IP: ");
  Serial.println(WiFi.localIP());
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

void attemptSensorReadAndReport() {
  readAndReport.detach();
  sensors.begin();
  int tries = 0;
  bool success = false;
  // Problems with EM interference? Just retry...
  while (tries < 10) {
    success = sensors.getDeviceCount() > 0;
    if (success) break;
    delay(500);
    sensors.begin();
    tries++;
  }

  if (success) {
    sensors.setResolution(12);
    sensors.requestTemperatures();
    report();
  } else {
    errorCounter++;
    error(tries);
  }
  readAndReport.attach(REPORT_FREQUENCY, attemptSensorReadAndReport);
}

