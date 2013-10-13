#include "pololu_controller.h"

uint8_t pcon_buffer_to_dev[PCON_MAX_TO_DEV];
uint8_t pcon_buffer_from_dev[PCON_MAX_FROM_DEV];

uint8_t pconSendCommand( polcore* dev, uint8_t* cmd ) {

    dev->serial_line->write( PCON_DEFAULT_COMMAND_BYTE );
    dev->serial_line->write( dev->device_number );

    // Starts at one since first byte is the number of bytes to be printed
    for( uint8_t i = 1; i <= cmd[0]; i++ ) {
        dev->serial_line->write( cmd[i] );
    }

    return 0;
}

uint8_t pconSendCommandBuffer( polcore* dev ) {
    return pconSendCommand( dev, pcon_buffer_to_dev );
}

uint8_t pconGenMotorGo( polcore* dev, uint8_t* buffer,
        uint8_t percent_power, enum PCON_DIRECTION direction ) {
    uint8_t direction_command;

    if( direction == PCON_FORWORD ) {
        direction_command = 0x05;
    } else if ( direction == PCON_BACKWORD ) {
        direction_command = 0x06;
    } else {
        // DEBUG Serial --> Invalid command
        return 1;
    }

    buffer[0] = 3; /* Number of bytes to be sent will always be 3 with this
                    * command
                    */
    buffer[1] = direction_command;
    buffer[2] = 0x00;
    buffer[3] = percent_power;

    return 0;
}

uint8_t pconGenMotorStop( polcore* dev, uint8_t* buffer ) {
    return pconGenMotorGo( dev, buffer, 0x0, PCON_FORWORD );
}
