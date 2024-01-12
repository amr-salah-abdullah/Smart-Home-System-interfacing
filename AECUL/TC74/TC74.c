#include "TC74.h"

uint8_t ReadTemp(i2c_address_t addr){
    uint8_t temp = 0;
    temp = I2C_Read1ByteRegister(addr,0x00);
    return temp;
}

