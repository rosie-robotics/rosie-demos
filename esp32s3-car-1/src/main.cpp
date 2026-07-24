#include <Arduino.h>
#include <esp_rom_sys.h>

#include "generated/robot_config.h"
#include <rosie/diff_drive_stack.h>

// Freenove ESP32-S3 CAM car — DiffDriveStack from robot.yaml.
// Edit robot.yaml; `rosie mcu build` regenerates robot_config.h.

static rosie::DiffDriveStack* g_stack = nullptr;

void setup() {
  esp_rom_printf("Rosie: entered setup()\n");
  Serial.begin(115200);
  delay(500);

  // On some macOS + PlatformIO setups, HWCDC never reports connected (operator
  // bool stays false) even while the monitor is open. ROM printf still works.
  esp_rom_printf("Rosie: USB CDC %s\n", Serial ? "connected" : "not connected");
  esp_rom_printf("Rosie: constructing stack\n");
  g_stack = new rosie::DiffDriveStack();
  esp_rom_printf("Rosie: calling begin() (Wi-Fi + Zenoh; may take ~20s)\n");
  g_stack->begin();
  esp_rom_printf("Rosie: begin() returned; zenoh ready=%d\n",
                 g_stack->base().ready() ? 1 : 0);
}

void loop() {
  if (g_stack) g_stack->loop();
}
