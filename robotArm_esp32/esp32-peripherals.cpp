#include "Arduino.h"
#include "esp32-peripherals.h"
#include "esp32-hal-ledc.h"

esp32Peripherals::esp32Peripherals(void)
{
    // Analog Port initialize
    pinMode(port_A1, ANALOG);
    pinMode(port_A2, ANALOG);
    pinMode(port_A3, ANALOG);
    pinMode(port_A4, ANALOG);
    pinMode(JOYSTICK, ANALOG);

    // Beeper initialize
    ledcSetup(Beeper_Channel, Beeper_DEFAULT_Freq, Beeper_RESOLUTION); // channel 5, 2000 Hz, 8-bit width
    ledcAttachPin(12, 5);                                              // GPIO 12 assigned to channel 5
}

// Analog implementation
int esp32Peripherals::readAnalogPort(int port)
{
    int sensor_pin;

    switch (port)
    {
    case 0:
        sensor_pin = port_A1;
        break;
    case 1:
        sensor_pin = port_A2;
        break;
    case 2:
        sensor_pin = port_A3;
        break;
    case 3:
        sensor_pin = port_A4;
        break;
    default:
        return 0;
    }
    return analogRead(sensor_pin);
}

// Analog JoyStick implementation
int esp32Peripherals::readJoyStick(void)
{
    return analogRead(JOYSTICK);
}

// Beeper implementation
void esp32Peripherals::turn_beep(int volume, int frequency)
{
    if (frequency)
    {
        ledcWriteTone(Beeper_Channel, frequency);
    }
    ledcWrite(Beeper_Channel, volume);
}

void esp32Peripherals::beep()
{
    ledcWriteTone(Beeper_Channel, 2500);
    ledcWrite(Beeper_Channel, 200);
    delay(40);
    ledcWrite(Beeper_Channel, 0);
}

void esp32Peripherals::stop_beep()
{
    ledcWrite(Beeper_Channel, 0);
}
