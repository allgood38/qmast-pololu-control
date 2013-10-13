#ifndef POLOLU_CONTROLLER_H
#define POLOLU_CONTROLLER_H 1

#include <Arduino.h>
#include <HardwareSerial.h>

#define PCON_MAX_TO_DEV 4
#define PCON_MAX_FROM_DEV 3

#define PCON_DEFAULT_COMMAND_BYTE 0xAA

extern uint8_t pcon_buffer_to_dev[PCON_MAX_TO_DEV];
extern uint8_t pcon_buffer_from_dev[PCON_MAX_FROM_DEV];

// For debugging, needs to be replaced with something more general
extern HardwareSerial Serial;

enum {
    PCON_IS_RUNNING = 0x1,
    PCON_IS_ATTACHED = 0x2
};

enum PCON_DIRECTION {
    PCON_FORWORD,
    PCON_BACKWORD
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
uint8_t pconSendCommand( polcore* dev, uint8_t* cmd );

/** Shortcut function, sends the global buffer down the serial line.
 */
uint8_t pconSendCommandBuffer( polcore* dev );

/** Generate a command to begin turning the motor at a specified power in the
 * specified direction. Uses the PCON_DIRECTION struct.
 *
 * Doesn't actually send the string down the serial line, call
 * pconSendCommand with the buffer as an argument, or store the value to the
 * global buffer and call pconSendCommandBuffer
 */
uint8_t pconGenMotorGo( polcore* dev, uint8_t* buffer,
        uint8_t percent_power, enum PCON_DIRECTION direction );

/** Shortcut to send a 0 power command to the motor to get it to stop. This is
 * different from braking as there will be no applied voltage.
 */
uint8_t pconGenMotorStop( polcore* dev, uint8_t* buffer );

/** Planned functions
 *
 * Schedule stop time
 * Poll for motor stop conditions
 */

#endif
