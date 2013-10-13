/* Pololu DC Motor controller
 *
 * Revision 0.0.1
 */
#include <pololu_controller.h>

polcore* test_device;

uint8_t cmd_safe_string[] = { 1, 0x03 };
uint8_t cmd_motor_for[] = { 3, 0x05, 0x00, 0x64 };
uint8_t cmd_motor_stop[] = { 3, 0x05, 0x00, 0x00 };

void setup() {
    Serial.begin( 9600 );
    Serial2.begin( 9600 );
    
    test_device = (polcore*) malloc( sizeof(polcore) );
    test_device->serial_line = &Serial2;
    test_device->device_number = 13;
    test_device->control = 0;

    pconSendCommand( test_device, cmd_safe_string );
}

void loop() {
    pconSendCommand( test_device, cmd_safe_string );
    pconSendCommand( test_device, cmd_motor_for );
    delay(500);
    pconSendCommand( test_device, cmd_motor_stop );
    delay(500);

    pconGenMotorGo( test_device, pcon_buffer_to_dev, 45, PCON_FORWORD );
    pconSendCommandBuffer( test_device );
    delay(500);

    if( Serial2.available() != 0 ) Serial.print( (char) Serial2.read() );
}
