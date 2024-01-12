/* 
 * File:   ExtEEPROM.h
 * Author: AMR SALAH ABDULLAH
 *
 * Created on December 7, 2023, 7:50 PM
 */
#include "ExtEEPROM.h"

void EXTEEPROM_WriteByte(i2c_address_t Eadd,i2c_address_t Byteadd, uint8_t data){
    I2C_Write1ByteRegister(Eadd,Byteadd,data);
}

uint8_t EXTEEPROM_ReadByte(i2c_address_t Eadd,i2c_address_t Byteadd){
    uint8_t read;
    read = I2C_Read1ByteRegister(Eadd,Byteadd); 
    return read;
}