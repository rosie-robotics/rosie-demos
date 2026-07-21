#include <Arduino.h>

#include "generated/robot_config.h"
#include <rosie/diff_drive_stack.h>

// Freenove ESP32-S3 CAM car — DiffDriveStack from robot.yaml.
// Edit robot.yaml; `rosie mcu build` regenerates robot_config.h.

static rosie::DiffDriveStack g_stack;

void setup() {
  Serial.begin(115200);
  delay(300);
  g_stack.begin();
}

void loop() {
  g_stack.loop();
}
