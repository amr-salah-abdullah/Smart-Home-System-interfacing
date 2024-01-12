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

![Full Smart Home Network](https://github.com/amr-salah-abdullah/Smart-Home-System-interfacing/assets/156439432/19933318-9b5f-41d9-96f0-8260f4fab16f)

## I2C Bus Network

The network can be mainly defined as a single-master-multi-slave communication network using the I2C bus feature of the used MCU

The network cosists of:
* Master
   * PIC18F46k20 8-bit Microcontroller (configured as Master).
* Slaves
   * PIC18F46k20 8-bit Microcontroller (configured as Slave).
   * Two 24C02C EEPROM Modules.
   * DS1307 Clock module with a 32 KHZ crystal.
   * TC74 temperature sensor.
and a vertual I2C debugger for displaying the current communication messages states.

![I2C Bus Network](https://github.com/amr-salah-abdullah/Smart-Home-System-interfacing/assets/156439432/44418b95-86db-4758-9a47-4d53231cf071)

- The EEPROM modules are used as a periodic backup storage for the current states of operation of the system modules - is the gate opened/closed, is the light on/off, ...etc-  
- The clock module is used to define the current date/time and provide a stable ticking source that can be used for time syncing between the system modules.
however, here is mainly used to record the current time variables and send them periodicly every one second to the master MCU.
- The temperature sensor sends periodically the current temperature readings to the Master MCU for decoding, which later sends the decoded readings to the slave MCU to configure the fans target speed.

Note: the clock module can be configured by the user input in the Master MCU to generate a square wave output based on the supplied frequency from the attached crystal

((( image here )))
 
## Temperature Regulation System
The system cosists of:
* PIC18F46k20 8-bit Microcontroller (configured as Slave).
* TC74 temperature sensor.
* L298n motor driver.
* DC motor (fan motor).

- As mentioned in the I2c network section, the temperature readings are fed through the I2C network to later reach the Slave MCU for speed processing.
- the MCU controls the speed by providing a PWM signal of variable duty cycle and a fixed frequency of 4 kHz.
- The fan controller logic works as follows:
	* The target temperature set to be maintained through the code to be in range of 30-35°C. 
	* If the temperature exceeds 35°C, the fan will start operating with a 50% duty cycle being fed to the motor driver.
	* If the temperature kept the rising - regardless of the fan opeating- till it reaches 40°C, The duty cycle will change to 75% effectively speeding up the fan.
	* Once the temperature drops below 30°C the fans will automaticlly shut down and wont turn on until the temperature reaches 35°C.

Note: there is a small period where the fan will follow the last state of action between 31-34°C (if the temperature was droping from 35°C, then the fan will stay active regardless of droping below 35°C, and vice versa; if the temperature was rising from 30°C then the fan will remain off until the temperature reaches 35°C).
Note: while its mostly common to use single phase induction motors for fans, the proteus simulator did not have avilable induction motor models, so i opted for DC motors instead for just the demonstration perposes.

((( image here )))    

## Smart Gate System
the gate system consists of:
* PIC18F46k20 8-bit Microcontroller (configured as Slave).
* L298n motor driver.
* DC motor (Gate motor).
* a button in active High configuration. 
* Buzzer with an NPN BJT transistor circuit.

((( image here )))

- The gate opeartion relys on the a single button input, the same button can both open and close the gate based on its last stationary state (was the gate open or closed?).
- The gate also memorizes its last stationary state even if the power went out by recording the last state in the EEPROM inside the MCU and reading it every time the button is pressed.
- in the practical world, the motors do not instantly stop once the power is cut from the terminals, and thus a break period is a must to avoid damaging the motor. 
This is why if the user tried to instantly run the gate motor right after or during the operating period, a buzzer is set to alarm the user instead that the motor is still not stationary - ready for reversing - yet to begin another operating cycle.
Once the a set time has based from the first cycle, the motor can once again start operating in the reverse direction. 
 
Note: the system operates on the first positive edge applied on the Slave MCU using the external interruption routine INTx pins (in this case INT0 was used).
  
## Automatic Lighting control 

The main idea of this system is having lighting units that automatically switch ON/OFF without the need of manual interactions.

this was applied in here through 2 tecniques:
1. using a LDR (light dependent switch) Sensor mounted to the rood of the house.
2. using a code based set time range that turns ON/OFF the lighting based on readings of the clock module.

### Using LDR Sensor.

### Using a Time Based turn ON/OFF.
