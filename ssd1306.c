#include "ssd1306.h"
#include "i2c.h"
#include <stdint.h>
#include "data.h"

#define slaveAddress 0x3c

void OLED_command(uint8_t c){
  uint8_t control = 0x00;
  char arr[2] = {control, c};
  I2C_sendMultipleBytes(slaveAddress, 2, arr);
}

void  OLED_data(uint8_t c){
  char arr[2] = {0x40, c};
  I2C_sendMultipleBytes(slaveAddress, 2, arr);
}

void OLED_setColAddress(){
  OLED_command(SSD1306_COLUMNADDR); // 0x21 COMMAND
  OLED_command(0); // Column start address
  OLED_command(SSD1306_LCDWIDTH-1); // Column end address
}

void OLED_setPageAddress(){
  OLED_command(SSD1306_PAGEADDR); // 0x22 COMMAND
  OLED_command(0); // Start Page address
  OLED_command((SSD1306_LCDHEIGHT/8)-1);// End Page address
}

void OLED_Init(){
  // Init sequence for 128x32 OLED module
  OLED_command(SSD1306_DISPLAYOFF);                    // 0xAE

  OLED_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
  OLED_command(0x80);                 // the suggested ratio 0x80

  OLED_command(SSD1306_SETMULTIPLEX);                  // 0xA8
  OLED_command(31);    // 0 - 32

  OLED_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
  OLED_command(0x0);                                   // no offset

  OLED_command(SSD1306_SETSTARTLINE);// | 0x0);        // line #0

  OLED_command(SSD1306_CHARGEPUMP);                    // 0x8D
  OLED_command(0x14);  // using internal VCC

  OLED_command(SSD1306_SETCOMPINS);                    // 0xDA
  OLED_command(0x02);

  OLED_command(SSD1306_SETCONTRAST);                   // 0x81
  OLED_command(0x7F);

  OLED_command(SSD1306_SETPRECHARGE);                  // 0xd9
  OLED_command(0x22);

  OLED_command(SSD1306_SETVCOMDETECT);                 // 0xDB
  OLED_command(0x40);

  OLED_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4

  OLED_command(SSD1306_MEMORYMODE); 
  OLED_command(0x00);

  OLED_command(SSD1306_NORMALDISPLAY);                 // 0xA6

  OLED_command(SSD1306_DISPLAYON);                     //switch on OLED
}

void OLED_displayOn(void){
  OLED_command(0xaf);   //display on
}

void OLED_displayOff(void){
  OLED_command(0xae);   //display off
}

void OLED_resetDisplay(void){
  OLED_displayOff();
  OLED_clearDisplay();
  OLED_displayOn();
}

void OLED_clearDisplay(void)
{
  unsigned char i,k;
  for(k=0;k<8;k++)
  {
    OLED_setXY(k,0);
    {
      for(i=0;i<128;i++)
      {
        OLED_sendChar(0);
      }
    }
  }
}

void OLED_sendChar(unsigned char data){
  char arr[2] = {0x40, data};
  I2C_sendMultipleBytes(slaveAddress, 2, arr);
}

void OLED_setXY(unsigned char row,unsigned char col){
  OLED_command(0xb0+row);                //set page address
  OLED_command(0x00+(8*col&0x0f));       //set low col address
  OLED_command(0x10+((8*col>>4)&0x0f));  //set high col address
}

void OLED_setPixelXY(unsigned char X,unsigned char Y){
  OLED_command(0xb0+X);
  OLED_command(0x00+Y&0x0f);
  OLED_command(0x10+((Y>>4)&0x0f));
}

void OLED_sendCharXY(unsigned char data, int X, int Y)
{
  char arr[6];
  uint8_t i;
  OLED_setXY(X, Y);
  arr[0] = 0x40;

  for(i = 0; i < 5; i++)
    arr[i + 1] = ASCII_font5x8[data - 0x20][i];

  I2C_sendMultipleBytes(slaveAddress, 6, arr);
}

void OLED_sendStrXY(char *string, int X, int Y)
{
  int i;
  for(i = 0; string[i] != '\0'; i++){
    OLED_sendCharXY(string[i], X, Y++);
  }
  
}

void OLED_printBigNumber(char string, int X, int Y)
{
  OLED_setXY(X,Y);
  int jump=0;
  for(int i = 0; i < 96; i++)
  {
    
    if(string == ' ') {
      OLED_sendChar(0);
    }else
      OLED_sendChar(bigNumbers[string-0x30][i]);
 
    if(jump == 23) {
        jump = 0;
        X++;
        OLED_setXY(X,Y);
    }else
      jump++;
  }
}