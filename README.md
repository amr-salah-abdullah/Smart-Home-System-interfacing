# Smart-Home-System-interfacing
A smart home system designed on Proteus 8 pro and coded on MPLAP X IDE for PIC18F46K20 microcontrollers

The following system was designed as a finale project for the MCU Interfacing phase in an Embedded systems deploma made by Eng. Ahmed abd-El Ghafar El kenany 
with the addition of the smart gate and lighting system from my personal research purposes.

The system is divided into 4 main sections:
  * I2C Bus Network.
  * Temperature regulation system.
  * Smart Gate system.
  * Automatic lighting control system.
with the added addition of an LCD unit to display the current date, time and temperature data read by the MCUs.

![Smart Home model display](/Full Smart Home Network.png)

## I2C Bus Network

The network can be mainly defined as a single-master-multi-slave communication network using the I2C bus feature of the used MCU

The network cosists of:
* Master
   * A PIC18F46k20 8-bit Microcontroller (configured as Master).
* Slaves
   * A PIC18F46k20 8-bit Microcontroller (configured as Slave).
   * Two 24C02C EEPROM Modules.
   * A DS1307 Clock module with a 32 KHZ crystal.
   * A TC74 temperature sensor
and a vertual I2C debugger for displaying the current communication messages states


The EEPROM modules are used as a periodic backup storage for the current states of the  
   
