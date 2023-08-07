/**
 * See README.txt for wiring.
 */

#include "Adafruit_BMP3XX.h"
#include <RH_RF95.h>

#define SCK 3   // SCK: Override due to radio problem
#define MOSI 4  // SDA: Override due to radio problem
#define CS 9
#define STATUS 13

Adafruit_BMP3XX bmp;
RH_RF95 rf95(12, 6);

float frequency = 921.2;

int readings = 16;

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

  // First reading is always garbage
  if (!bmp.performReading()) {
    SerialUSB.println("> Lobby: BMP reading failed!");
  }

  SerialUSB.println("> Setup complete.");
}

void loop() {
  float elevatorPressure;
  float elevatorAccelX;
  float elevatorAccelY;
  float elevatorAccelZ;

  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      // RX LED means we are activly recieving packets
      digitalWrite(PIN_LED_RXL, LOW);  // This LED is backwards from factory
      prevPacket = millis();

      float pressure;
      float accelX;
      float accelY;
      float accelZ;
      ::memcpy(&pressure, buf, sizeof(float));
      ::memcpy(&accelX, buf + sizeof(float), sizeof(float));
      ::memcpy(&accelY, buf + sizeof(float) * 2, sizeof(float));
      ::memcpy(&accelZ, buf + sizeof(float) * 3, sizeof(float));

      elevatorPressure = pressure;
      elevatorAccelX = accelX;
      elevatorAccelY = accelY;
      elevatorAccelZ = accelZ;

    } else {
      SerialUSB.println("> Recieve failed!");
      return;
    }

    float lobbyPressure = getPressure(readings);

    SerialUSB.print(millis());
    SerialUSB.print(" ");
    SerialUSB.print(lobbyPressure);
    SerialUSB.print(" ");
    SerialUSB.print(elevatorPressure); 
    SerialUSB.print(" ");
    SerialUSB.print(elevatorAccelX);
    SerialUSB.print(" ");
    SerialUSB.print(elevatorAccelY);
    SerialUSB.print(" ");
    SerialUSB.print(elevatorAccelZ);
    SerialUSB.print(" ");
    SerialUSB.println(getFloorEstimate(elevatorPressure, lobbyPressure));
  }

  if (millis() - prevPacket > 750) {
    digitalWrite(PIN_LED_RXL, HIGH);  // This LED is backwards from factory
    prevPacket = millis();            // No need to keep writing
  }
}

float getPressure(int r) {
  float sum = 0;
  for (int i = 0; i < r; i++) {
    if (!bmp.performReading()) {
      SerialUSB.println("> Lobby: BMP reading failed!");
    }
    sum += bmp.readPressure();
  }
  return sum / r;
}

int getFloorEstimate(float elevatorPressure, float lobbyPressure) {
  // Higher difference == Lower Floor
  float diff = lobbyPressure - elevatorPressure;
  // float diff = elevatorPressure - lobbyPressure;
  if (diff > 129.24) { return 1; }
  else if (diff > 87.65) { return 2; }
  else if (diff > 46.38) { return 3; } 
  else if (diff > 9.89) { return 4; }
  else if (diff > -27.14) { return 5; }
  else if (diff > -67.07) { return 6; }
  else { return 7; }
}