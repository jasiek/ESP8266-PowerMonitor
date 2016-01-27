#include <statsdclient.h>
#include <ArduinoJson.h>
#include <Ticker.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "IPAddress.h"
#include "WiFiUdp.h"
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "settings.h"
#include "string.h"


#define PULSE_PIN 2
#define ONEWIRE_PIN 4
#define PIR_PIN 5
#define LED_PIN 16
// Report frequency is in seconds
#define REPORT_FREQUENCY 60

OneWire bus(ONEWIRE_PIN); // Use GPIO4 as it is not connected to any peripherals
DallasTemperature sensors(&bus);
ESP8266WebServer server(80);
Ticker readAndReport;

WiFiUDP statsdUdp;
statsdclient statsd(STATSD_IP, STATSD_PORT, statsdUdp);

int movementCounter;
int energyCounter;
int errorCounter;
unsigned long pulseStartTime;
unsigned long pulseWidth;
unsigned long packetsSent;
float voltage;
float temperature;
int rssi;

char _metricLabel[64];

void pulseStart();
void pulseEnd();
void determineNodeName();
void recordMovement();
void report();
void setupHttpServer();
void attemptSensorReadAndReport();
bool maybeReconnect();

String nodeName;

ADC_MODE(ADC_VCC);

void setup() {
  Serial.begin(115200);
  Serial.println();

  maybeReconnect();
  determineNodeName();
  setupHttpServer();
  // When there's a pulse, increment the counter.
  pulseStartTime = millis();
  pinMode(PIR_PIN, INPUT);
  pinMode(PULSE_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); // Used for signalling errors
  digitalWrite(LED_PIN, HIGH);
  attachInterrupt(PULSE_PIN, pulseStart, FALLING);
  attachInterrupt(PIR_PIN, recordMovement, RISING);

  readAndReport.attach(REPORT_FREQUENCY, attemptSensorReadAndReport);
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
  server.handleClient();
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

const char *metricLabel(const char *label) {
  memset(_metricLabel, 0, 64);
  strcpy(_metricLabel, nodeName.c_str());
  strcat(_metricLabel, ".");
  strcat(_metricLabel, label);
  return _metricLabel;
}

void reportTemperature() {
  temperature = sensors.getTempCByIndex(0);
  Serial.println("temperature: " + String(temperature));
  statsd.begin().gauge(metricLabel("temperature"), 0).gauge(metricLabel("temperature"), temperature).send();
}

void reportPulses() {
  Serial.println("energy: " + String(energyCounter) + " pulses");
  statsd.begin().counter(metricLabel("energy"), energyCounter).send();
  energyCounter = 0;
}

void reportMovement() {
  Serial.print("Movements: ");
  Serial.println(movementCounter);
  statsd.begin().counter(metricLabel("movement"), movementCounter).send();
  movementCounter = 0;
}

void reportRSSI() {
  rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.println(rssi);
  statsd.begin().gauge(metricLabel("rssi"), 0).gauge(metricLabel("rssi"), rssi).send();
}

void reportVoltage() {
  voltage = ESP.getVcc() / 1000.0;
  Serial.print("voltage: ");
  Serial.println(voltage);
  statsd.begin().gauge(metricLabel("voltage"), voltage).send();
}

void incrementDataCounter() {
  packetsSent++;
  statsd.begin().counter(metricLabel("packets"), 1).send();
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

void attemptSensorReadAndReport() {
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
}

void setupHttpServer() {
  server.on("/", [](){
    String stream;
    StaticJsonBuffer<200> buffer;
    JsonObject& root = buffer.createObject();
    root["nodeName"] = nodeName;
    root["temperature"] = temperature;
    root["movementCounter"] = movementCounter;
    root["energyCounter"] = 1.0f * energyCounter / PULSE_PER_WH;
    root["errorCounter"] = errorCounter;
    root["voltage"] = voltage;
    root["rssi"] = rssi;
    root["packetsSent"] = packetsSent;
    root["uptime"] = millis();
    root.printTo(stream);
    server.send(200, "application/json", stream);
  });
  server.begin();
}

