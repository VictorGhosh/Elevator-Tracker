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

bool debug = true;
int STATUS = 13;
float frequency = 921.2;

// Last recived measurment
float elvPres = -1;
float elvTemp = -1;
// Time from last recived packet
long prevPacket = 0;

void setup() {
  SerialUSB.begin(115200);
  if (debug) { while (!SerialUSB); }

  SerialUSB.println("> Lobby: Begin setup...");

  if (!bmp.begin_SPI(CS, SCK, MISO, MOSI)) {
    SerialUSB.println("> Lobby: Radio setup failed!");
  }

  if (rf95.init() == false) {
    SerialUSB.println("> Lobby: Radio setup failed!");
  }

  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  rf95.setFrequency(frequency);
  // rf95.setTxPower(14, false);

  SerialUSB.println("> Lobby: Setup complete.");

  if (debug) {
    digitalWrite(STATUS, HIGH);
    delay(500);
    digitalWrite(STATUS, LOW);
  }
}

void loop() {
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
      SerialUSB.println("> Lobby: Recieve failed!");
    }

    if (!bmp.performReading()) {
      SerialUSB.println("> Lobby: BMP reading failed!");
    }

    SerialUSB.print("> Lobby: recieved (");
    SerialUSB.print(elvPres);
    SerialUSB.print("f, ");
    SerialUSB.print(elvTemp);
    SerialUSB.println("f) ");
  }

  if (millis() - prevPacket > 1000) {
    digitalWrite(PIN_LED_RXL, HIGH);  // This LED is backwards from factory
    prevPacket = millis();            // No need to keep writing
  }
}
