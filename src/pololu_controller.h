#ifndef POLOLU_CONTROLLER_H
#define POLOLU_CONTROLLER_H 1

#include <Arduino.h>
#include <HardwareSerial.h>

#define PCON_MAX_TO_DEV 4
#define PCON_MAX_FROM_DEV 3

#define PCON_DEFAULT_COMMAND_BYTE 0xAA

extern uint8_t pcon_buffer_to_dev[PCON_MAX_TO_DEV];
extern uint8_t pcon_buffer_from_dev[PCON_MAX_FROM_DEV];

enum {
    PCON_IS_RUNNING = 0x1,
    PCON_IS_ATTACHED = 0x2
};

typedef struct polcore {
    HardwareSerial* serial_line;
    uint8_t device_number;
    uint32_t shedule_stop_time;
    uint8_t control;
} polcore;

/** Writes the command string out on the serial line,
 * Returns an error code
 */
uint8_t pconSendCommand( polcore* dev, uint8_t* command_string );

#endif
