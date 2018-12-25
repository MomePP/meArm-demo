#ifndef esp32Peripherals_h
#define esp32Peripherals_h

#include "Arduino.h"

#define Beeper_RESOLUTION       8
#define Beeper_DEFAULT_Freq     2000

#define port_A1                 35
#define port_A2                 34
#define port_A3                 39
#define port_A4                 36

#define JOYSTICK                33

#define Beeper_Channel          5

class esp32Peripherals
{
  public:
    esp32Peripherals(void);

    int readAnalogPort(int port);
    int readJoyStick(void);

    void turn_beep(int volume, int frequency);
    void beep();
    void stop_beep();
    
  private:
    
};

#endif
