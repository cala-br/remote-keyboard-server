#ifndef REMOTE_KEYBOARD_SERVER_WIFI_HPP_
#define REMOTE_KEYBOARD_SERVER_WIFI_HPP_


void initTime();
bool connectToWifi(
  const char *ssid, 
  const char *password,
  const char *dname
);

#endif // !REMOTE_KEYBOARD_SERVER_WIFI_HPP_
