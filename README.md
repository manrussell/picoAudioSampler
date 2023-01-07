# picoAudioSampler
Raspberry pi pico audio sampler synth toy

Hardware...
    *) Electret microphone
    *) Adafruit MAX98357 I2S Class-D Mono Amp 
        https://learn.adafruit.com/adafruit-max98357-i2s-class-d-mono-amp?view=all
    *) power supply for the Max98357 
        at 5V (3W max) it can draw up to 800mA good to have 650mA
    *) 4 Ohm speaker
        pimoroni link...

I2S..
used the pico-playground example but defined the pins
#define PICO_AUDIO_I2S_DATA_PIN         (9)
#define PICO_AUDIO_I2S_CLOCK_PIN_BASE   (10)
// #define l/R ...                      (PICO_AUDIO_I2S_CLOCK_PIN_BASE+1)

Software...
    *)
    You should clone it alongside pico-sdk
        $ ls
        pico-examples pico-sdk        pico-extras      picotool
        openocd       pico-playground picoAudioSampler picoprobe

    *)
    How to build OpenOCD etc see /doc

    *)
    I didn't use this but, here for ref...
    https://github.com/raspberrypi/pico-project-generator
