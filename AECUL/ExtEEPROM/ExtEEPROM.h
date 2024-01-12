/* 
 * File:   ExtEEPROM.h
 * Author: AMR SALAH ABDULLAH
 *
 * Created on December 7, 2023, 7:50 PM
 */

#ifndef EXTEEPROM_H
#define	EXTEEPROM_H

/* includes */
#include "../../mcc_generated_files/mcc.h"
#include "../../../SmartHome.X/mcc_generated_files/examples/i2c_master_example.h"

/* data types */

/* functions */
void EXTEEPROM_WriteByte(i2c_address_t Eadd,i2c_address_t Byteadd, uint8_t data);
uint8_t EXTEEPROM_ReadByte(i2c_address_t Eadd,i2c_address_t Byteadd);

#endif	/* EXTEEPROM_H */

