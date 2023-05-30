/**
 * This program is used to calibrate the BMP sensors pressure. If using two modules
 * one should run this code while the other runs elevator with debug turned off.
 */

#include "Adafruit_BMP3XX.h"
#include <RH_RF95.h>

#define CS 9
#define SCK 3   // SCK: Override due to radio problem
#define MOSI 4  // SDA: Override due to radio problem

Adafruit_BMP3XX bmp;
RH_RF95 rf95(12, 6);

int readDelay = 200; // Reading delay (ms). Only with rfMode off

int STATUS = 13;
float frequency = 921.2;
float calibrateNum = 11.9;

float thisSumPres = 0;
float recvSumPres = 0;
float errorSum = 0;

int measureNum = 0;

long prevPacket = 0;

void setup() {
  SerialUSB.begin(115200);
  while(!SerialUSB);

  SerialUSB.println("> Begin setup...");

  if (!bmp.begin_SPI(CS, SCK, MISO, MOSI)) {
    SerialUSB.println("> BMP setup failed!");
  }

  if (rf95.init() == false) {
    SerialUSB.println("> Radio setup failed!");
  }

  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  rf95.setFrequency(frequency);

  // First reading is always garbage
  if (!bmp.performReading()) {
    SerialUSB.println("> BMP reading failed!");
  }

  SerialUSB.println("> Setup complete.");

  digitalWrite(STATUS, HIGH);
  delay(500);
  digitalWrite(STATUS, LOW);
}

void loop() {
  float recvPres;
  float thisPres;
  float error;

  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      // RX LED means we are activly recieving packets
      digitalWrite(PIN_LED_RXL, LOW);  // This LED is backwards from factory
      prevPacket = millis();

      ::memcpy(&recvPres, buf, sizeof(float));
      recvSumPres += recvPres;
    } else {
      SerialUSB.println("> Recieve failed!");
      return;
    }

    if (!bmp.performReading()) {
      SerialUSB.println("> BMP reading failed!");
      return;
    }

    thisPres = bmp.readPressure() - calibrateNum;
    thisSumPres += thisPres;
    measureNum++;

    error = thisPres - recvPres;
    errorSum += error;

    SerialUSB.println("--------");

    SerialUSB.print("Unit reading #");
    SerialUSB.print(measureNum);
    SerialUSB.print(": ");
    SerialUSB.print(thisPres);
    SerialUSB.print(" avg: ");
    SerialUSB.println(thisSumPres / measureNum);

    SerialUSB.print("Recived reading #");
    SerialUSB.print(measureNum);
    SerialUSB.print(": ");
    SerialUSB.print(recvPres);
    SerialUSB.print(" avg: ");
    SerialUSB.println(recvSumPres / measureNum);

    SerialUSB.print("Reading error: ");
    SerialUSB.print(error);
    SerialUSB.print(" avg error: ");
    SerialUSB.println(errorSum / measureNum);
  }

  if (millis() - prevPacket > 1000) {
    digitalWrite(PIN_LED_RXL, HIGH);  // This LED is backwards from factory
    prevPacket = millis();            // No need to keep writing
  }
}
