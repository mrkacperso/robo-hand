#include "Arduino.h"
#include <SPI.h>
#include <SimpleFOC.h>

const SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE3);
const uint32_t CountsPerRev = 262144;
const uint32_t LowMagField = 0x40000;
const uint32_t OverSpeed = 0x80000;

class MT6825: public Sensor{
    public:
    MT6825(uint8_t chipSelect, uint8_t spiMISO, uint8_t spiMOSI, uint8_t spiSCLK);

    /**
     * Sensor initialisation with SPI class
    */
    void init(SPIClass* spi);

    // implementation of abstract functions of the Sensor class
    /** get current angle (rad) */
    float getSensorAngle() override;

    private:
        SPIClass* spi;
        uint8_t chipSelect;
        uint8_t spiMISO;
        uint8_t spiMOSI;
        uint8_t spiSCLK;


        uint32_t readRegisters();
        bool calcEvenParity(uint8_t data);
        float getRawAngle();
        void close();
};