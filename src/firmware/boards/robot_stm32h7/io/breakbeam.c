#include "breakbeam.h"

#include <stdlib.h>

typedef struct Breakbeam
{
    GpioPin_t* breakbeam_pin;
} Breakbeam_t;

Breakbeam_t* io_breakbeam_create(GpioPin_t* breakbeam_pin)
{
    Breakbeam_t* new_breakbeam = (Breakbeam_t*)malloc(sizeof(Breakbeam_t));

    new_breakbeam->breakbeam_pin = breakbeam_pin;

    // TODO setup IRQ on breakbeam_pin.

    return new_breakbeam;
}

void io_breakbeam_destroy(Breakbeam_t* breakbeam)
{
    free(breakbeam);
}

bool io_breakbeam_getState(Breakbeam_t* breakbeam)
{
    return io_gpio_pin_getState(breakbeam->breakbeam_pin);
}
