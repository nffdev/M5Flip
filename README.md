# M5Flip

A project combining Flipper Zero and M5StickC to explore, hack, and control IoT devices in a fun way.

> ⚠️ **For education and authorized use only.** 

## Features

| Screen        | Status     | Notes                                             |
|---------------|------------|---------------------------------------------------|
| WiFi Scan     | ✅ working  | SSID, RSSI, encryption                           |
| WiFi Detail   | ✅ working  | Signal, channel, security, BSSID, quality        |
| BLE Scan      | ✅ working  | name/address + RSSI (NimBLE)                     |
| BLE Detail    | ✅ working  | Address, addr type, RSSI, connectable, services  |
| IR Remote     | ✅ working  | Multi-brand codes (Samsung/Sony/LG) via IR LED   |
| TV-B-Gone     | ✅ working  | Sends a power-off sequence for many TV brands    |
| System        | ✅ working  | Battery, IMU accel, uptime, free heap            |

## Controls

Three buttons, consistent everywhere:

- **A** (front button) - select / OK / open detail / send
- **B** (side button) - next / down 
- **PWR** (short press) - back

## Build

Arduino IDE (2.x) with the **M5Stack** board package. Board: **M5StickCPlus2**.

Add this board-manager URL in *Preferences*, then install *M5Stack* from the
Boards Manager:

```
https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
```

Libraries (Library Manager):

| Library            | Used for                          |
|--------------------|-----------------------------------|
| `M5Unified`        | core API (buttons, power, IMU)    |
| `M5GFX`            | display + `M5Canvas` renderer     |
| `NimBLE-Arduino`   | BLE scan (**≥ 2.0**)              |
| `IRremoteESP8266`  | IR transmit                       |

Open `M5Flip.ino`, select the port, and upload.
