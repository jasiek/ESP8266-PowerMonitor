#include <Arduino.h>

#include <ArduinoJson.h>
#include <Ticker.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
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
WiFiClient client;
PubSubClient mqtt(client);

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
  Serial.print("Built on ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);
  Serial.println("Starting up.");
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASS);

  maybeReconnect();
  determineNodeName();
#ifdef MQTT_SERVER
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
#endif
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
  delay(REPORT_FREQUENCY * 1000);
  attemptSensorReadAndReport();
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
  if (pulseWidth > METER_PULSE_WIDTH - 10 && pulseWidth < METER_PULSE_WIDTH + 10) {
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
  http.setUserAgent(String("ESP8266-PowerMonitor") + __DATE__ + __TIME__);
  http.begin(String(API_ENDPOINT) + nodeName);
  String stream;
  StaticJsonBuffer<200> buffer;
  JsonObject& root = buffer.createObject();
  root["temperature"] = temperature;
  root["movementCounter"] = movementCounter;
  root["energyCounter"] = energyCounter;
  root["errorCounter"] = errorCounter;
  root["voltage"] = voltage;
  root["rssi"] = rssi;
  root["packetsSent"] = packetsSent;
  root["uptime"] = millis();
  root.printTo(stream);
  Serial.println(stream);

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

#ifdef MQTT_SERVER
  if (mqtt.connect("ESP8266-PowerMonitor")) {
    String topic = "/devices/" + nodeName;
    mqtt.publish(topic.c_str(), stream.c_str());
    mqtt.disconnect();
  }
#endif
}

void maybeReconnect() {
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print("(Re)connecting to: ");
    Serial.println(WIFI_SSID);
    delay(1000);
  }
  Serial.print("connected to: ");
  Serial.println(WiFi.BSSIDstr());
  Serial.print("IP: ");
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
