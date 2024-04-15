#include <SimpleFOC.h>
#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include "mt6825.h"

const uint8_t SPI2_MISO = 37;
const uint8_t SPI2_MOSI = 35;
const uint8_t SPI2_SCLK = 38;
const uint8_t MT6825_CS = 34;
MT6825 mt6825 = MT6825(MT6825_CS, SPI2_MISO, SPI2_MOSI, SPI2_SCLK);

void setup() {
  // monitoring port
  Serial.begin(115200);

  // init magnetic sensor hardware
  mt6825.init(&SPI);
  Serial.println("MT6825 ready");
  // SPI.begin(SPI2_SCLK, SPI2_MISO, SPI2_MOSI);
  Serial.print("Initial sensor reading: ");
  mt6825.update();
  Serial.print(mt6825.getAngle());
  Serial.print("\n");
  delay(1000);
}

void loop() {
  // IMPORTANT - call as frequently as possible
  // update the sensor values
  mt6825.update();
  // display the angle and the angular velocity to the terminal
  // init magnetic sensor hardware
  // Serial.print(">angle:");
  // Serial.print(mt6825.getAngle());
  // Serial.println("[Rad]\n==============================");

    // Serial.print(">angle_rad:");
    // Serial.println(mt6825.getAngle());
  delay(20);
}