/**
  File Name: main.c
  Summary: main code of the master MCU of the project. 
  Auther: Amr Salah Abdullah
*/

/************** Includes section *************/
#include "mcc_generated_files/mcc.h"
#include "AECUL/RealTimerClockDS1307/RealTimerCLock.h"
#include "AECUL/ExtEEPROM/ExtEEPROM.h"
#include "AECUL/TC74/TC74.h"
#include "mcc_generated_files/examples/i2c_master_example.h"
#include "AECUL/LCD_LM016L/LCD.h"

/************** Variables Initialization *************/
#define ON      0x01
#define OFF     0x00

DateAndTime_t   timer;
uint8_t         TCA7temp = 0;
uint8_t         EEPROMreading = 0;
uint16_t        lightread = 0;
uint8_t         homelightauto = 1;
uint8_t         doorlightauto = 1;
uint8_t         autocont = 1;
uint8_t         LCDtemp[4];

LCD4B_t lcd ={
    .ENpin = 1,  .REpin= 0,
    .ENport= 3,  .REport= 3,
    .datapins = {2,3,4,5},
    .dataport = {3,3,3,3},   
};
/************** Functions Declaration *************/
void lightSwitch(void);
void manual_Override(void);
void manual_homelight(void);
void manual_Doorlight(void);
void clockReading(void);
/************** main code here *************/
void main(void)
{
    /* Initialize the device */
    SYSTEM_Initialize();
    //initializing the Interruption routines functions pointers
    ADC_SetInterruptHandler(lightSwitch);
    //TMR0_SetInterruptHandler(clockReading);
    
    INT0_SetInterruptHandler(manual_Override);
    INT1_SetInterruptHandler(manual_homelight);
    INT2_SetInterruptHandler(manual_Doorlight); 
    
    // Saving Data to Two External EEPROM
    EXTEEPROM_WriteByte(0x50, 0x00, 0x07);
    __delay_ms(500);
    EXTEEPROM_WriteByte(0x51, 0x00, 0x08);
    __delay_ms(500);
    // Reading the Data Stored in One of the EEPROMs
    EEPROMreading = EXTEEPROM_ReadByte(0x50, 0x00);
    __delay_ms(500);
    //initialize the LCD module
    LCD4B_SET(&lcd);
    
    // the Looping Code        
    while (1){
        // Read the current date and time data from the external clock.
        timer = GetDataAndTime(); 
        // Print the current date and time on the Tx output pin.
        PrintDateUART();
        PrintTimeUART();
        
        // Read the current Temperature sensor current value.
        TCA7temp = ReadTemp(0x4F);
        //int2str(TCA7temp,LCDtemp);
        sprintf((char *)LCDtemp,"%u",TCA7temp);
        // Send the Temperature Readings to the Slave MCU.
        I2C_Write1ByteRegister(0x38,0x00,TCA7temp);
        
        if (homelightauto == ON){
            // Read the current lighting level from the LDR unit.
            lightread = ADC_GetConversion(LDR);      
        }  
        __delay_ms(200);
        
        
        //display the current date, time and thermal level
        //also print the current date and time on the UART channel
        LCD4B_SENDCHAR(&lcd,LCDclear);
        LCD4B_SENDSTRPOS(&lcd,(uint8_t *)"Date: ",1,1);
        LCD4B_SENDSTR(&lcd,DatetoString());
        LCD4B_SENDSTRPOS(&lcd,(uint8_t *)"Time: ",2,1);
        LCD4B_SENDSTR(&lcd,TimetoString());
        LCD4B_SENDSTRPOS(&lcd,(uint8_t *)"TEMP: ",3,1);
        LCD4B_SENDSTR(&lcd,LCDtemp);
        
        //turn back ON the automatic system at 7 am in the morning.
        if (timer.hour == 0x08){
            homelightauto = ON;
            doorlightauto = ON;
        }
        __delay_ms(737);
    }
}
/**
 * @Param: 
 *      none.
 * @Summary: 
 *      interruption routine for for when a reading is received 
 *      from the LDR sensor.
 * @Return: 
 *      none
 */
void lightSwitch(void){
    if (homelightauto == ON){    
        // Based on current lighting level; turn ON/OFF the home lighting
        if (lightread <= 10000){
            Home_SetHigh();
        } else {
            Home_SetLow();
        }
    }
    if (doorlightauto == ON){
        // Based on the current time; turn ON/OFF the front door lighting
        // if it's between 06:00 PM and 04:00 AM turn on the front door light
        if ((timer.hour >= 0x18)||(timer.hour <= 0x04)){
            Door_SetHigh(); 
        } else {
            Door_SetLow();
        }       
    }
}
/**
 * @Param: 
 *      none.
 * @Summary: 
 *      manual control toggle for all auto lighting units.
 * @Return: 
 *      none
 */
void manual_Override(void){
    if (homelightauto == doorlightauto){
        //toggle the home light controls
        if (homelightauto == ON){
            Home_Toggle();    
            homelightauto = OFF;
        } 
        else if (homelightauto == OFF){
            homelightauto = ON;
        } 
        else {
            homelightauto = ON;
        }
        //toggle the door light controls
        if (doorlightauto == ON)     {doorlightauto = OFF;} 
        else if (doorlightauto == OFF){doorlightauto = ON;} 
        else                        {doorlightauto = ON;}
        } 
    
    else{  
        //ENable back all the automatic switches
        homelightauto = ON;
        doorlightauto = ON;
    }     
}
/**
 * @Param: 
 *      none.
 * @Summary: 
 *      manual control for Home lighting button actions.
 * @Return: 
 *      none
 */
void manual_homelight(void){
    // Toggle the Home Lighting state.
    Home_Toggle();  
    // Disable the auto Home Lighting switching.
    homelightauto = OFF;
} 
/**
 * @Param: 
 *      none.
 * @Summary: 
 *      manual control for Door lighting button actions.
 * @Return: 
 *      none
 */
void manual_Doorlight(void){
    // Toggle the Door Lighting state.
    Door_Toggle();  
    // Disable the auto Door Lighting switching.
    doorlightauto = OFF;
}
/**
 * @Param: 
 *      none.
 * @Summary: 
 *      read the clock data once every one second using the TMR0 module
 * @Return: 
 *      none
 */
