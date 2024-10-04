# Techno Keyer

*Techno Keyer* is an autonomous CW keyer with encode/decode abilities for amateur radio (ham radio) enthusiasts to send out morse codes with USB keyboards.

> ℹ ️ This repository only contains firmware implementation for *Techno Keyer*. The hardware design and schematics are not included. 

> The design of *Techno Keyer* comes with a VFD (vacuum fluorescent display) module, which makes it feels more like other vintage electronic devices from 1980s. Because of this idea, the word "Techno" seems to be a good fit for naming this project.


## Features

1. **Display**
   - 16x2 VFD display for messages and status.
   - Blue LED for CW key output status.
   - Red LED for audio input status.

2. **TX Mode**
   - Transmit morse code by input form USB keyboard.
   - Work as a straight key by the 3.5mm key port.
   - Display input messages on VFD before sending out.

3. **RX Mode**
   - Receive morse code (CW) audio signal from radio or other source.
   - Decode and display messages received on VFD.
   - Select specific pitch frequency for audio input.

4. **Configurable**
   - Set CW speed (10-50 WPM) for transmitting.
   - Set VFD brightness.
   - Set pitch frequency (400-1000Hz) for buzzer output (TX & RX mode).


---
## Development

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


### IO Connectors

- 3.5mm key port
- 3.5mm audio input jack
- USB keyboard input port
- USB Type-C port for power supply and serial communication


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

- [K45B CW Modem w/USB Keyboard I/F](https://www.hamcrafters2.com/K45_B.html)
- [K4ICY's CW Morse Decoder](http://www.k4icy.com/cw_decoder.html)
- [wb7fhc-cw-decoder](https://github.com/kareiva/wb7fhc-cw-decoder)
- [VK2IDL_CW_Decoder](https://github.com/ideal54/VK2IDL_CW_Decoder)

---
Designed by BD4WEI. Build on 🌍 with 💓.
