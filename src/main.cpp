#include <Arduino.h>
#include "esp_system.h"

void setup() {
  Serial.begin(115200);
  delay(1500);

  Serial.println();
  Serial.println("=== SUPER N16R8 BOOT TEST ===");
  Serial.print("reset reason = ");
  Serial.println((int)esp_reset_reason());
  Serial.print("flash size = ");
  Serial.println(ESP.getFlashChipSize());
  Serial.print("free heap = ");
  Serial.println(ESP.getFreeHeap());
  Serial.println("APP STARTED");
}

void loop() {
  Serial.println("ALIVE");
  delay(1000);
}
