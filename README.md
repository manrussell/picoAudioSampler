# picoAudioSampler
Raspberry pi Pico audio sampler synth toy.
The Pico may not be the best MCU for DSP but i will have a go and see.

## Hardware
1. Pi Pico
    - (two if you want to use a pi pico-probe for SWD debugging)
3. Electret microphone,
    - I had a PCB module with onboard Opamp
5. Adafruit MAX98357 I2S Class-D Mono Amp.              \
    - https://learn.adafruit.com/adafruit-max98357-i2s-class-d-mono-amp?view=all
6. Power supply for the Max98357.
    -   at 5V (3W max) it can draw up to 800mA good to have 650mA
7. 4 Ohm speaker, i used one from /pimoroni link.../
8. Optional, logic analyser

### Circuit simulations use Falstad


### Mic pins


### I2S pins
Used the pico-playground example so far and defined the pins \
#define PICO_AUDIO_I2S_DATA_PIN         (9)                 \
#define PICO_AUDIO_I2S_CLOCK_PIN_BASE   (10)                \
// #define l/R ... (PICO_AUDIO_I2S_CLOCK_PIN_BASE+1)

## Software
1. You should clone it alongside pico-sdk\
        $ ls \
        pico-examples pico-sdk        pico-extras       picotool \
        openocd       pico-playground picoAudioSampler  picoprobe

1. How to build OpenOCD etc see /doc

1. Create a pi Pcio VSCode project, I didn't use this but, here for ref... \
    https://github.com/raspberrypi/pico-project-generator

1. Logic analyser software:
    - $ pulseview
    - E.g. Run: 1M samples @ 12MHz
