#ifndef Statsd_h
#define Statsd_h

#include "Arduino.h"
#include "IPAddress.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"

class StatsD
{
public:
  StatsD(IPAddress ip, int port, int localPort);
  void increment(const char *metric);
  void decrement(const char *metric);
  void counter(const char *metric, int counter);
  void timing(const char *metric, int ms);
  void gauge(const char *metric, int gaugeValue);
  void gauge(const char *metric, float gaugeValue);
  void sets(const char *metric, int setsValue);
private:
  void _send(const char *metric, int value, const char *cmd);
  void _send(const char *metric, float value, const char *cmd);
  void _send(const char *metric, const char *value, const char *cmd);
  IPAddress _ip;
  int _port;
};

#endif
