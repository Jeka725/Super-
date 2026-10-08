#include <Arduino.h>
#include <TFT_eSPI.h>
#include "esp_system.h"

TFT_eSPI tft = TFT_eSPI();

static void screenInfo() {
  Serial.println();
  Serial.println("=== SUPER 1.8 TFT ST7735S TESTER ===");
  Serial.println("Rotation: 180 degrees");
  Serial.println("Resolution: 128x160");
  Serial.println("SPI: SCK=5 MOSI=6 CS=16 DC=7 RST=15 BL=4");
}

static void solid(uint16_t color, const char* name) {
  tft.fillScreen(color);
  Serial.print("TEST: ");
  Serial.println(name);
  delay(1500);
}

static void colorBars() {
  const uint16_t colors[] = {
    TFT_RED, TFT_GREEN, TFT_BLUE, TFT_CYAN,
    TFT_MAGENTA, TFT_YELLOW, TFT_WHITE, TFT_BLACK
  };
  const char* names[] = {
    "RED", "GREEN", "BLUE", "CYAN",
    "MAGENTA", "YELLOW", "WHITE", "BLACK"
  };
  const int barH = tft.height() / 8;
  for (int i = 0; i < 8; ++i) {
    tft.fillRect(0, i * barH, tft.width(), barH, colors[i]);
    Serial.print("BAR: ");
    Serial.println(names[i]);
  }
  delay(2500);
}

static void checkerboard() {
  const int cell = 16;
  for (int y = 0; y < tft.height(); y += cell) {
    for (int x = 0; x < tft.width(); x += cell) {
      bool on = ((x / cell) + (y / cell)) & 1;
      tft.fillRect(x, y, cell, cell, on ? TFT_WHITE : TFT_BLACK);
    }
  }
  delay(2500);
}

static void borderAndGrid() {
  tft.fillScreen(TFT_BLACK);
  tft.drawRect(0, 0, tft.width() - 1, tft.height() - 1, TFT_WHITE);
  for (int x = 0; x < tft.width(); x += 8)
    tft.drawFastVLine(x, 0, tft.height(), TFT_DARKGREY);
  for (int y = 0; y < tft.height(); y += 8)
    tft.drawFastHLine(0, y, tft.width(), TFT_DARKGREY);
  tft.drawRect(2, 2, tft.width() - 5, tft.height() - 5, TFT_RED);
  delay(2500);
}

void setup() {
  Serial.begin(115200);
  delay(300);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  screenInfo();
  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);

  Serial.println("DISPLAY INIT OK");

  solid(TFT_BLACK, "BLACK");
  solid(TFT_WHITE, "WHITE");
  solid(TFT_RED, "RED");
  solid(TFT_GREEN, "GREEN");
  solid(TFT_BLUE, "BLUE");
  solid(TFT_YELLOW, "YELLOW");
  solid(TFT_CYAN, "CYAN");
  solid(TFT_MAGENTA, "MAGENTA");
  colorBars();
  checkerboard();
  borderAndGrid();

  Serial.println("TEST COMPLETE - repeating");
}

void loop() {
  colorBars();
  checkerboard();
  borderAndGrid();
}
