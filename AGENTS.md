# AGENTS.md

## Overview
This repository contains an Arduino sketch for a USB mini keyboard powered by the CH552G microcontroller. The firmware is written for the CH55xDuino board manager and relies on the Arduino IDE for building and uploading.

## Key Build & Development Steps
- **Prerequisites** (Windows):
  - Install the following via Winget:
    - `ArduinoSA.CLI`
    - `Git.Git`
    - `LLVM.LLVM`
    - `Cppcheck.Cppcheck`
  - Install the Windows driver for CH552G from the WCH website.
- **Add Board Support**: In Arduino IDE → Preferences → Additional Boards Manager URLs add
  `https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/package_ch55xduino_mcs51_index.json`.
- **Open project**: `ch552g_mini_keyboard.ino`.
- **Select board**: `CH55xDuino`.
- **Bootloader settings**: `P3.6 (D+) Pull up`.
- **Clock source**: `16MHz (internal) 3.5V or 5V`.
- **Upload method**: `USB`.
- **USB Setting**: `USER CODE w/148B USB RAM` (must be set, otherwise sketch fails to compile).
- **Compile** → **Upload**.
- **Bootloader mode**: Connect a 10 kΩ pull‑up to P3.6 (R12) and short it to VCC to bootload.
- **Return to bootloader while running**: Reconnect USB while either pressing the encoder button or pressing all buttons simultaneously.
- **Pin definitions in the .ino**: The actual pin numbers used by the sketch are `PIN_BTN_1=11, PIN_BTN_2=17, PIN_BTN_3=16, PIN_BTN_ENC=33, ENCODER_A=31, ENCODER_B=30, LED_PIN=34`. This overrides the pin names in the README.

## Configuration
- Edit `configuration.cpp` to change key/button behaviours.
- Runtime configuration changes: hold the rotary encoder while pressing a button to cycle through predefined setups.

## Pinout
| Description | Pin |
|-------------|-----|
| BUTTON 1 | P16 |
| BUTTON 2 | P17 |
| BUTTON 3 | P11 |
| BUTTON R | P33 |
| ENCODER A | P31 |
| ENCODER B | P30 |
| LED | P34 |

## Additional Notes
- The sketch does not use any tests, CI, linting, or type‑checking.
- The original firmware will be overwritten once the new firmware is flashed.
- The source is a plain Arduino sketch; build commands are therefore limited to the IDE.
- If you are using a non‑Windows host, you still need the Windows driver to communicate with the board via USB.
- This repo contains no `package.json` or Node tooling; any scripting should be done manually or via the IDE.

## File Locations
- Main sketch: `ch552g_mini_keyboard.ino`
- Configuration: `configuration.cpp`
- Core source: all files under `src/`

**Agent Tip**: When working in an OpenCode session, the agent should first ensure that the Arduino IDE and board package are installed. The only way to upload firmware is via the IDE ‑ there are no make scripts or CLI commands in this repository.