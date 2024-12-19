# Set minimum required CMake version and include the Pico SDK
cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Pull in Pico SDK (must be before project)
message(STATUS "PICO_SDK_PATH: $ENV{PICO_SDK_PATH}")
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
# Set the project name
project(prj CXX C)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Add the executable
add_executable(led_matrix_example
    main.cpp
)
target_compile_features(led_matrix_example PUBLIC cxx_std_20)


# Link the required libraries
target_link_libraries(led_matrix_example
    PRIVATE
        pico_stdlib        # Standard library for Pico
        hardware_spi       # SPI hardware library
)

# Enable USB and UART output (optional, for debugging)
pico_enable_stdio_usb(led_matrix_example 1)  # Enable USB stdout
pico_enable_stdio_uart(led_matrix_example 0) # Disable UART stdout

# Add extra outputs for the executable
pico_add_extra_outputs(led_matrix_example)
