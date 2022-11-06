#define DEVICEID    Arduino-1         // Change to a custom id for your device, if not define, DEVICEID will be defaulted as Unknown
#include "ArduinoOTAFirmwareUpdater.h"

#define ssid              "<WiFi-SSID>"
#define password          "<WiFi-Password>"
#define TX                tx
#define RX                rx

#define IND_LED       <Digital-Pin-Num-For-Indicator-LED>
#define RESET_PIN     <Digital-Pin-Num-For-Reset>

WiFiClient espClient;
ArduinoOTAFirmwareUpdater ArduinoFlash(&espClient, RESET_PIN, IND_LED);

void wifiSetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    digitalWrite(IND_LED, HIGH);
    delay(200);
    digitalWrite(IND_LED, LOW);
    delay(200);
  }
}

void setup() {
  wifiSetup();
}

void loop() {
  ArduinoFlash.clientFlashArduino();
}