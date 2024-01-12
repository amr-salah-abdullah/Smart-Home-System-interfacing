/* 
 * File:   LCDdisplay.h
 * Author: AMR SALAH ABDULLA
 *
 * Created on November 11, 2023, 12:29 AM
 */

#ifndef LCD_H
#define	LCD_H
/***************** INCLUDEs *************************/
#include "../../mcc_generated_files/mcc.h"
#include "../../../SmartHome.X/mcc_generated_files/examples/i2c_master_example.h"

/***************** MACRO DEC ***********************/
#define E_OK                0x01
#define E_NOK               0x00
#define LCDclear            0x01
#define LCDreturnhome       0x02
#define LCDentrymode        0x06
#define LCDcurOFFdisON      0x0c
#define LCDcurOFFdisOFF     0x0b
#define LCDcurOBBLKON       0x0f
#define LCDcurOBBLKOFF      0x0e
#define LCDdisSHIFTRIGHT    0x1c
#define LCDdisSHIFTLEFT     0x18
#define LCDdisSHIFTLEFT     0x18
#define LCD8bit2line        0x38
#define LCD4bit2line        0x28
#define LCDCGROMSTART       0x40
#define LCDDDRAMSTART       0x80
/***************** MACRO FUMC DEC ******************/
#define SETBIT(REG, BitPos)         (REG |= (((uint8_t)1) << BitPos))
#define CLEARBIT(REG, BitPos)       (REG &= ~(((uint8_t)1) << BitPos))
#define TOGGLEBIT(REG, BitPos)      (REG ^= (((uint8_t)1) << BitPos))
#define READBIT(REG, BitPos)         ((REG >> BitPos)& ((uint8_t)1))
/***************** DATA TYPE DEC *******************/
typedef struct{
    uint8_t   port          :3;   /*PORTINDEX*/
    uint8_t   pin           :3;   /*PININDEX*/
    uint8_t   direction     :1;   /*DIRECTION STATUS*/
    uint8_t   logic         :1;   /*LOGIC STATUS*/
}PinConfig_t;

typedef struct{
    uint8_t REpin;
    uint8_t REport;
    uint8_t ENpin;
    uint8_t ENport;
    uint8_t datapins[4];
    uint8_t dataport[4];
}LCD4B_t;


/***************** FUNC DEC ************************/
uint8_t LCD4B_SET           (const LCD4B_t *lcd);
uint8_t LCD4B_SENDCMD       (const LCD4B_t *lcd, uint8_t cmd);
uint8_t LCD4B_SENDCHAR      (const LCD4B_t *lcd, uint8_t data);
uint8_t LCD4B_SENDCHARPOS   (const LCD4B_t *lcd, uint8_t data, uint8_t row, uint8_t column);
uint8_t LCD4B_SENDSTR       (const LCD4B_t *lcd, uint8_t *str);
uint8_t LCD4B_SENDSTRPOS    (const LCD4B_t *lcd, uint8_t *str, uint8_t row, uint8_t column);
uint8_t LCD4B_SENDCUSTOMCHAR(const LCD4B_t *lcd, uint8_t row, uint8_t column,
                             const uint8_t chr[],uint8_t mem_pos);

void byte2str   (uint8_t  input, char *str);
void short2str  (uint16_t input, char *str);
void int2str    (uint32_t input, char *str);

uint8_t PINSTART   (const PinConfig_t * pinconfig);
uint8_t PINWRITE   (const PinConfig_t * pinconfig, uint8_t log);
#endif	/* LCD_H */

