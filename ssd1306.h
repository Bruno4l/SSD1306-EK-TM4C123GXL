#ifndef SSD1306_H_
#define SSD1306_H_

#include <stdint.h>

#define SSD1306_LCDWIDTH      128
#define SSD1306_LCDHEIGHT      64
#define SSD1306_SETCONTRAST   0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

typedef uint8_t bitmap_t[8][128];
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

// Em teste
void OLED_setPixelXY(unsigned char X, unsigned char Y);
void OLED_setPageAddress(void);
void OLED_setColAddress(void);

#endif /* SSD1306_H_ */
