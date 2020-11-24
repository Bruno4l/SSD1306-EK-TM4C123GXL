# SSD1306-EK-TM4C123GXL

This is a driver for 128x32 oled screens that use SSD1306 and communicate through the I2C protocol.

This drive was developed in the IAR Embedded Workbench. For more information about how to use: [Tiva™ for C Series Development and Evaluation Kits for IAR Embedded Workbench®](https://www.ti.com/lit/ml/spmu354/spmu354.pdf?ts=1606222928076&ref_url=https%253A%252F%252Fwww.ti.com%252Ftool%252FEK-TM4C123GXL)

To use this driver you will need to download and use [TivaWare](https://www.ti.com/tool/download/SW-TM4C).

This code works perfectly on the [EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL) (ARM® Cortex®-M4F Based MCU TM4C123G LaunchPad ™ Evaluation Kit). Still, use it at your own risk, especially on other launchpads.

## Documentation
Before using the OLED functions you'll need to configure the I2C communication. In this example we will use TM4C123GH6PM's I2C3.
See full example [here](https://github.com/Bruno4l/SSD1306-EK-TM4C123GXL/blob/main/main.c).
```C
/*
 *  You can change the I2C module configuration.
 *  In this example we will use the I2C3
 */
void I2C_3_config(){
  SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  GPIOPinConfigure(GPIO_PD0_I2C3SCL);
  GPIOPinConfigure(GPIO_PD1_I2C3SDA);
  GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
  GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);
  I2CMasterInitExpClk(I2C3_BASE, SysCtlClockGet(), false);
  
  // Pull up I2C3 by PB6 and PB7 pins
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_6);
  GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_7);
  GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD_WPU);
}

/* 
 * This function with this name (I2C_sendSingleByte) is necessary for the operation.
 * You can change the I2C module by changing the I2C3_BASE to the desired module
 */
void I2C_sendSingleByte(uint8_t slave_addr, char data){
  I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, false);
  I2CMasterDataPut(I2C3_BASE, data);
  I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);
  while(I2CMasterBusy(I2C3_BASE));
}

/* 
 * This function with this name (I2C_sendMultipleBytes) is necessary for the operation.
 * You can change the I2C module by changing the I2C3_BASE to the desired module
 */
void I2C_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[]){
  uint8_t i;
  I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, false);
  I2CMasterDataPut(I2C3_BASE, by[0]);
  I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
  while(I2CMasterBusy(I2C3_BASE));
  for(i = 1; i < numOfBytes - 1; i++){
    I2CMasterDataPut(I2C3_BASE, by[i]);
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
    while(I2CMasterBusy(I2C3_BASE));
  }
  I2CMasterDataPut(I2C3_BASE, by[numOfBytes - 1]);
  I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
  while(I2CMasterBusy(I2C3_BASE));
}
```
Functions for the OLED display:
```c
void OLED_Init(void);
void OLED_sendStrXY( char *string, int X, int Y);
void OLED_setXY(unsigned char row,unsigned char col);
void OLED_sendCharXY(unsigned char data, int X, int Y);
void OLED_sendChar(unsigned char data);
void OLED_displayOn(void);
void OLED_displayOff(void);
void OLED_clearDisplay(void);
void OLED_resetDisplay(void);
void OLED_printBigNumber(char string, int X, int Y);
```

## License and Copyright
[MIT License](https://github.com/Bruno4l/SSD1306-EK-TM4C123GXL/blob/main/LICENSE)
