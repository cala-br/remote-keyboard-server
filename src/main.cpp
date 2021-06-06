#include <udp_server_secure.hpp>
#include <Wire.h>

#include "wifi.hpp"
#include "certs"
#include "wifi_credentials"

using namespace iremote;

const int SDA_PIN = D2;
const int SCL_PIN = D1;


UdpServerSecure irServer {
  new AuthServer {
    "calabr",
    "12345",
    {SERVER_CERT, SERVER_KEY},
  }
};


void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  bool connected = 
    connectToWifi(SSID, PASSWORD, DNAME);
  
  if (!connected) {
    delay(15000);
    ESP.restart();
  }
  

  initTime();
  irServer.begin(7382);
  Serial.println("Server is ready");
}

void loop() {
  irServer.handleNext([] (UdpString command) {
    Wire.beginTransmission(0x1);
    Wire.println(command);
    Wire.endTransmission();
  });
}