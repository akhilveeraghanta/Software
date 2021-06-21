#pragma once

#include "firmware/boards/robot_stm32h7/io/breakbeam.h"

typedef struct Chicker Chicker_t;

/**
 * Initialize the IO layer for the Chicker
 *
 * @param [in] breakbeam
 */
void io_chicker_init(Breakbeam_t *breakbeam);

void io_chicker_kick(float speed_m_per_s);

void io_chicker_chip(float distance_m);

void io_chicker_enable_auto_kick(float speed_m_per_s);

void io_chicker_enable_auto_chip(float distance_m);

void io_chicker_disable_auto_kick();

void io_chicker_disable_auto_chip();

void io_chicker_handleBreakbeam();
