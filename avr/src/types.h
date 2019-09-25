#include <stdint.h>

#ifndef _INCL_TYPES
#define _INCL_TYPES

typedef struct
{
    int8_t      integral;
    uint8_t     mantissa;
}
decimal16_t;

typedef struct
{
    int16_t     integral;
    uint8_t     mantissa;
}
decimal24_t;

#define populate_decimal(i, m)      { .integral = i, .mantissa = m }

#endif