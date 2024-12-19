#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

class MAX7219
{
private:
    spi_inst_t *spi_port;
    uint8_t pin_sck;
    uint8_t pin_mosi;
    uint8_t pin_cs;
    bool initialized;

    static bool spi_initialized; // Track SPI initialization across instances

    void send(uint8_t address, uint8_t data)
    {
        gpio_put(pin_cs, 0); // Select the device
        spi_write_blocking(spi_port, &address, 1);
        spi_write_blocking(spi_port, &data, 1);
        gpio_put(pin_cs, 1); // Deselect the device
    }

public:
    MAX7219(spi_inst_t *spi_port, uint8_t pin_sck, uint8_t pin_mosi, uint8_t pin_cs)
        : spi_port(spi_port), pin_sck(pin_sck), pin_mosi(pin_mosi), pin_cs(pin_cs), initialized(false) {}

    bool init()
    {
        if (initialized)
        {
            printf("SPI port already initialized.\n");
            return false;
        }

        // Attempt to claim and initialize the SPI port
        if (!spi_initialized)
        {
            spi_init(spi_port, 1000000); // 1 MHz
            gpio_set_function(pin_sck, GPIO_FUNC_SPI);
            gpio_set_function(pin_mosi, GPIO_FUNC_SPI);
            spi_initialized = true;
        }

        // Initialize CS pin
        gpio_init(pin_cs);
        gpio_set_dir(pin_cs, GPIO_OUT);
        gpio_put(pin_cs, 1);

        // MAX7219 initialization sequence
        send(0x0F, 0x00); // Disable display test
        send(0x0B, 0x07); // Use all 8 digits
        send(0x09, 0x00); // No decode (matrix mode)
        send(0x0A, 0x08); // Medium brightness
        send(0x0C, 0x01); // Exit shutdown mode

        initialized = true;
        return true;
    }

    void
    displayPattern(const uint8_t *pattern)
    {
        if (!initialized)
        {
            printf("MAX7219 not initialized. Call init() first.\n");
            return;
        }
        for (uint8_t i = 0; i < 8; i++)
        {
            send(0x01 + i, pattern[i]);
        }
    }
};
bool MAX7219::spi_initialized = false;