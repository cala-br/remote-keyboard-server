#include <Arduino.h>
#include "wifi.hpp"

#ifdef ESP32
  #include <WiFi.h>
  #include <mDNS.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#endif


void initTime() {
  constexpr int gmt = 2;
  constexpr int timezone = gmt * 3600;
  configTime(timezone, 0, "pool.ntp.org", "time.nist.gov");
}

bool connectToWifi(
  const char *ssid, 
  const char *password,
  const char *dname
) {
  byte timeout = 50;

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  for (int i = 0; i < timeout; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected to WiFi");
      Serial.print("Server can be accessed at https://");
      Serial.print(WiFi.localIP());

      if (MDNS.begin(dname)) {
        Serial.print(" or at https://");
        Serial.print(dname);
        Serial.println(".local");
      }

      return true;
    }
    delay(5000);
    Serial.print(".");
  }

  Serial.println("\nFailed to connect to WiFi");
  Serial.println("Check network status and access data");
  Serial.println("Push RST to try again");
  return false;
}