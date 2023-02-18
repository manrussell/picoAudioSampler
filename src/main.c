/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copied from pico-examples/ file, microphone_adc.c
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "pico/binary_info.h"
#include "myTimers.h"
// #include "inc/myTimers.h"

/* Example code to extract analog values from a microphone using the ADC
   with accompanying Python file to plot these values

   Connections on Raspberry Pi Pico board, other boards may vary.

   GPIO 26/ADC0 (pin 31)-> AOUT or AUD on microphone board
   3.3v (pin 36) -> VCC on microphone board
   GND (pin 38)  -> GND on microphone board
*/
#define ADC_NUM     ( 0 )
#define ADC_PIN     ( 26 + ADC_NUM )
#define ADC_RANGE   ( 1 << 12 )
#define ADC_VREF    ( 3.3 )
#define ADC_CONVERT ( ADC_VREF / ( ADC_RANGE - 1 ) )

// gpio pins for timing with logic analyser
static logicAnalyserGpioDebugPin_t timingpins[] = { { .pin = 12, .state = false },
                                                 { .pin = 13, .state = false },
                                                 { .pin = 14, .state = false },
                                                 { .pin = 15, .state = false } };

// callback for the timer IRQ
bool repeating_timer_callback(struct repeating_timer *t) {
    // printf("Repeat at %lld\n", time_us_64());
    log_time_pin_toggle( 2 );
    return true;
}

int main( void )
{
    const uint led_pin                       = 25;
    struct repeating_timer timer;
    uint adc_raw;

    // Initialize LED pin
    gpio_init( led_pin );
    gpio_set_dir( led_pin, GPIO_OUT );

    // initialise some gpio for debugging time via logic analyser
    // init_debug_pins( timingpins );
    for( int dpin = 0;
         dpin < sizeof( timingpins ) / sizeof( logicAnalyserGpioDebugPin_t );
         ++dpin )
    {
        gpio_init( timingpins[dpin].pin );
        gpio_set_dir( timingpins[dpin].pin, GPIO_OUT );
        gpio_put( timingpins[dpin].pin, false );
    }

    stdio_init_all( );
    printf( "Beep boop, listening...\n" );

    // bi_decl( bi_program_description(
    //     "Analog microphone example for Raspberry Pi Pico" ) ); // for picotool
    // bi_decl( bi_1pin_with_name( ADC_PIN, "ADC input pin" ) );

    adc_init( );
    adc_gpio_init( ADC_PIN );
    adc_select_input( ADC_NUM );

    // status on
    gpio_put( led_pin, true );

    // repeating timer every 27us which is 'nearly' 44100Hz
    time( add_repeating_timer_us(-100, repeating_timer_callback, NULL, &timer), 3 );

    // wait for a bit... no real reason
    sleep_us( 100 );

    while( 1 )
    {
        // log_time_state_toggle( loop_start );
        // log_time_pin( loop_start );
        log_time_pin_toggle( loop_start );

        log_time_pin_start( 1 );
        adc_raw = adc_read( ); // raw voltage from ADC... ~2.5uS
        log_time_pin_stop( 1 );

        time( printf( "%.2f\n", adc_raw * ADC_CONVERT ), 2 );
        sleep_ms( 10 );
    }

    return 0;
}
