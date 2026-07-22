# Rosie demos

Example robots and projects that use the [Rosie](https://github.com/rosie-robotics/rosie)
framework. Each subdirectory is a self-contained robot project: edit
`robot.yaml`, flash with `rosie mcu`, drive with `rosie drive`.

Rosie itself lives in a **separate** repository — install it first, then open a
demo folder.

## Install Rosie (once)

From a Rosie checkout (recommended while developing Rosie + demos on one machine):

```bash
pip install -e "/path/to/rosie/python[mcu]"           # required: flash / build
# optional: OpenCV for `rosie drive` snap / live camera view
# pip install -e "/path/to/rosie/python[mcu,camera]"
# Quote the path — zsh treats [...] as a glob.
rosie setup
```

Or from a released package (when published):

```bash
pip install "rosie[mcu]"
# pip install "rosie[mcu,camera]"
rosie setup
```

## Demos

| Demo | Hardware | Notes |
|------|----------|--------|
| [esp32s3-car-1](esp32s3-car-1/) | Freenove ESP32-S3 CAM + TB6612 + encoders + MPU6050 | DiffDriveStack reference car |

## Typical workflow (any demo)

```bash
cd esp32s3-car-1
rosie mcu setup && rosie mcu flash
rosie router                  # terminal 1 — Zenoh bus
rosie drive --config robot.yaml   # terminal 2
```

Follow each demo’s README for network bring-up (e.g. SoftAP). Edit that
demo’s `robot.yaml` for pins, Wi‑Fi, and gains.

## Developing Rosie + demos on one machine

Keep checkouts as siblings:

```text
ESP32/
  rosie/           # framework (editable pip install)
  rosie-demos/     # this repo
```

Changes in `rosie/firmware` and `rosie/python` apply immediately to demos after
`rosie mcu flash` / restarting host tools — no need to vendor Rosie inside demos.

## Docs

- [Getting started](https://github.com/rosie-robotics/rosie/blob/main/docs/getting-started.md)
- [BYOR](https://github.com/rosie-robotics/rosie/blob/main/docs/byor.md)
- [Mobile base](https://github.com/rosie-robotics/rosie/blob/main/docs/mobile-base.md)
- [Fleet networking](https://github.com/rosie-robotics/rosie/blob/main/docs/fleet-networking.md)

