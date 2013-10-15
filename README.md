qmast-pololu-control
====================

Pololu binary protocol control for the Arduino.

Compiled with <inotool.org>

## Usage

You need to define and initialise a serial line connected to the pololu. The
pololu needs to be configured the same way as the wiki specifies. The main
thing is that you get the baud-rate right and set it to use the "pololu"
protocol.

```Arduino
#include <pololu_controller.h>

polcore* some_motor;

void setup() {
    Serial2.begin(9600);

    pconInitialise( some_motor, &Serial2, 13 );
}

void loop() {
    pconGenMotorGo( some_motor, pcon_buffer_to_dev, 45, PCON_FORWARD );
    pconSendCommandBuffer( some_motor );
    delay(100)
    
    pconGenMotorStop( some_motor, pcon_buffer_to_dev );
    pconSendCommandBuffer( some_motor );
    delay(100);
}
```

### Rational

This just barely abstracts away specifying the byte strings in their raw form.
These commands will be used as the base for the API header file. When the API
is created, it will specify the motors by name, (i.e. mast)

Furthermore, these commands will be extended to check for a stop condition for
each movement.
