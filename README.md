Following repository contains HAL C code for interfacing a 1602 LCD I2C controller module - AIP31068 with STM32U545RE-Q microcontroller for displaying a moving word.
AIP31068 is a 40 SEG / 16 COM driver & controller for dot matrix LCD supporting I2C communication protocol. The data sheet of the LCD module is:
https://support.newhavendisplay.com/hc/en-us/article_attachments/4414498095511
. Only the main source files are added in this repository as the rest of the files are generated automatically by the STMCubeIDE.
The target microcontroller - STM32U545RE-Q is selected in the STMCubeMX, matching the hardware.
LCD is initialized by the respective commands as described in the data sheet of the LCD controller.
Following main code includes the initialization of the LCD module, sending commands and data to the LCD and displaying a moving word.
