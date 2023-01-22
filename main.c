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

/************************************************************************************/
/* Initialise some gpio for debugging time via logic analyser */
typedef struct
{
    const uint pin;
    bool state;
} logicAnalyserGpioDebugPin_t;

/* Use this as a handle to use the gpio output pins*/
enum
{
    loop_start,
    blank1,
    blank2,
    blank3,
};

#define log_time_pin_start( x_ )    ( gpio_put( timingpins[x_].pin, true ) )
#define log_time_pin_stop( x_ )     ( gpio_put( timingpins[x_].pin, false ) )

#define log_time_state_toggle( x_ ) ( timingpins[x_].state = !timingpins[x_].state )
#define log_time_pin( x_ )          ( gpio_put( timingpins[x_].pin, timingpins[x_].state ) )

//.. todo, is there abetter way...?
#define log_time_pin_toggle( x_ )                                                    \
    ( gpio_put( timingpins[x_].pin, log_time_state_toggle( x_ ) ) )

// todo doesn't work
void init_debug_pins( logicAnalyserGpioDebugPin_t *odpins )
{
    for( int i = 0; i < sizeof( odpins ) / sizeof( logicAnalyserGpioDebugPin_t );
         ++i )
    {
        gpio_init( odpins[i].pin );
        gpio_set_dir( odpins[i].pin, GPIO_OUT );
        gpio_put( odpins[i].pin, false );
    }
}

// todo
/* some wrapper function to time just a function..
 * time( printf( "Beep boop, listening...\n" ) );
 * not what i wanted to do and doesn't work if there ia a return'd value
 */
#define time( f_, i_ )                                                               \
    log_time_pin_start( i_ );                                                        \
    f_;                                                                              \
    log_time_pin_stop( i_ );

// todo a proper wrapper if you can remember, look in gtf

/************************************************************************************/

int main( void )
{
    logicAnalyserGpioDebugPin_t timingpins[] = { { .pin = 12, .state = false },
                                                 { .pin = 13, .state = false },
                                                 { .pin = 14, .state = false },
                                                 { .pin = 15, .state = false } };

    const uint led_pin                       = 25;
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

    bi_decl( bi_program_description(
        "Analog microphone example for Raspberry Pi Pico" ) ); // for picotool
    bi_decl( bi_1pin_with_name( ADC_PIN, "ADC input pin" ) );

    adc_init( );
    adc_gpio_init( ADC_PIN );
    adc_select_input( ADC_NUM );

    // status on
    gpio_put( led_pin, true );

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
