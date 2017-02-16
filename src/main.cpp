#include <Arduino.h>
#include <ArduinoJson.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <FS.h>
#include <metering.h>
#include "IPAddress.h"
#include "string.h"

#define PULSE_PIN 2
#define ONEWIRE_PIN 4
#define PIR_PIN 5
#define LED_PIN 16
// Report frequency is in seconds
#define REPORT_FREQUENCY 300
#define BUFFER_SIZE 1024

ADC_MODE(ADC_VCC);

OneWire bus(ONEWIRE_PIN); // Use GPIO4 as it is not connected to any peripherals
DallasTemperature sensors(&bus);

int movementCounter;
int energyCounter;
int errorCounter;
unsigned long pulseStartTime;
unsigned long pulseWidth;
unsigned long packetsSent;
float voltage;
float temperature;

int METER_PULSE_WIDTH = 90;

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
  Serial.println();
  Serial.println("ESP8266 Power Monitor");
  Serial.print("Built on ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.print(__TIME__);
  Serial.print(" from ");
  Serial.println(GIT_REVISION);
  Serial.println("-----------------------");
  Serial.flush();

  // Set up sensors, interrupts, etc.
  // When there's a pulse, increment the counter.
  pulseStartTime = millis();
  pinMode(PIR_PIN, INPUT);
  pinMode(PULSE_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); // Used for signalling errors
  digitalWrite(LED_PIN, HIGH);
  attachInterrupt(PULSE_PIN, pulseStart, FALLING);
  attachInterrupt(PIR_PIN, recordMovement, RISING);

  network::start("ESP8266-PowerMonitor");
  network::hello();
  updater::begin();
}

void loop() {
  int cycles = REPORT_FREQUENCY;
  while (cycles > 0) {
    network::loop();
    Serial.print("Measuring. Seconds left: ");
    Serial.println(cycles--);
    if (cycles % 30 == 0) {
      Serial.print("Pulse width: ");
      Serial.println(pulseWidth);
    }
    delay(1000);
  }

  attemptSensorReadAndReport();
  ESP.restart();
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
    temperature = sensors.getTempCByIndex(0);

    StaticJsonBuffer<BUFFER_SIZE> json;
    JsonObject &root = json.createObject();

    if (!isnan(temperature)) {
      root["temperature"] = temperature;
    }
    root["energyCounter"] = energyCounter;
    root["movementCounter"] = movementCounter;
    root["errorCounter"] = errorCounter;
    root["uptime"] = millis();
    root["rssi"] = WiFi.RSSI();

    String stream;
    Serial.println(stream);
    root.printTo(stream);
    network::report(stream);
  } else {
    errorCounter++;
  }
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  network::mqtt_message_received_cb(topic, payload, bytes, length);
}
