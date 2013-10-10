/* Pololu DC Motor controller
 *
 * Revision 0.0.1
 */
#include "pololu_controller.h"

polcore* test_device;

void setup() {
    Serial.begin( 9600 );
    Serial2.begin( 9600 );
    
    Serial2.write( 0xAA );
    Serial2.write( 0x0D );
    Serial2.write( 0x03 );
}

void loop() {
    Serial2.write( 0xAA );
    Serial2.write( 0x0D );
    Serial2.write( 0x05 );
    Serial2.write( 0x00 );
    Serial2.write( 0x64 );

    delay(1000);

    Serial2.write( 0xAA );
    Serial2.write( 0x0D );
    Serial2.write( 0x05 );
    Serial2.write( 0x00 );
    Serial2.write( 0x00 );

    delay( 1000 );

    Serial2.write( 0xAA );
    Serial2.write( 0x0D );
    Serial2.write( 0x06 );
    Serial2.write( 0x00 );
    Serial2.write( 0x64 );

    delay( 1000 );

    Serial2.write( 0xAA );
    Serial2.write( 0x0D );
    Serial2.write( 0x21 );
    Serial2.write( 0x00 );

    if( Serial2.available() != 0 ) Serial.print( (char) Serial2.read() );
}
