/**
 * See README.txt for wiring.
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include "SparkFun_BMA400_Arduino_Library.h"
#include <RH_RF95.h>

#define CS 9
#define SCK 3 // SCK: Override due to radio problem
#define MOSI 4 // SDA: Override due to radio problem

Adafruit_BMP3XX bmp;
BMA400 bma;
RH_RF95 rf95(12, 6);

uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT; // 0x14

// Options
bool debug = false;
int readings = 4; // Readings per pressure data point
float upperMoveBound = 1.02; // Upper normal bound for accelerometer when still
float lowerMoveBound = 0.96; // Lower normal bound for accelerometer when still
long maxWait = 60000; // Max time between packets sent in milliseconds

long prevPacket = 0; // Time last packet was sent in milliseconds
float frequency = 921.2; // Set broadcast frequency


void setup() {
  SerialUSB.begin(115200);
  if (debug) { while(!SerialUSB); }
  
  SerialUSB.println("> Elevator: Begin setup...");

  Wire.begin();

  if (!bmp.begin_SPI(CS, SCK, MISO, MOSI)) {
    SerialUSB.println("> Elevator: BMP setup failed!");
    return;
  }

  if (rf95.init() == false){
    SerialUSB.println("> Elevator: Radio setup failed!");
    return;
  }

  if (bma.beginI2C(i2cAddress) != BMA400_OK) {
    SerialUSB.println("> Elevator: Accelerometer setup failed!");
    return;
  }

  // This is a real thing but I dont know how to make it work.
  // bma.setAutoLowPower(bma400_auto_lp_conf *config)

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
}


void loop() {
  float pres = getPressure(readings);
  float acc = getAcceleration();

  if (acc > upperMoveBound || acc < lowerMoveBound || millis() - prevPacket > maxWait) {
    prevPacket = millis();

    float accelX = bma.data.accelX;
    float accelY = bma.data.accelY;
    float accelZ = bma.data.accelZ;

    uint8_t buf[sizeof(float) * 4];
    ::memcpy(buf, &pres, sizeof(float));
    ::memcpy(buf + sizeof(float), &accelX, sizeof(float));
    ::memcpy(buf + sizeof(float) * 2, &accelY, sizeof(float));
    ::memcpy(buf + sizeof(float) * 3, &accelZ, sizeof(float));

    rf95.send(buf, sizeof(buf));
    rf95.waitPacketSent();
  
    if (debug) {
      SerialUSB.print("> Elevator: transmitting (");
      SerialUSB.print(pres);
      SerialUSB.print("f, ");
      SerialUSB.print(accelX);
      SerialUSB.print("f, ");
      SerialUSB.print(accelY);
      SerialUSB.print("f, ");
      SerialUSB.print(accelZ);
      SerialUSB.print("f) Total: ");
      SerialUSB.println(getAcceleration());
    }
  }

  delay(500);
}


float getPressure(int r) {
  float sum = 0;
  for (int i = 0; i < r; i++) {
    if (!bmp.performReading()) {
      SerialUSB.println("> Elevator: BMP reading failed!");
    }
    sum += bmp.readPressure();
  }
  return sum / r;
}


float getAcceleration() {
  bma.getSensorData();
  return sqrt(sq(bma.data.accelX) + sq(bma.data.accelY) + sq(bma.data.accelZ));
}