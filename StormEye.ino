#include "RF24.h"
#include "esp_bt.h"
#include "esp_wifi.h"
#include <SPI.h>

const int CHANNEL_LIMIT = 80;
const int MIN_DELAY_MICROSECONDS = 20;
const int MAX_DELAY_MICROSECONDS = 80;
const int LED = 27;

SPIClass *vspi = nullptr;
SPIClass *hspi = nullptr;
bool vspi_status = true;
bool hspi_status = true;

// HSPI=SCK = 14, MISO = 12, MOSI = 13, CS = 15 , CE = 16
// VSPI=SCK = 18, MISO =19, MOSI = 23 ,CS =21 ,CE = 22

RF24 radio_hspi(16, 15, 16000000);
RF24 radio_vspi(22, 21, 16000000);

void channel_hopping(RF24 &radio) {
  radio.setChannel(random(CHANNEL_LIMIT));
  delayMicroseconds(random(MIN_DELAY_MICROSECONDS, MAX_DELAY_MICROSECONDS));
}

void config_esp() {
  Serial.begin(115200);
  esp_bt_controller_deinit();
  esp_wifi_stop();
  esp_wifi_deinit();
  esp_wifi_disconnect();
}

void setup() {
  config_esp();
  initHSPI();
  initVSPI();
  digitalWrite(LED, HIGH);
}

void initVSPI() {
  vspi = new SPIClass(VSPI);
  vspi->begin();
  if (radio_vspi.begin(vspi)) {
    Serial.println("VSPI started !!!");
    radio_vspi.setAutoAck(false);
    radio_vspi.stopListening();
    radio_vspi.setRetries(0, 0);
    radio_vspi.setPALevel(RF24_PA_MAX, true);
    radio_vspi.setDataRate(RF24_2MBPS);
    radio_vspi.setCRCLength(RF24_CRC_DISABLED);
    radio_vspi.printPrettyDetails();
    radio_vspi.startConstCarrier(RF24_PA_MAX, 35);
  } else {
    Serial.println("VSPI couldn't start !!!");
    vspi_status = false;
  }
}

void initHSPI() {
  hspi = new SPIClass(HSPI);
  hspi->begin();
  if (radio_hspi.begin(hspi)) {
    Serial.println("HSPI Started !!!");
    radio_hspi.setAutoAck(false);
    radio_hspi.stopListening();
    radio_hspi.setRetries(0, 0);
    radio_hspi.setPALevel(RF24_PA_MAX, true);
    radio_hspi.setDataRate(RF24_2MBPS);
    radio_hspi.setCRCLength(RF24_CRC_DISABLED);
    radio_hspi.printPrettyDetails();
    radio_hspi.startConstCarrier(RF24_PA_MAX, 50);
  } else {
    Serial.println("HSPI couldn't start !!!");
    hspi_status = false;
  }
}

void loop() {
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  if (vspi_status && hspi_status) {
    channel_hopping(radio_vspi);
    channel_hopping(radio_hspi);
  } else if (vspi_status && !hspi_status) {
    channel_hopping(radio_vspi);
  } else if (!vspi_status && hspi_status) {
    channel_hopping(radio_hspi);
  } else {
    Serial.println("Device couldn't start !!!");
    while (true) {
      delay(1000);
    }
  }
}
