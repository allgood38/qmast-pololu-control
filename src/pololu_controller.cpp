#include "pololu_controller.h"

uint8_t pconSendCommand( polcore* dev, uint8_t* command_string ) {

    dev->serial_line->write( PCON_DEFAULT_COMMAND_BYTE );

    for( uint8_t i = 0; command_string[i] != '0x0'; i++ ) {
        dev->serial_line->write( command_string[i] );
    }

    return 0;
}
