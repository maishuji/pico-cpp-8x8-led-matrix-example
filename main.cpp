#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

// Define SPI pins
#define SPI_PORT spi0
#define PIN_SCK 18
#define PIN_MOSI 19
#define PIN_CS 17

// MAX7219 Commands
#define MAX7219_NO_OP 0x00
#define MAX7219_DIGIT0 0x01
#define MAX7219_DIGIT7 0x08
#define MAX7219_DECODE_MODE 0x09
#define MAX7219_INTENSITY 0x0A
#define MAX7219_SCAN_LIMIT 0x0B
#define MAX7219_SHUTDOWN 0x0C
#define MAX7219_DISPLAY_TEST 0x0F

// Function to send data to the MAX7219
void max7219_send(uint8_t address, uint8_t data) {
    gpio_put(PIN_CS, 0);  // Select the device
    spi_write_blocking(SPI_PORT, &address, 1);
    spi_write_blocking(SPI_PORT, &data, 1);
    gpio_put(PIN_CS, 1);  // Deselect the device
}

void max7219_init() {
    max7219_send(MAX7219_DISPLAY_TEST, 0x00);  // Disable display test
    max7219_send(MAX7219_SCAN_LIMIT, 0x07);   // Use all 8 digits
    max7219_send(MAX7219_DECODE_MODE, 0x00);  // No decode (matrix mode)
    max7219_send(MAX7219_INTENSITY, 0x08);    // Set medium brightness (0x00 to 0x0F)
    max7219_send(MAX7219_SHUTDOWN, 0x01);     // Exit shutdown mode
    max7219_send(MAX7219_NO_OP, 0x00);        // Reset internal state
}


// Display an 8x8 pattern
void max7219_display_pattern(const uint8_t *pattern) {
    for (uint8_t i = 0; i < 8; i++) {
        max7219_send(MAX7219_DIGIT0 + i, pattern[i]);
    }
}

int main() {
    // Initialize the system
    stdio_init_all();

    // Initialize SPI
    spi_init(SPI_PORT, 1000000);  // 1 MHz
    spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // Initialize CS pin
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    // Initialize the MAX7219
    max7219_init();

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

    // Display the smiley face
    max7219_display_pattern(smiley_face);

    while (true) {
        tight_loop_contents();  // Keep running
    }
}
