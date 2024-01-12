/* 
 * File:   RealTimerCLock.h
 * Author: AMR SALAH ABDULLAH
 *
 * Created on December 7, 2023, 2:35 PM
 */

#ifndef REALTIMERCLOCK_H
#define	REALTIMERCLOCK_H

#include "../../mcc_generated_files/mcc.h"
#include "../../../SmartHome.X/mcc_generated_files/examples/i2c_master_example.h"

typedef struct{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t init_read   :1;
}DateAndTime_t;

DateAndTime_t GetDataAndTime(void);  
uint8_t * DateArray(void);
uint8_t * TimeArray(void);
void PrintDateUART(void);
void PrintTimeUART(void);
void EUSART_SendString(uint8_t *str);
uint8_t * TimetoString (void);
uint8_t * DatetoString (void);

#endif	/* REALTIMERCLOCK_H */

