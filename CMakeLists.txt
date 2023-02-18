# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

# Include build functions from Pico SDK
include(pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(picoAudioSampler_proj C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

include_directories(${PROJECT_NAME}
    inc)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
    src/main.c
    # inc/myTimers.h
)

# disable usb output, enable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
# pico_enable_stdio_usb(${PROJECT_NAME} 1)
# pico_enable_stdio_uart(${PROJECT_NAME} 0)

# left for example only
add_compile_options(-Wall -Werror)
# tried to get interleaved C and assembly as the dissassembly window isn't working
# add_compile_options(-fverbose-asm -S)
# add_compile_options( -fsanitize=address -fsanitize=bounds -fsanitize=undefined )

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# add lib for adc
target_link_libraries(
    ${PROJECT_NAME}
    pico_stdlib
    hardware_adc
)

