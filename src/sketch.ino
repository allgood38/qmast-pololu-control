/* Pololu DC Motor controller
 *
 * Revision 0.0.1
 */
#include <pololu_controller.h>
#include <ArduinoPrintf.h>

polcore* mast;
polcore* sail;

ArduinoPrintf* sout;

uint8_t cmd_safe_string[] = { 1, 0x03 };
uint8_t cmd_motor_for[] = { 3, 0x05, 0x00, 0x64 };
uint8_t cmd_motor_stop[] = { 3, 0x05, 0x00, 0x00 };

void setup() {
    Serial.begin( 9600 );
    Serial2.begin( 9600 );

    sout = new ArduinoPrintf( &Serial );
    
    pconInitialise( &mast, &Serial2, 12 );
    pconInitialise( &sail, &Serial2, 13 );

    /*sout->printf("test_device -> %lu \r\n", test_device );*/
    delay(100);
}

void loop() {

    pconGenMotorGo( mast, pcon_buffer_to_dev, 45, PCON_FORWORD );
    pconSendCommandBuffer( mast );
    pconGenMotorGo( sail, pcon_buffer_to_dev, 45, PCON_BACKWORD );
    pconSendCommandBuffer( sail );
    delay(500);

    pconGenMotorGo( mast, pcon_buffer_to_dev, 45, PCON_BACKWORD );
    pconSendCommandBuffer( mast );
    pconGenMotorGo( sail, pcon_buffer_to_dev, 45, PCON_FORWORD );
    pconSendCommandBuffer( sail );
    delay(500);

    pconGenMotorStop( mast, pcon_buffer_to_dev );
    pconSendCommandBuffer( mast );
    pconGenMotorStop( sail, pcon_buffer_to_dev );
    pconSendCommandBuffer( sail );

    for( uint8_t i = 0; i < 100; i++ ) {
        pconGenMotorGo( mast, pcon_buffer_to_dev, i, PCON_BACKWORD );
        pconSendCommandBuffer( mast );
        delay(2);
    }
    delay(1000);
    pconGenMotorStop( mast, pcon_buffer_to_dev );
    pconSendCommandBuffer( mast );

    for( uint8_t i = 0; i < 100; i++ ) {
        pconGenMotorGo( sail, pcon_buffer_to_dev, i, PCON_FORWORD );
        pconSendCommandBuffer( sail );
    }
    delay(1000);
    pconGenMotorStop( mast, pcon_buffer_to_dev );
    pconSendCommandBuffer( mast );


    if( Serial2.available() != 0 ) Serial.print( (char) Serial2.read() );
}
