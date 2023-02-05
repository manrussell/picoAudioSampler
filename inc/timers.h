
/*************************************************************************************
 * file :       timers.h
 * decription : Initialise some gpio for debugging time via logic analyser
 * author :     mark russell
 *
 ************************************************************************************/
#if !defined TIMERS_H
#    defined TIMERS_H

#    include <stdio.h>
#    include "pico/stdlib.h"

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

#    define log_time_pin_start( x_ ) ( gpio_put( timingpins[x_].pin, true ) )
#    define log_time_pin_stop( x_ )  ( gpio_put( timingpins[x_].pin, false ) )

#    define log_time_state_toggle( x_ )                                              \
        ( timingpins[x_].state = !timingpins[x_].state )
#    define log_time_pin( x_ )                                                       \
        ( gpio_put( timingpins[x_].pin, timingpins[x_].state ) )

//.. todo, is there abetter way...?
#    define log_time_pin_toggle( x_ )                                                \
        ( gpio_put( timingpins[x_].pin, log_time_state_toggle( x_ ) ) )

// todo doesn't work
static inline void init_debug_pins( logicAnalyserGpioDebugPin_t *odpins )
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
#    define time( f_, i_ )                                                           \
        log_time_pin_start( i_ );                                                    \
        f_;                                                                          \
        log_time_pin_stop( i_ );

// todo a proper wrapper if you can remember, look in gtf

#endif /* TIMERS_H */
