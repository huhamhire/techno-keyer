# Techno Keyer

*Techno Keyer* is an autonomous CW (continuous wave) keyer with encode/decode abilities for amateur radio (ham radio) enthusiasts to send out morse codes with USB keyboards.

![Techno Keyer](./docs/images/techno-keyer.jpg)

> ℹ ️ This repository only contains firmware implementation of *Techno Keyer*. The hardware design and schematics are not included. 

> The design of *Techno Keyer* comes with a VFD (vacuum fluorescent display) module, which makes it feels more like other vintage electronic devices from 1980s. Because of this idea, the word "Techno" seems to be a good fit for naming this project.


## Features

1. **Dimension**: 115mm (W) x 52mm (D) x 45mm (H)

2. **Display**
   - 16x2 VFD display for messages and status.
   - Blue LED for CW key output status.
   - Red LED for audio input status.

3. **TX Mode**
   - Transmit morse code by input form USB keyboard.
   - Work as a straight key by the 3.5mm key port.
   - Display input messages on VFD before sending out.

4. **RX Mode**
   - Receive morse code (CW) audio signal from radio or other source.
   - Decode and display messages received on VFD.
   - Select specific pitch frequency for audio input.

5. **Configurable**
   - Set CW speed (10-50 WPM) for transmitting.
   - Set VFD brightness.
   - Set pitch frequency (400-1000Hz) for buzzer output (TX & RX mode).


## User Guide

1. **Power On**
   - Connect USB Type-C cable to power the *Techno Keyer* on.
   - The VFD will display the welcome message.
   - After 2 seconds, the keyer will enter the transmit (TX) mode.

2. **Send Morse Code**
   - Plug USB keyboard to the Type-A port.
   - Connect radio to the 3.5mm key port, set key mode as straight key.
   - Use the USB keyboard to input messages.
   - Press <kbd>Enter</kbd> or <kbd>Space</kbd> key to send out the message in morse code.
   - Press <kbd>Backspace</kbd> key to retract the last word.

3. **Decode Audio Input**
   - Connect audio source to the 3.5mm audio input jack.
   - Rotate the rotary encoder to adjust the centering pitch frequency.
   - The *Techno Keyer* will decode morse code from audio signal matching target pitch frequency automatically.
   - The decoded messages will be displayed on the VFD, and the *Techno Keyer* would entering the receive (RX) mode.

4. **Config Settings**
   - Press the rotary encoder button to enter the configuration mode.
   - Press the encoder button again to select the setting to change.
   - Rotate the encoder to change value of selected setting.
   - The settings include:
     - VFD brightness (0-100%)
     - TX Speed - CW speed for transmit mode (10-50 WPM)
     - TX Tone - Pitch frequency for transmit mode (400-1000Hz)
     - RX Tone - Pitch frequency for receive mode (400-1000Hz)
   - After configuring the last menu item, press the encoder button to save and exit the configuration mode, all changes made would be saved.

5. **Other Functions**
   - The buzzer could be turned off by the switch beside the USB type-C port.
   - Press the rotary encoder button for 3 seconds to restart the keyer.

> ℹ ️ Note: 
> - If TX mode is active, the audio input will be blocked for 3 seconds after sending out the last character.
> - If RX mode is active, the keyboard input will be blocked for 3 seconds. 

---
## Developer Guide

### Firmware

- Developed with [PlatformIO](https://platformio.org/) and Arduino framework.
- Platform: `esp32-s3`
- Libraries:
  - [Ai Esp32 Rotary Encoder](https://www.arduino.cc/reference/en/libraries/ai-esp32-rotary-encoder/)
  - [ESP32_CH9350_KEY](https://github.com/joetrs/ESP32_CH9350_KEY)

### Components

- ESP32-WROOM module as main MCU
- CIG25-1605N VFD module
- Rotary encoder
- Solid state relay (TLP175A) for CW key control
- LM567 tone decoder
- CH9350 USB keyboard & mouse communication control chip
- Passive Buzzer with one switch to turn it off

![PCB Components](./docs/images/pcb-components.jpg)

### IO Connectors

- 3.5mm key port
- 3.5mm audio input jack
- USB Type-A keyboard input port
- USB Type-C port for power supply and serial communication


### Schematics

- [Schematics](./docs/schematics.pdf)

  ![Main](./docs/images/schematic-main.jpg)

### MCU Pinout

Pins used by ESP32-WROOM module for *Techno Keyer*.

| GPIO | Description                                    |
|:----:|------------------------------------------------|
|  12  | SPI clock                                      |
|  11  | SPI data out (MOSI)                            |
|  21  | SPI chip select for pitch tuning potentiometer |
|  10  | SPI chip select for VFD                        |
|  17  | VFD enable                                     |
|  18  | VFD reset                                      |
|  15  | Keyboard data receive (RX)                     |
|  16  | Keyboard data transmit (TX)                    |
|  5   | Rotary encoder A                               |
|  6   | Rotary encoder B                               |
|  7   | Rotary encoder button                          |
|  14  | CW (morse code) signal output                  |
|  2   | Buzzer output                                  |
|  8   | Audio signal input                             |


## LICENSE

[GPLv3](./LICENSE)


## Inspired by

- [Morserino-32](https://www.morserino.info/)
- [K45B CW Modem w/USB Keyboard I/F](https://www.hamcrafters2.com/K45_B.html)
- [K4ICY's CW Morse Decoder](http://www.k4icy.com/cw_decoder.html)
- [wb7fhc-cw-decoder](https://github.com/kareiva/wb7fhc-cw-decoder)
- [VK2IDL_CW_Decoder](https://github.com/ideal54/VK2IDL_CW_Decoder)

---
Designed by BD4WEI. Build on 🌍 with 💓.
