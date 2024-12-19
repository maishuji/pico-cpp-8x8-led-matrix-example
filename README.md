# 8x8 LED Matrix Controller for Raspberry Pi Pico

This project provides a simple class to control an 8x8 LED matrix connected to the Raspberry Pi Pico using the SPI0 interface.

## Overview

The class allows you to interface with an 8x8 LED matrix via SPI0, enabling you to send data to control individual LEDs, display patterns, or even scroll text on the matrix.

## Requirements

- **Hardware**: Raspberry Pi Pico, 8x8 LED matrix (compatible with SPI interface)

## Pin Connections

| LED Matrix Pin | Raspberry Pi Pico Pin |
|----------------|-----------------------|
| VCC            | 3V3                   |
| GND            | GND                   |
| DIN (MOSI)     | GP19                  |
| CLK (SCK)      | GP18                  |
| CS             | GP17                  |
| LOAD           | GP13                  |


Make sure to connect the LED matrix correctly to the SPI0 pins of the Raspberry Pi Pico.

## Building the project

   ```bash
   mkdir build
   cmake ..
   make all
   ``` 
