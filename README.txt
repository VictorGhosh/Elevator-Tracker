Components: 
    - Sparkfun SAMD21 Pro RF (RF)
    - Adafruit BMP390 (BMP)
    
Wiring:
    - BMP(VIN)  -> RF(3v3)
    - BMP(GND)  -> RF(GND)
    - BMP(SCL)  -> RF(D3)   *SCK in code
    - BMP(SDO)  -> RF(MISO) *MISO in code
    - BMP(SDA)  -> RF(D4)   *MOSI in code
    - BMP(CS)   -> RF(9)    *CS in code 
    *Note that SCK and MOSI have been overridden due to complications with the
        RF function of the board. This is not an ideal solution as the board
        has dedicated MOSI and SCK pinouts.
