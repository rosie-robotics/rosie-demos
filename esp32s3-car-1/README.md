# ESP32-S3 Car-1

Public **reference robot** for [Rosie](https://github.com/rosie-robotics/rosie):
a Freenove ESP32-S3 CAM differential-drive car using **`robot.yaml` + DiffDriveStack**.

Framework docs:
[BYOR](https://github.com/rosie-robotics/rosie/blob/main/docs/byor.md) ·
[Mobile base](https://github.com/rosie-robotics/rosie/blob/main/docs/mobile-base.md) ·
[Drivers](https://github.com/rosie-robotics/rosie/blob/main/docs/drivers.md) ·
[Fleet networking](https://github.com/rosie-robotics/rosie/blob/main/docs/fleet-networking.md).

## Framework vs this robot

| Rosie (framework) | This project |
|-------------------|--------------|
| DiffDriveStack, MobileBase, chip drivers | `robot.yaml` — pins, geometry, gains |
| `rosie mcu gen-config` → `robot_config.h` | ~20-line `src/main.cpp` |
| `rosie drive` / `tune` / `MobileRobot` | Hardware bring-up for this car |

## Hardware

- Freenove ESP32-S3-WROOM CAM (camera preset: `esp32s3_eye`)
- TB6612FNG dual motor driver + quadrature encoders
- MPU6050 on I2C

## Bring-up

```bash
# Install Rosie once (editable checkout while developing the framework):
pip install -e "../../rosie/python[mcu]"              # if sibling to rosie-demos
# pip install -e "../../rosie/python[mcu,camera]"     # + OpenCV for drive snap/cam
# or: pip install -e "/path/to/rosie/python[mcu]"
# Quote the path — zsh treats [...] as a glob.
rosie setup

cd esp32s3-car-1   # this directory
rosie mcu setup
rosie mcu flash
```

**Solo SoftAP** (default `robot.yaml`): the car hosts Wi‑Fi **ESP32S3-Car-1** /
password `esp32s3-car-1`. Join that network from the laptop, then:

```bash
rosie router          # terminal 1 — Zenoh bus on the laptop
rosie drive --config robot.yaml   # terminal 2
```

Reset the board if it tried to connect before the router was up. Host tools on
this laptop use `tcp/127.0.0.1:7447` by default; the MCU uses
`network.connect` from `robot.yaml` (`tcp/192.168.4.2:7447` for SoftAP).

Dedicated AP / station mode: edit `network` in `robot.yaml` (or see
[Fleet networking](https://github.com/rosie-robotics/rosie/blob/main/docs/fleet-networking.md)).

### Useful commands

| Command | What it does |
|---------|----------------|
| `rosie drive --config robot.yaml` | Waypoints, teleop, camera REPL |
| `rosie teleop --robot car1` | WASD → `cmd_vel` only |
| `rosie tune --config robot.yaml` | Live-tune velocity PID |
| `rosie mcu build` / `flash` / `monitor` | Compile, flash, serial log |
| `rosie drivers list` | Supported driver / board ids |

## What to edit

Edit **`robot.yaml`** for pins, geometry, and gains. After changes:
`rosie mcu flash`. Do not hand-edit `src/generated/robot_config.h`.

## Firmware

```cpp
#include "generated/robot_config.h"
#include <rosie/diff_drive_stack.h>

static rosie::DiffDriveStack g_stack;

void setup() {
  Serial.begin(115200);
  delay(300);
  g_stack.begin();
}

void loop() {
  g_stack.loop();
}
```

## Layout

```
esp32s3-car-1/
  robot.yaml
  platformio.ini
  src/main.cpp
  src/generated/             # auto robot_config.h
  lib/rosie → Rosie firmware (via rosie mcu setup)
```
