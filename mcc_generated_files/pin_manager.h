/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K20
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LDR aliases
#define LDR_TRIS                 TRISAbits.TRISA0
#define LDR_LAT                  LATAbits.LATA0
#define LDR_PORT                 PORTAbits.RA0
#define LDR_ANS                  ANSELbits.ANS0
#define LDR_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LDR_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LDR_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LDR_GetValue()           PORTAbits.RA0
#define LDR_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LDR_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LDR_SetAnalogMode()      do { ANSELbits.ANS0 = 1; } while(0)
#define LDR_SetDigitalMode()     do { ANSELbits.ANS0 = 0; } while(0)

// get/set Home aliases
#define Home_TRIS                 TRISAbits.TRISA3
#define Home_LAT                  LATAbits.LATA3
#define Home_PORT                 PORTAbits.RA3
#define Home_ANS                  ANSELbits.ANS3
#define Home_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define Home_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define Home_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define Home_GetValue()           PORTAbits.RA3
#define Home_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define Home_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define Home_SetAnalogMode()      do { ANSELbits.ANS3 = 1; } while(0)
#define Home_SetDigitalMode()     do { ANSELbits.ANS3 = 0; } while(0)

// get/set Door aliases
#define Door_TRIS                 TRISAbits.TRISA4
#define Door_LAT                  LATAbits.LATA4
#define Door_PORT                 PORTAbits.RA4
#define Door_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define Door_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define Door_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define Door_GetValue()           PORTAbits.RA4
#define Door_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define Door_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELHbits.ANS12 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELHbits.ANS12 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELHbits.ANS10 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELHbits.ANS10 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELHbits.ANS8 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELHbits.ANS8 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)

// get/set LED aliases
#define LED_TRIS                 TRISDbits.TRISD0
#define LED_LAT                  LATDbits.LATD0
#define LED_PORT                 PORTDbits.RD0
#define LED_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define LED_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define LED_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define LED_GetValue()           PORTDbits.RD0
#define LED_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/