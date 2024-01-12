# Smart Home System Interfacing

A smart home system designed in Proteus 8 Pro and coded in MPLAB X IDE for PIC18F46K20 microcontrollers.

This system was developed as the final project for the MCU Interfacing phase in an Embedded Systems diploma under the guidance of Eng. Ahmed Abd-El Ghafar El Kenany. Additionally, it includes a smart gate and lighting system based on my personal research.

The system is divided into four main sections:
  * I2C Bus Network.
  * Temperature Regulation System.
  * Smart Gate System.
  * Automatic Lighting Control System.
  
In addition, there is an LCD unit to display the current date, time, and temperature data read by the MCUs.

![Full Smart Home Network](https://github.com/amr-salah-abdullah/Smart-Home-System-interfacing/assets/156439432/19933318-9b5f-41d9-96f0-8260f4fab16f)

## I2C Bus Network

The network is primarily defined as a single-master-multi-slave communication network using the I2C bus feature of the used MCU.

The network consists of:
* Master
   * PIC18F46K20 8-bit Microcontroller (configured as Master).
* Slaves
   * PIC18F46K20 8-bit Microcontroller (configured as Slave).
   * Two 24C02C EEPROM Modules.
   * DS1307 Clock module with a 32 KHZ crystal.
   * TC74 temperature sensor.
   
Additionally, there is a virtual I2C debugger for displaying the current communication messages' states.

![I2C Bus Network](https://github.com/amr-salah-abdullah/Smart-Home-System-interfacing/assets/156439432/44418b95-86db-4758-9a47-4d53231cf071)

The EEPROM modules serve as periodic backup storage for the current states of the system modules (e.g., is the gate opened/closed, is the light on/off). The clock module provides the current date/time and a stable ticking source for time syncing between the system modules.

Note: The clock module can be configured by the user input in the Master MCU to generate a square wave output based on the supplied frequency from the attached crystal.

![Screenshot 2024-01-12 204954](https://github.com/amr-salah-abdullah/Smart-Home-System-interfacing/assets/156439432/f2f66dcc-3f8b-49f6-b864-8a1ef031202c)

## Temperature Regulation System

The system consists of:
* PIC18F46K20 8-bit Microcontroller (configured as Slave).
* TC74 temperature sensor.
* L298n motor driver.
* DC motor (fan motor).

![Temperature Control System](https://github.com/amr-salah-abdullah/Smart-Home-System-interfacing/assets/156439432/c5574184-2030-4b78-b31e-54407b5adc1a)

As mentioned in the I2C network section, temperature readings are transmitted through the I2C network to the Slave MCU for further processing. The MCU controls the fan speed by providing a PWM signal with a variable duty cycle and a fixed frequency of 4 kHz.

The fan controller logic works as follows:
* The target temperature is set to be maintained in the range of 30-35°C.
* If the temperature exceeds 35°C, the fan will start operating with a 50% duty cycle.
* If the temperature continues to rise, reaching 40°C, the duty cycle increases to 75%, speeding up the fan.
* Once the temperature drops below 30°C, the fan will automatically shut down and won't turn on until the temperature reaches 35°C.

Note: There is a short period where the fan follows the last action state between 31-34°C (if the temperature was dropping from 35°C, then the fan will stay active regardless of dropping below 35°C, and vice versa).

Note: While it's common to use single-phase induction motors for fans, the Proteus simulator did not have available induction motor models, so DC motors were used for demonstration purposes.

## Smart Gate System

The gate system consists of:
* PIC18F46K20 8-bit Microcontroller (configured as Slave).
* L298n motor driver.
* DC motor (Gate motor).
* A button in active-high configuration.
* Buzzer with an NPN BJT transistor circuit.

![Smart Gate System](https://github.com/amr-salah-abdullah/Smart-Home-System-interfacing/assets/156439432/25f6aa57-5bd8-4cdb-82d9-fe742476682e)

The gate operation relies on a single button input. The same button can both open and close the gate based on its last stationary state (was the gate open or closed?). The gate also memorizes its last stationary state even if the power goes out by recording the last state in the EEPROM inside the MCU and reading it every time the button is pressed.

In the practical world, motors do not instantly stop once the power is cut from the terminals. Thus, a break period is necessary to avoid damaging the motor. If the user tries to run the gate motor right after or during the operating period, a buzzer is set to alarm the user that the motor is still not stationary - ready for reversing - yet to begin another operating cycle.

Once a set time has passed from the first cycle, the motor can start operating in the reverse direction.

Note: The system operates on the first positive edge applied to the Slave MCU using the external interruption routine INTx pins (in this case, INT0 was used).

## Automatic Lighting Control 

The main idea of this system is having lighting units that automatically switch ON/OFF without the need for manual interactions.

![Smart Lighting System](https://github.com/amr-salah-abdullah/Smart-Home-System-interfacing/assets/156439432/7093619c-9544-44e4-85e2-f428b284c501)

This is applied through two techniques:

### 1. Using LDR Sensor.

This technique controls the main home lighting unit in the simulation and consists of:
* LDR sensor.
* Manual Control button.
* Lamp/LED (Home Lighting unit).

The system is set so that as the sun sets and the resistance of the LDR increases (light detected is getting lower), a lower value is detected on the analog input on the MCU. Until a certain threshold is reached, causing the lamp (home lighting) to turn ON, and vice versa.

The button exists as a means for the user to manually turn ON/OFF the lighting, effectively switching off the automatic controls until the user decides to turn it back on again or it automatically resets (turn the automatic control back on) when a certain time frame is reached.

This method has the advantage of adaptation to the change in the day-night cycle (nights are shorter during the summer and longer during the winter). However, it requires a shade-free environment to work properly (any shade might count as a signal to turn on the lighting).

### 2. Using a Time-Based turn ON/OFF.

This technique controls the main home lighting unit in the simulation and consists of:
* LDR sensor.
* Manual Control button.
* Lamp/LED (Outside Lighting unit).

The system uses time readings from the clock module to decide on a target range at which the lamp turns ON (for this case, it's set to turn on the lamp from 06:00 PM to 04:00 AM).

The button exists as a means for the user to manually turn ON/OFF the lighting, effectively switching off the automatic controls until the user decides to turn it back on again or it automatically resets (turn the automatic control back on) when a certain time frame is reached.

This method has the better advantage of utilizing fewer components while still effectively working in a similar operating range compared to the first method.

Note: Both systems' automatic controls can be reset or toggled by the same automatic control button (if one is off, then the MCU sends a signal to turn both back on. If both are ON/OFF, the button will toggle their current state - ON to OFF and vice versa).

Note: The automatic control button also toggles the main lighting as it's expected to be the most commonly used.

## The Display Units

To display the current occupying data on the MCU, an LCD display is used to show the current Date, Time, and temperature readings of the temperature sensor. Also, the date and time data are sent through the UART module on the Master MCU for any later clock sync requirements on external communication protocols needed (CAN, LIN, etc.).

## Small Notes about the Code

The code is built and configured on MPLAB X IDE as it was the main IDE software upon which the embedded diploma's MCU interfacing phase was taught. The code is made with a layer-based programming technique, meaning every segment of the code is divided for easier modification and replaceability. Any segment can be easily modified without affecting anything that is based on it or from it. The code is split into two folders - one per MCU - each has a similar MCA layer, however, different ECU layer.

## Small Notes about the Simulation

The simulation is built on Proteus 8 Professional version 8.9. The simulation is entirely built from scratch with no external libraries or components needed. On low-end devices, the simulation might be slow, so it's best to just disconnect the FanPWM terminal as it causes the biggest lag on the rest of the simulation. All I2C transmissions are set to trigger within a one-second delay from each other (with an error of ±1ms).

## Special Thanks

I would like to express my sincerest gratitude to Eng. Ahmed Abd-El Ghafar for his amazing impact and outstanding teaching skills without which I wouldn't have had the chance to make such a remarkable project. I highly recommend checking out his Embedded Systems diploma for more information; his LinkedIn page is right [here]((https://www.linkedin.com/in/ahmedabdelghafarmohammed/)).

Thanks to everyone who took the time to read this project description, and I am more than welcome to answer or have a conversation about any segment you found unclear about this project.

Your future colleague,
Amr Salah Abdullah
