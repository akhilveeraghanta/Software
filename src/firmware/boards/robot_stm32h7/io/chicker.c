#include "firmware/boards/robot_stm32h7/io/chicker.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "firmware/app/logger/logger.h"

static Chicker_t *_chicker;

typedef struct Chicker
{
    bool auto_chip_enabled;
    float auto_chip_distance_m;
    bool auto_kick_enabled;
    float auto_kick_speed_m_per_s;
    Breakbeam_t *breakbeam;
} Chicker_t;

// ensure that static point to chicker is initialized before use
static bool initialized = false;

void io_chicker_init(Breakbeam_t *breakbeam)
{
    Chicker_t *new_chicker = (Chicker_t *)malloc(sizeof(Chicker_t));

    new_chicker->auto_chip_enabled = false;
    new_chicker->auto_kick_enabled = false;
    new_chicker->breakbeam         = breakbeam;

    _chicker = new_chicker;

    initialized = true;
}

void io_chicker_kick(float speed_m_per_s)
{
    // TODO (#2080) implement this
}

void io_chicker_chip(float distance_m)
{
    // TODO (#2080) implement this
}

void io_chicker_enable_auto_kick(float speed_m_per_s)
{
    // TODO (#2080) implement this
}

void io_chicker_enable_auto_chip(float distance_m)
{
    // TODO (#2080) implement this
}

void io_chicker_disable_auto_kick()
{
    // TODO (#2080) implement this
}

void io_chicker_disable_auto_chip()
{
    // TODO (#2080) implement this
}

void io_chicker_handleBreakbeam()
{
    assert(initialized);

    // prioritize kicking over chipping
    if (_chicker->auto_kick_enabled)
    {
        io_chicker_kick(_chicker->auto_kick_speed_m_per_s);
        return;
    }
    else if (_chicker->auto_chip_enabled)
    {
        io_chicker_chip(_chicker->auto_chip_distance_m);
        return;
    }
    else
    {
        return;
    }
}
