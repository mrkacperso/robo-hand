#include "mt6825.h"
#include <mat.h>
#include <bitset>

MT6825::MT6825(uint8_t chipSelect, uint8_t spiMISO, uint8_t spiMOSI, uint8_t spiSCLK) {
    this->chipSelect = chipSelect;
    this->spiMISO = spiMISO;
    this->spiMOSI = spiMOSI;
    this->spiSCLK = spiSCLK;
}

void MT6825::init(SPIClass* spi) {
    this->spi = spi;
    pinMode(chipSelect, OUTPUT);
    spi->begin(spiSCLK, spiMISO, spiMOSI, chipSelect);
    digitalWrite(chipSelect, HIGH);
    this->Sensor::init();
}

float MT6825::getSensorAngle() {
    uint32_t rawData = readRegisters();

    // if (rawData & LowMagField) {
    //     // Serial.println("Magnetic flux insufficient");
    //     return 0;
    // }

    // if (rawData & OverSpeed) {
    //     // Serial.println("Overspeed");
    //     return 0;
    // }

    Serial.print(">raw:");
    Serial.println(rawData);
    uint16_t angleDeg = (rawData / (float)CountsPerRev) * 360;
    Serial.print(">angle_deg:");
    Serial.println(angleDeg);


    // calculate angle in radians by dividing raw sensor data by number of counts per revolution (range of 18-bits) 
    return (angleDeg * _PI)/180;
}

uint32_t MT6825::readRegisters() {
    uint8_t r3 = 0;
    uint8_t r4 = 0;
    uint8_t r5 = 0;

    uint32_t res = 0;
    // reg0x03 = 0, reg0x04 = 0, reg0x05 = 0;

    //  Create a read command by setting MSB in first register address to 1
    // uint32_t readCommand = 0x03 | (1 << 7);    

    spi->beginTransaction(spiSettings);
    digitalWrite(chipSelect, LOW);
    spi->transfer(0x03 | (1 << 7)); // 0x300 = 00000011 00000000
    delayMicroseconds(1);
    r3 = spi->transfer(0x0);
    digitalWrite(chipSelect, HIGH);
    spi->endTransaction();

    // for (int i = 7; i >= 0; i--) {
        // Serial.print((r3 >> i) & 0x1);
    // }
    // Serial.print(" ");
    res = (res | r3) << 6; 


    spi->beginTransaction(spiSettings);
    digitalWrite(chipSelect, LOW);
    spi->transfer(0x04 | (1 << 7)); // 0x300 = 00000011 00000000
    delayMicroseconds(1);
    r4 = spi->transfer(0x0);
    digitalWrite(chipSelect, HIGH);
    spi->endTransaction();

    uint8_t mask = 0xFC;
    res = (res | (r4 & mask)) << 4;


    // for (int i = 7; i >= 0; i--) {
        // Serial.print((r4 >> i) & 0x1);
    // }
    // Serial.print(" ");
    
    if (r4 & 0x2) {
        Serial.print(">diag_mag:");
        Serial.println(1);
    } else {
        Serial.print(">diag_mag:");
        Serial.println(0);
    }

    spi->beginTransaction(spiSettings);
    digitalWrite(chipSelect, LOW);
    spi->transfer(0x05 | (1 << 7)); 
    delayMicroseconds(1);
    r5 = spi->transfer(0x0);
    digitalWrite(chipSelect, HIGH);
    spi->endTransaction();

    mask = 0xF0;
    res = res | (r5 & mask);

    if (r5 & 0x8) {
        Serial.print(">diag_spd:");
        Serial.println(1);
    } else {
        Serial.print(">diag_spd:");
        Serial.println(0);
    }

    Serial.print(">reg3:");
    Serial.println(r3);

    Serial.print(">reg4:");
    Serial.println(r4);

    Serial.print(">reg5:");
    Serial.println(r5
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    );

    return res;
}

/**
 * Close the SPI connection
 * SPI has an internal SPI-device counter, for each init()-call the close() function must be called exactly 1 time
*/
void MT6825::close() {
    spi->end();
}