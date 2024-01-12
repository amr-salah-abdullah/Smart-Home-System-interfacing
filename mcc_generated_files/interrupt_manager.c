/**
  Generated Interrupt Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K20
        Driver Version    :  2.12
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above or later
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

#include "interrupt_manager.h"
#include "mcc.h"

void  INTERRUPT_Initialize (void)
{
    // Enable Interrupt Priority Vectors
    RCONbits.IPEN = 1;

    // Assign peripheral interrupt priority vectors

    // Interrupt INT0I has no priority bit. It will always be called from the High Interrupt Vector

    // INT1I - high priority
    INTCON3bits.INT1IP = 1;

    // INT2I - high priority
    INTCON3bits.INT2IP = 1;

    // SSPI - high priority
    IPR1bits.SSPIP = 1;

    // BCLI - high priority
    IPR2bits.BCLIP = 1;


    // ADI - low priority
    IPR1bits.ADIP = 0;    

}

void __interrupt() INTERRUPT_InterruptManagerHigh (void)
{
   // interrupt handler
    if(INTCONbits.INT0IE == 1 && INTCONbits.INT0IF == 1)
    {
        INT0_ISR();
    }
    else if(INTCON3bits.INT1IE == 1 && INTCON3bits.INT1IF == 1)
    {
        INT1_ISR();
    }
    else if(INTCON3bits.INT2IE == 1 && INTCON3bits.INT2IF == 1)
    {
        INT2_ISR();
    }
    else if(PIE1bits.SSPIE == 1 && PIR1bits.SSPIF == 1)
    {
        MSSP_InterruptHandler();
    }
    else if(PIE2bits.BCLIE == 1 && PIR2bits.BCLIF == 1)
    {
        MSSP_InterruptHandler();
    }
    else
    {
        //Unhandled Interrupt
    }
}

void __interrupt(low_priority) INTERRUPT_InterruptManagerLow (void)
{
    // interrupt handler
    if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
    {
        ADC_ISR();
    }
    else
    {
        //Unhandled Interrupt
    }
}
/**
 End of File
*/
