#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "MAX7219.hpp"

// Define SPI pins
#define SPI_PORT spi0
#define PIN_SCK 18
#define PIN_MOSI 19
#define PIN_CS 17

int main() {
    // Initialize the system
    stdio_init_all();

    // Initialize the SPI hardware
    MAX7219 max7219(SPI_PORT, PIN_SCK, PIN_MOSI, PIN_CS);
    // Initialize the MAX7219
    if (!max7219.init()) {
        printf("Failed to initialize MAX7219.\n");
        return -1;
    }

    // Define a smiley face pattern
    const uint8_t smiley_face[8] = {
        0b00111100,  //   ****
        0b01000010,  //  *    *
        0b10100101,  // * *  * *
        0b10000001,  // *      *
        0b10100101,  // * *  * *
        0b10011001,  // *  **  *
        0b01000010,  //  *    *
        0b00111100   //   ****
    };

    const uint8_t smiley_face2[8] = {
        0b00111100,  //   ****
        0b01000010,  //  *    *
        0b10100101,  // * *  * *
        0b10011001,  // *      *
        0b10000001,  // * *  * *
        0b10111101,  // *  **  *
        0b01000010,  //  *    *
        0b00111100   //   ****
    };

    // Display the smiley face
    max7219.displayPattern(smiley_face2);

    while (true) {
        //tight_loop_contents();  // Keep running
        sleep_ms(1000);
        max7219.displayPattern(smiley_face);
        sleep_ms(1000);
        max7219.displayPattern(smiley_face2);
    }
}
