#include "RealTimerCLock.h"
static DateAndTime_t dt;
uint8_t _Date[3]; // 'year' ' month' 'day'
uint8_t _Time[3]; // 'hours' ' minutes' 'seconds'
uint8_t  timestr[10];
uint8_t  datestr[10];
DateAndTime_t GetDataAndTime(void){
    dt.second = I2C_Read1ByteRegister(0x68, 0x00);
    dt.minute = I2C_Read1ByteRegister(0x68, 0x01);
    dt.hour   = I2C_Read1ByteRegister(0x68, 0x02);
    dt.day    = I2C_Read1ByteRegister(0x68, 0x04);
    dt.month  = I2C_Read1ByteRegister(0x68, 0x05);
    dt.year   = I2C_Read1ByteRegister(0x68, 0x06);
    dt.init_read = 1;

    return dt;
}
uint8_t * DateArray(void){
    if (dt.init_read != 1){
        dt = GetDataAndTime();        
    }
    _Date[0] = dt.year;
    _Date[1] = dt.month;
    _Date[2] = dt.day;
    return _Date;
}

uint8_t* TimeArray(void){
    if (dt.init_read != 1){
        dt = GetDataAndTime();        
    }
    _Time[0] = dt.hour;
    _Time[1] = dt.minute;
    _Time[2] = dt.second;
    return _Time;

}
void EUSART_SendString(uint8_t *str){
    uint16_t len = strlen((char *)str);
    while(len--){
        EUSART_Write(*str++);
    }
}

void PrintDateUART(void){
    uint8_t * str = DatetoString();
    EUSART_SendString((uint8_t*)"DATE: ");
    EUSART_SendString(str);
}
void PrintTimeUART(void){
    uint8_t * str = TimetoString();
    EUSART_SendString((uint8_t*)"Time: ");
    EUSART_SendString(str);

}

uint8_t * TimetoString (void){
    // Formulate the time array to begin the conversions
    TimeArray();
    timestr[0] = ((_Time[2] >> 4) + '0');
    timestr[1] = ((_Time[2] & 0x0F) + '0');
    timestr[2] = ':';
    timestr[3] = ((_Time[1] >> 4) + '0');
    timestr[4] = ((_Time[1] & 0x0F) + '0');
    timestr[5] = ':';
    timestr[6] = ((_Time[0] >> 4) + '0');
    timestr[7] = ((_Time[0] & 0x0F) + '0');
    timestr[8] = '\r';
    
    return timestr;
}
uint8_t * DatetoString(void){
    // Formulate the time array to begin the conversions
    DateArray();
    datestr[0] = ((_Date[2] >> 4) + '0');
    datestr[1] = ((_Date[2] & 0x0F) + '0');
    datestr[2] = '/';
    datestr[3] = ((_Date[1] >> 4) + '0');
    datestr[4] = ((_Date[1] & 0x0F) + '0');
    datestr[5] = '/';
    datestr[6] = ((_Date[0] >> 4) + '0');
    datestr[7] = ((_Date[0] & 0x0F) + '0');
    datestr[8] = '\r';
 
    return datestr;
}