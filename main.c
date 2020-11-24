#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"

#include "i2c.h"
#include "ssd1306.h"

// I2C
#define GPIO_PD0_I2C3SCL 0x00030003
#define GPIO_PD1_I2C3SDA 0x00030403

void I2C_3_config(){ // Configure I2C3 for pins PD0 and PD1
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

void I2C_sendSingleByte(uint8_t slave_addr, char data){
  I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, false);
  I2CMasterDataPut(I2C3_BASE, data);
  I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);
  while(I2CMasterBusy(I2C3_BASE));
}

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

void main (void){
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // 80 MHz
  
  I2C_3_config();
  OLED_Init();
  OLED_clearDisplay();
  OLED_sendCharXY('#', 0, 0);
  OLED_sendStrXY("TEST", 1, 0);
  
  while(1);
}