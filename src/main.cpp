#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

static uint32_t frameNo = 0;
static uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(r,g,b);
}

void drawStarfield(uint32_t t) {
  tft.fillScreen(TFT_BLACK);

  // Deterministic animated star field
  for (int i = 0; i < 46; ++i) {
    uint32_t seed = 0x9E3779B9u * (i + 1);
    int x = (seed >> 8) % 128;
    int baseY = (seed >> 17) % 190;
    int speed = 1 + (seed % 3);
    int y = (baseY + (t / (45 / speed + 1))) % 190 - 15;

    uint8_t b = 80 + ((seed >> 24) & 0x7F);
    uint8_t s = 1 + ((seed >> 29) & 1);
    tft.fillRect(x, y, s, s, rgb(b/3,b/2,b));
  }

  // Moving neon rings
  int cx = 64, cy = 76;
  int pulse = (t / 30) % 20;
  for (int r = 18 + pulse; r >= 8; r -= 5) {
    uint8_t a = 255 - (18 + pulse - r) * 7;
    tft.drawCircle(cx, cy, r, rgb(30, a/2, a));
  }

  // Central energy core
  int core = 6 + ((t / 55) % 3);
  for (int r = core + 5; r >= 1; --r) {
    uint8_t k = 255 - (r * 22);
    if (k < 30) k = 30;
    tft.fillCircle(cx, cy, r, rgb(k/4, k/2, k));
  }

  // Energy beams
  int sweep = (t / 7) % 360;
  for (int a = 0; a < 360; a += 45) {
    float rad = (a + sweep) * 0.0174533f;
    int x = cx + (int)(cosf(rad) * 54);
    int y = cy + (int)(sinf(rad) * 70);
    tft.drawLine(cx, cy, x, y, rgb(12, 42, 95));
  }
}

void drawSuperText(uint32_t t) {
  // Fade-like pulsing title without storing an image/video
  uint8_t pulse = 80 + ((sinf(t * 0.004f) + 1.0f) * 70);
  uint16_t c = rgb(30, pulse/2, 255);

  tft.setTextDatum(MC_DATUM);
  tft.setTextFont(4);
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.drawString("SUPER", 64, 126);

  tft.setTextColor(c, TFT_BLACK);
  tft.drawString("SUPER", 64, 125);

  tft.setTextFont(1);
  tft.setTextColor(rgb(80, 100, 160), TFT_BLACK);
  tft.drawString("ESP32-S3  /  ST7735S", 64, 145);
}

void setup() {
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.init();
  tft.setRotation(2); // 180 degrees
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);

  Serial.begin(115200);
  delay(150);
  Serial.println("SUPER boot animation");
}

void loop() {
  uint32_t t = millis();
  drawStarfield(t);
  drawSuperText(t);
  ++frameNo;
  delay(45); // ~22 FPS, safe for 40 MHz SPI
}
