#pragma once

#include <stdbool.h>

#include "firmware/boards/robot_stm32h7/io/gpio_pin.h"

typedef struct Breakbeam Breakbeam_t;

/**
 * Create a Breakbeam
 *
 * Sets an IRQ to trigger when the Breakbeam pin is SET.
 *
 * @param breakbeam_pin A GPIO pin connected to the "breakbeam" pin.
 * @return A Breakbeam.
 */
Breakbeam_t* io_breakbeam_create(GpioPin_t* breakbeam_pin);

/**
 * Destroy the given Breakbeam
 * @param breakbeam The breakbeam to destroy.
 */
void io_breakbeam_destroy(Breakbeam_t* breakbeam);

/**
 * Gets the current Breakbeam pin state
 * @param breakbeam
 * @return
 */
bool io_breakbeam_getState(Breakbeam_t* breakbeam);
