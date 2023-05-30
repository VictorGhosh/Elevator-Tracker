/**
 * See README.txt for wiring.
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <RH_RF95.h>

#define CS 9
#define SCK 3 // SCK: Override due to radio problem
#define MOSI 4 // SDA: Override due to radio problem

Adafruit_BMP3XX bmp;
RH_RF95 rf95(12, 6);

bool debug = false;
int readings = 8;

int STATUS = 13;
float frequency = 921.2;

void setup() {
  SerialUSB.begin(115200);
  if (debug) { while(!SerialUSB); }
  
  SerialUSB.println("> Elevator: Begin setup...");

  if (!bmp.begin_SPI(CS, SCK, MISO, MOSI)) {
    SerialUSB.println("> Elevator: BMP setup failed!");
  }

  if (rf95.init() == false){
    SerialUSB.println("> Elevator: Radio setup failed!");
  }

  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  rf95.setFrequency(frequency);
  // rf95.setTxPower(14, false);

  // First reading is always garbage
  if (!bmp.performReading()) {
    SerialUSB.println("> BMP reading failed!");
  }

  SerialUSB.println("> Elevator: Setup complete.");
  if (debug) {
    digitalWrite(STATUS, HIGH);
    delay(500);
    digitalWrite(STATUS, LOW);
  }
}

void loop() {
  if (!bmp.performReading()) {
    SerialUSB.println("> Elevator: BMP reading failed!");
  }

  float pres = getPressure(readings);
  float temp = bmp.readTemperature();

  uint8_t buf[sizeof(float) * 2];
  // uint8_t buf[sizeof(float)];
  ::memcpy(buf, &pres, sizeof(float));
  ::memcpy(buf + sizeof(float), &temp, sizeof(float));

  if (debug) {
    SerialUSB.print("> Elevator: transmitting (");
    SerialUSB.print(pres);
    SerialUSB.print("f, ");
    SerialUSB.print(temp);
    SerialUSB.println("f)");
    // digitalWrite(PIN_LED_TXL, LOW); // LED is backwards from factory
  }
  digitalWrite(PIN_LED_TXL, LOW); // LED is backwards from factory


  rf95.send(buf, sizeof(buf));
  rf95.waitPacketSent();

  // if (debug) { digitalWrite(PIN_LED_TXL, HIGH); }
  digitalWrite(PIN_LED_TXL, HIGH);

  delay(100);
}

float getPressure(int r) {
  float sum = 0;
  for (int i = 0; i < r; i++) {
    if (!bmp.performReading()) {
      SerialUSB.println("> BMP reading failed!");
    }
    sum += bmp.readPressure();
  }
  return sum / r;
}