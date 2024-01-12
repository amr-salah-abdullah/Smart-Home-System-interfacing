/* 
 * File:   LCDdisplay.h
 * Author: AMR SALAH ABDULLA
 *
 * Created on November 11, 2023, 12:29 AM
 */
#include "LCD.h"

/******************** helper    FUNC ************************/
static uint8_t send4bit       (const LCD4B_t * lcd, uint8_t data);
static uint8_t sendenable     (const LCD4B_t * lcd);
static uint8_t setcursor4bit  (const LCD4B_t *lcd, uint8_t row, uint8_t col);

/******************** converter FUNC ************************/
void byte2str   (uint8_t input,  char *str){
    memset(str,'\0',4);
    sprintf(str,"%i",input);
}

void short2str  (uint16_t input, char *str){
    memset(str,'\0',6);
    sprintf(str,"%i",input);
}

void int2str    (uint32_t input, char *str){
    memset(str,'\0',11);
    sprintf(str,"%lu",input);
}
/****************** code from the old HAL_GPIO ************************/

    /*************** REGSTERS Pointers *********************/
volatile uint8_t *TRIS_Reg[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8_t *LAT_Reg[]  = {&LATA,&LATB,&LATC,&LATD,&LATE};
volatile uint8_t *PORT_Reg[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};


#if (PORT_PIN_CONFIG==ENABLE)
        /**************** PIN CONFIG FUNCTIONS *****************/

uint8_t PINSTART   (const PinConfig_t * pinconfig){
    uint8_t ret = E_OK;
    if((pinconfig->pin > (8-1)) || (pinconfig == NULL)){
        ret = E_NOK;
        printf("User Entered invalid PIN Location or NULL POINTER\n");
    }
    else{
        switch (pinconfig->direction){
            case OUTPUT:
                CLEARBIT(*TRIS_Reg[pinconfig->port],pinconfig->pin);
                break;
            case INPUT:
                SETBIT  (*TRIS_Reg[pinconfig->port],pinconfig->pin);
                break;
            default:
                ret = E_NOK;
                break;
        }
        ret = PINWRITE(pinconfig, pinconfig->logic);
    }
    return ret;
}

uint8_t PINWRITE   (const PinConfig_t * pinconfig, uint8_t log){
    uint8_t ret = E_OK;
    if((pinconfig->logic > 1) || (pinconfig == NULL)){
        ret = E_NOK;
        printf("User Entered invalid Logic or NULL POINTER\n");
    }
    else{
        switch (log){
            case LOW:
                CLEARBIT(*LAT_Reg[pinconfig->port],pinconfig->pin);
                break;
            case HIGH:
                SETBIT  (*LAT_Reg[pinconfig->port],pinconfig->pin);
                break;
            default:
                ret = E_NOK;
                break;
        }
    }
    return ret;
}
#endif
/******************** 4bit LCD FUNC ************************/
uint8_t LCD4B_SET         (const LCD4B_t *lcd){
    uint8_t ret = E_OK;
    if (lcd == NULL){
        ret= E_NOK;
    }
    else{
        PinConfig_t pinptr = {.pin = lcd->REpin, .port=lcd->REport, 
                            .direction = OUTPUT, .logic = LOW  };
        ret = PINSTART(&pinptr);
        pinptr.pin = lcd->ENpin;
        pinptr.port = lcd->ENport;
        ret = PINSTART(&pinptr);
        for (int i = 0; i < 4; i++){
            PinConfig_t pinptr = {.pin = lcd->datapins[i], .port=lcd->dataport[i], 
                                .direction = OUTPUT, .logic = LOW  };
            ret = PINSTART(&pinptr);         
        }
        //initialization process
        __delay_ms(20);
        ret = LCD4B_SENDCMD(lcd,LCD8bit2line);
        __delay_ms(5);
        ret = LCD4B_SENDCMD(lcd,LCD8bit2line);
        __delay_ms(150);
        ret = LCD4B_SENDCMD(lcd,LCD8bit2line);
        //starting setting
        ret = LCD4B_SENDCMD(lcd,LCDclear);
        ret = LCD4B_SENDCMD(lcd,LCDreturnhome);
        ret = LCD4B_SENDCMD(lcd,LCDentrymode);
        ret = LCD4B_SENDCMD(lcd,LCDcurOFFdisON);
        ret = LCD4B_SENDCMD(lcd,LCD4bit2line);
        ret = LCD4B_SENDCMD(lcd,LCDDDRAMSTART);
    }
    return ret;
}

uint8_t LCD4B_SENDCMD     (const LCD4B_t *lcd, uint8_t cmd){
    uint8_t ret = E_OK;
    if (lcd == NULL){
        ret= E_NOK;
    }
    else{
        PinConfig_t pinptr = {.pin = lcd->REpin, .port=lcd->REport, 
                            .direction = OUTPUT, .logic = LOW  };
        ret = PINWRITE(&pinptr,LOW);
        for (int i = 0; i < 4; i++){
            pinptr.pin  = lcd->datapins[i];
            pinptr.port = lcd->dataport[i];
            ret  = PINWRITE(&pinptr,(cmd >> (i+4))&(uint8_t)0x01);
        }
        ret = sendenable(lcd);
        for (int i = 0; i < 4; i++){
            pinptr.pin  = lcd->datapins[i];
            pinptr.port = lcd->dataport[i];
            ret  = PINWRITE(&pinptr,(cmd >> i)&(uint8_t)0x01);
        }
        ret = sendenable(lcd);
    }
    return ret;
}

uint8_t LCD4B_SENDCHAR    (const LCD4B_t *lcd, uint8_t data){
    uint8_t ret = E_OK;
    if (lcd == NULL){
        ret= E_NOK;
    }
    else{
        PinConfig_t pinptr = {.pin = lcd->REpin, .port=lcd->REport, 
                            .direction = OUTPUT, .logic = LOW  };
        ret = PINWRITE(&pinptr,HIGH);
        for (int i = 0; i < 4; i++){
            pinptr.pin  = lcd->datapins[i];
            pinptr.port = lcd->dataport[i];
            ret  = PINWRITE(&pinptr,(data >> (i+4))&(uint8_t)0x01);
        }
        ret = sendenable(lcd);
        for (int i = 0; i < 4; i++){
            pinptr.pin  = lcd->datapins[i];
            pinptr.port = lcd->dataport[i];
            ret  = PINWRITE(&pinptr,(data >> i)&(uint8_t)0x01);
        }
        ret = sendenable(lcd);
    }
    return ret;
}

uint8_t LCD4B_SENDCHARPOS (const LCD4B_t *lcd, uint8_t data, uint8_t row, uint8_t column){
    uint8_t ret = E_OK;
    if (lcd == NULL){
        ret= E_NOK;
    }
    else{
        ret = setcursor4bit(lcd,row,column);
        PinConfig_t pinptr = {.pin = lcd->REpin, .port=lcd->REport, 
                            .direction = OUTPUT, .logic = LOW  };
        ret = PINWRITE(&pinptr,HIGH);
        ret = send4bit(lcd, data >> 4);
        ret = sendenable(lcd);
        ret = send4bit(lcd, data);
        ret = sendenable(lcd);
    }
    return ret;
}

uint8_t LCD4B_SENDSTR     (const LCD4B_t *lcd, uint8_t *str){
    uint8_t ret = E_OK;
    uint8_t *str_old = str;
    uint8_t length = (uint8_t)strlen((const char *)str);
    if (lcd == NULL){
        ret= E_NOK;
    }
    else{
        while(length--){
            ret = LCD4B_SENDCHAR(lcd,*str++);
        }
        //reset the given pointer to its original location
        str = str_old;
    }
    return ret;
}

uint8_t LCD4B_SENDSTRPOS  (const LCD4B_t *lcd, uint8_t *str, uint8_t row, uint8_t column){
    uint8_t ret = E_OK;
    if (lcd == NULL){
        ret= E_NOK;
    }
    else{
        ret = setcursor4bit(lcd,row,column);
        while(*str){
            ret = LCD4B_SENDCHAR(lcd,*str++);
        }
    }
    return ret;
}

uint8_t LCD4B_SENDCUSTOMCHAR(const LCD4B_t *lcd, uint8_t row, uint8_t column,
                         const uint8_t chr[],uint8_t mem_pos){
    uint8_t ret = E_OK;
    if (lcd == NULL){
        ret= E_NOK;
    }
    else{
        ret = LCD4B_SENDCMD(lcd, LCDCGROMSTART + (mem_pos * 8));
        for (int i = 0; i <7 ; i++){
            ret = LCD4B_SENDCHAR(lcd, chr[i]);
        }
        LCD4B_SENDCHARPOS(lcd,mem_pos,row,column);
    }
    return ret;
}

/**************************helper FUNC Definition *************/
static uint8_t send4bit (const LCD4B_t * lcd, uint8_t data){
    uint8_t ret = E_OK;
    for (int i = 0; i<4; i++){
        PinConfig_t pinobj = {.pin = lcd->datapins[i], .port=lcd->dataport[i], 
                            .direction = OUTPUT, .logic = LOW  };
        ret = PINWRITE(&pinobj, (data >> i) & (uint8_t)0x01);
    }
    return ret;
}

static uint8_t sendenable(const LCD4B_t * lcd){
    uint8_t ret = E_OK;
    PinConfig_t pinEN = {.pin = lcd->ENpin, .port=lcd->ENport, 
                            .direction = OUTPUT, .logic = LOW  };
    ret = PINWRITE(&pinEN,HIGH);
    __delay_us(10);
    ret = PINWRITE(&pinEN,LOW);
    return ret;    
}

static uint8_t setcursor4bit (const LCD4B_t *lcd, uint8_t row, uint8_t col){
    uint8_t ret = E_OK;
    col--;
    switch(row){
        case 1: ret = LCD4B_SENDCMD(lcd,(0x80 + col)); break;
        case 2: ret = LCD4B_SENDCMD(lcd,(0xc0 + col)); break;
        case 3: ret = LCD4B_SENDCMD(lcd,(0x94 + col)); break;
        case 4: ret = LCD4B_SENDCMD(lcd,(0xd4 + col)); break;
        default: ret = E_NOK; break;       
    }
    return ret; 
}
