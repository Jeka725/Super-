#include <Arduino.h>
#include "esp_system.h"

void setup() {
  // Hardware-isolation boot test: no TFT, no backlight, no heap allocation.
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("=== SUPER MINIMAL BOOT ===");
  Serial.print("reset reason = ");
  Serial.println((int)esp_reset_reason());
  Serial.print("free heap = ");
  Serial.println(ESP.getFreeHeap());
  Serial.println("APP STARTED");
}

void loop() {
  delay(1000);
  Serial.println("ALIVE");
}
