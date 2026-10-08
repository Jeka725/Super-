#include <Arduino.h>
#include <TFT_eSPI.h>
#include "esp_system.h"

static TFT_eSPI* tft = nullptr;

static uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  return tft->color565(r, g, b);
}

static void printResetInfo() {
  Serial.println();
  Serial.println("=== SUPER SAFE BOOT ===");
  Serial.print("reset reason = ");
  Serial.println((int)esp_reset_reason());
  Serial.print("flash size = ");
  Serial.println(ESP.getFlashChipSize());
  Serial.print("free heap = ");
  Serial.println(ESP.getFreeHeap());
}

static void drawIntro(uint32_t t) {
  tft->fillScreen(TFT_BLACK);

  const int pulse = 10 + (int)((sinf(t * 0.004f) + 1.0f) * 8.0f);
  for (int r = 34; r >= 8; r -= 5) {
    const uint8_t b = (uint8_t)(90 + pulse * 6 - (34 - r) * 2);
    tft->drawCircle(64, 68, r, rgb(15, b / 2, b));
  }

  tft->fillCircle(64, 68, pulse / 2, rgb(35, 90, 255));

  tft->setTextDatum(MC_DATUM);
  tft->setTextFont(4);
  tft->setTextColor(rgb(40, 120, 255), TFT_BLACK);
  tft->drawString("SUPER", 64, 116);

  tft->setTextFont(1);
  tft->setTextColor(rgb(100, 130, 190), TFT_BLACK);
  tft->drawString("ESP32-S3 / ST7735S", 64, 139);
}

void setup() {
  // Nothing display-related is constructed before setup().
  Serial.begin(115200);
  delay(500);
  printResetInfo();

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW);

  Serial.println("Creating TFT driver...");
  tft = new TFT_eSPI();
  delay(100);

  Serial.println("Calling TFT init...");
  tft->init();
  Serial.println("TFT init returned.");

  tft->setRotation(2);
  tft->fillScreen(TFT_BLACK);

  digitalWrite(TFT_BL, HIGH);
  Serial.println("SUPER display OK.");
}

void loop() {
  if (tft == nullptr) {
    delay(1000);
    return;
  }

  drawIntro(millis());
  delay(55);
  yield();
}
