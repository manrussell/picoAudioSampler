picoAudioSampler
================
Raspberry pi Pico audio sampler synth toy.
The Pico may not be the best MCU for DSP but i will have a go and see.

Hardware
========
1. Pi Pico
    - (two if you want to use a pi pico-probe for SWD debugging)
3. Electret microphone,
    - I had a PCB module with onboard Opamp
5. Adafruit MAX98357 I2S Class-D Mono Amp.              \
    - https://learn.adafruit.com/adafruit-max98357-i2s-class-d-mono-amp?view=all
6. Power supply for the Max98357.
    -   at 5V (3W max) it can draw up to 800mA good to have 650mA
7. 4 Ohm speaker, i used one from /pimoroni link.../
8. Optional, logic analyser for debugging

Circuit simulations use Falstad
===============================

//ToDo add the file


Mic pins
========


I2S pins
========

Used the pico-playground example so far and defined the pins \
#define PICO_AUDIO_I2S_DATA_PIN         (9)                 \
#define PICO_AUDIO_I2S_CLOCK_PIN_BASE   (10)                \
// #define l/R ... (PICO_AUDIO_I2S_CLOCK_PIN_BASE+1)

Software
========

1. You should clone it alongside pico-sdk\
        $ ls \
        pico-examples pico-sdk        pico-extras       picotool \
        openocd       pico-playground picoAudioSampler  picoprobe

2. How to build OpenOCD etc see /doc

3. Create a pi Pico VSCode project, I didn't use this but, here for ref... \
    https://github.com/raspberrypi/pico-project-generator

4. Logic analyser software:
    - $ pulseview
    - E.g. Run: 1M samples @ 12MHz

How to build the binaries
=========================

$ cd build
$ make

How to flash the board
======================

Either :
- Use the bootloader and the u2f file. So hold down the button on the pico board
and power cycle the board this should open up a the usb file system where you copy the file to.
or
- Can i use the pico to flash the thing?


How to debug with pico-probe
============================

In Vscode go to the debug window and hit "Pico Debug"
- Warning hitting 'F5' seems to make openOcd go weird and display a message about
  vflash failing


Pi Pico SDK notes
=================

1. Using add_repeating_timer_us( -27us ) i found that using a small timer values E.g.
27us, The timer ended up going into an assert when in debug mode. Perhaps the overhead
of the function was too large and the timer was firing before it could findih itself??
I measured add_repeating_timer_us() by toggleing a digi pin and it read as 86.6 us so
... thats a long time, i could get it to run at 100us with not much else happening.
Try using a low level method to get better performance here. E.g.


2. dissassembly view
Add the -fverbose-asm flag to the compile and (as well as the -S flag) and you will get the original C source lines intermixed with the assembler instructions. That makes it very easy indeed to find the corresponding code. Just search for something unique in the C source line and you are there instantly.


Timing Ideas
============

Static instrumentation
1. toggling pins and logic analyser (pulseview). Good but takes many pins

2. have a buffer and shove out of the SPI port (faster then UART) to a FTDI ft232H
   chip and parse the messages on the other side (perl?) and diaply somehow.
   Need a basic protocol to do this.




