#ifndef PINOUT_H
#define PINOUT_H

namespace TechnoKeyer {

/**
 * Pin definitions for GPIO
 */

// SPI
#define SPI_CS_PIN          10      // SPI Chip Select
#define SPI_CLK_PIN         12      // SPI Clock
#define SPI_MOSI_PIN        11      // SPI Data Out
#define SPI_MISO_PIN        (-1)    // SPI Data In

// VFD display
#define VFD_EN_PIN          17      // Enable
#define VFD_RST_PIN         18      // Reset
#define VFD_CS_PIN          10      // SPI Chip Select (Duplicate)

// Audio input
#define AUX_SIG_PIN         8       // Audio Signal Input

// Keyboard input
#define KBD_RX_PIN          15
#define KBD_TX_PIN          16

// Rotary encoder
#define ENCODER_A_PIN       5
#define ENCODER_B_PIN       6
#define ENCODER_BUTTON_PIN  7
#define ENCODER_VCC_PIN     (-1)    // Direct to 3V3

// Tuner
#define TUNER_CS_PIN        21

// CW Key
#define CW_PIN              14      // Key output (LED & Keyer)

// Buzzer
#define BZ_PIN              2

} // TechnoKeyer

#endif // PINOUT_H
