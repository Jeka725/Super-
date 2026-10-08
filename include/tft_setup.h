#pragma once
#define ST7735_DRIVER
#define TFT_WIDTH  128
#define TFT_HEIGHT 160

#define TFT_MOSI 6
#define TFT_SCLK 5
#define TFT_CS   16
#define TFT_DC   7
#define TFT_RST  15
#define TFT_BL   4

// ST7735S red-board panels commonly use BGR ordering.
#define TFT_RGB_ORDER TFT_BGR

// Start conservatively for stability; raise after the board is proven stable.
#define SPI_FREQUENCY 20000000
