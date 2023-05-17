/**
 * See README.txt for wiring.
 */

#include "Adafruit_BMP3XX.h"
#include <RH_RF95.h>

#define CS 9
#define SCK 3   // SCK: Override due to radio problem
#define MOSI 4  // SDA: Override due to radio problem

Adafruit_BMP3XX bmp;
RH_RF95 rf95(12, 6);

int STATUS = 13;
float frequency = 921.2;
float calibrateOffset = 7.53;

float inchesPerPascal = -3.3;

// Last recived measurment
// float elvPres = -1; // Moved
float elvTemp = -1;

// Time from last recived packet
long prevPacket = 0;

void setup() {
  SerialUSB.begin(115200);
  while (!SerialUSB);

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
  // rf95.setTxPower(14, false);

  SerialUSB.println("> Setup complete.");
}

void loop() {
  float lobbyPres;
  float elvPres;

  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      // RX LED means we are activly recieving packets
      digitalWrite(PIN_LED_RXL, LOW);  // This LED is backwards from factory
      prevPacket = millis();

      ::memcpy(&elvPres, buf, sizeof(float));
      ::memcpy(&elvTemp, buf + sizeof(float), sizeof(float));

    } else {
      SerialUSB.println("> Recieve failed!");
      return;
    }

    if (!bmp.performReading()) {
      SerialUSB.println("> BMP reading failed!");
      return;
    }

    lobbyPres = bmp.readPressure() - calibrateOffset;

    SerialUSB.println("--------");

    SerialUSB.print("Lobby: ");
    SerialUSB.print(lobbyPres);
    SerialUSB.print(" Elevator: ");
    SerialUSB.println(elvPres);

    SerialUSB.print("Pressure diff: ");
    SerialUSB.print(lobbyPres - elvPres);
    SerialUSB.print(" Height diff (inches): ");
    SerialUSB.println((lobbyPres - elvPres) * inchesPerPascal);
  }

  if (millis() - prevPacket > 1000) {
    digitalWrite(PIN_LED_RXL, HIGH);  // This LED is backwards from factory
    prevPacket = millis();            // No need to keep writing
  }
}
