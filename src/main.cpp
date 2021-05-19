#include <udp_server_secure.hpp>
#include <Wire.h>

#include "wifi.hpp"
#include "certs"
#include "wifi_credentials"

using namespace iremote;

const int SDA_PIN = D2;
const int SCL_PIN = D1;


bool connectToWifi();

AuthServer authServer {
  "calabr",
  "12345",
};

UdpServerSecure irServer {authServer};


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
  authServer.setCertificates(SERVER_CERT, SERVER_KEY);
  authServer.begin();
  irServer.begin(7382);
  
  Serial.println("Server is ready");
}

void loop() {
  authServer.handleNext();
  irServer.handleNext([] (UdpString command) {
    Wire.println(command);
  });
}