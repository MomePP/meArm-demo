#include <Arduino.h>
#line 1 "c:\\Users\\peera\\Desktop\\robotDemo\\robotArm\\robotArm.ino"
#line 1 "c:\\Users\\peera\\Desktop\\robotDemo\\robotArm\\robotArm.ino"
/*
   ESP32 Servo Example
   John K. Bennett
   March, 2017

   This sketch uses low-level ESP32 PWM functionality to sweep 4 servos in sequence.
   It does NOT use the ESP32_Servo library for Arduino.

   The ESP32 supports 16 hardware LED PWM channels that are intended
   to be used for LED brightness control. The low level ESP32 code allows us to set the
   PWM frequency and bit-depth, and then control them by setting bits in the relevant control
   register. The core files esp32-hal-ledc.* provides helper functions to make this set up
   straightforward.

   Different servos require different pulse widths to vary servo angle, but the range is
   an approximately 500-2500 microsecond pulse every 20ms (50Hz). In general, hobbyist servos
   sweep 180 degrees, so the lowest number in the published range for a particular servo
   represents an angle of 0 degrees, the middle of the range represents 90 degrees, and the top
   of the range represents 180 degrees. So for example, if the range is 1000us to 2000us,
   1000us would equal an angle of 0, 1500us would equal 90 degrees, and 2000us would equal 1800
   degrees.

   The ESP32 PWM timers allow us to set the timer width (max 20 bits). Thus
   the timer "tick" length is (pulse_period/2**timer_width), and the equation for pulse_high_width
   (the portion of cycle (20ms in our case) that the signal is high) becomes:

                    pulse_high_width  = count * tick_length
                                      = count * (pulse_period/2**timer_width)

              and count = (pulse_high_width / (pulse_period/2**timer_width))

   For example, if we want a 1500us pulse_high_width, we set pulse_period to 20ms (20000us)
   (this value is set in the ledcSetup call), and count (used in the ledcWrite call) to
   1500/(20000/65655), or 4924. This is the value we write to the timer in the ledcWrite call.

   As a concrete example, suppose we want to repeatedly sweep four Tower Pro SG90 servos
   from 0 to 180 degrees.  The published pulse width range for the SG90 is 500-2400us. Thus,
   we should vary the count used in ledcWrite from 1638 to 7864.

   Circuit:
   Servo motors have three wires: power, ground, and signal. The power wire is typically red,
   the ground wire is typically black or brown, and the signal wire is typically yellow,
   orange or white. Since the ESP32 can supply limited current at only 3.3V, and servos draw
   considerable power, we will connect servo power to the VBat pin of the ESP32 (located
   near the USB connector). THIS IS ONLY APPROPRIATE FOR SMALL SERVOS.

   We could also connect servo power to a separate external
   power source (as long as we connect all of the grounds (ESP32, servo, and external power).
   In this example, we just connect ESP32 ground to servo ground. The servo signal pins
   connect to any available GPIO pins on the ESP32 (in this example, we use pins
   22, 19, 23, & 18).

   In this example, we assume four Tower Pro SG90 small servos.
   The published min and max for this servo are 500 and 2400, respectively.
   These values actually drive the servos a little past 0 and 180, so
   if you are particular, adjust the min and max values to match your needs.
   Experimentally, 550us and 2350us are pretty close to 0 and 180.

   This code was inspired by a post on Hackaday by Elliot Williams.
*/

// Values for TowerPro SG90 small servos; adjust if needed
#define COUNT_LOW 1800
#define COUNT_HIGH 7700

#define middleLimit_LOW 1700
#define middleLimit_HIGH 6200
#define leftLimit_LOW 3350
#define leftLimit_HIGH 6800
#define rightLimit_LOW 1900
#define rightLimit_HIGH 6200
#define clawLimit_LOW 2300
#define clawLimit_HIGH 6000

#define TIMER_WIDTH 16

#define middle 1
#define left 2
#define right 3
#define claw 4

#include "esp32-hal-ledc.h"

const int leftX = 12;
const int leftY = 13;
const int rightX = 26;
const int rightY = 27;
const int rightSwitch = 0;

int middle_currPOS = 3670;
int left_currPOS = 4000;
int right_currPOS = 3500;
int claw_currPOS = 2400;

int leftVRx = 0;
int leftVRy = 0;
int rightVRx = 0;
int rightVRy = 0;

const int servo_relay = 10;
const int servo_scale = 20;

void setup()
{
  Serial.begin(115200);

  pinMode(rightSwitch, INPUT_PULLUP);

  ledcSetup(middle, 50, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
  ledcAttachPin(22, middle);          // GPIO 22 assigned to channel 1

  ledcSetup(left, 50, TIMER_WIDTH); // channel 2, 50 Hz, 16-bit width
  ledcAttachPin(19, left);          // GPIO 19 assigned to channel 2

  ledcSetup(right, 50, TIMER_WIDTH); // channel 3, 50 Hz, 16-bit width
  ledcAttachPin(23, right);          // GPIO 23 assigned to channel 3

  ledcSetup(claw, 50, TIMER_WIDTH); // channel 4, 50 Hz, 16-bit width
  ledcAttachPin(18, claw);          // GPIO 18 assigned to channel 4

  ledcWrite(middle, middle_currPOS);
  ledcWrite(left, left_currPOS);
  ledcWrite(right, right_currPOS);
  ledcWrite(claw, claw_currPOS);
}

void loop()
{
  // leftVRx = analogRead(leftX);
  // leftVRy = analogRead(leftY);
  // rightVRx = analogRead(rightX);
  // rightVRy = analogRead(rightY);

  // Serial.print("VRx: ");
  // Serial.println(leftVRx);
  // Serial.print("VRy: ");
  // Serial.println(leftVRy);

  // // analog left VRy
  // // CCW middle
  // if (leftVRy <= 10 && middle_currPOS > middleLimit_LOW)
  // {
  //   Serial.print("middle position: ");
  //   Serial.println(middle_currPOS);

  //   middle_currPOS -= servo_scale;
  //   ledcWrite(middle, middle_currPOS);
  //   delay(servo_relay);
  // }

  // // CW middle
  // if (leftVRy >= 4090 && middle_currPOS < middleLimit_HIGH)
  // {
  //   Serial.print("middle position: ");
  //   Serial.println(middle_currPOS);

  //   middle_currPOS += servo_scale;
  //   ledcWrite(middle, middle_currPOS);
  //   delay(servo_relay);
  // }

  // // analog left VRy
  // // UP left
  // if (rightVRx <= 10 && left_currPOS > leftLimit_LOW)
  // {
  //   Serial.print("left position: ");
  //   Serial.println(left_currPOS);

  //   left_currPOS -= servo_scale;
  //   ledcWrite(left, left_currPOS);
  //   delay(servo_relay);
  // }

  // // DOWN left
  // if (rightVRx >= 4090 && left_currPOS < leftLimit_HIGH)
  // {
  //   Serial.print("left position: ");
  //   Serial.println(left_currPOS);

  //   left_currPOS += servo_scale;
  //   ledcWrite(left, left_currPOS);
  //   delay(servo_relay);
  // }

  // // // analog right VRx
  // // // CCW claw
  // if (rightVRy <= 10 && claw_currPOS > clawLimit_LOW)
  // {
  //   Serial.print("claw position: ");
  //   Serial.println(claw_currPOS);

  //   claw_currPOS -= servo_scale;
  //   ledcWrite(claw, claw_currPOS);
  //   delay(servo_relay);
  // }

  // // CW claw
  // if (rightVRy >= 4090 && claw_currPOS < clawLimit_HIGH)
  // {
  //   Serial.print("claw position: ");
  //   Serial.println(claw_currPOS);

  //   claw_currPOS += servo_scale;
  //   ledcWrite(claw, claw_currPOS);
  //   delay(servo_relay);
  // }

  // // analog right VRy
  // // UP right
  // if (leftVRx >= 4090 && right_currPOS > rightLimit_LOW)
  // {
  //   Serial.print("right position: ");
  //   Serial.println(right_currPOS);

  //   right_currPOS -= servo_scale;
  //   ledcWrite(right, right_currPOS);
  //   delay(servo_relay);
  // }

  // // DOWN right
  // if (leftVRx <= 10 && right_currPOS < rightLimit_HIGH)
  // {
  //   Serial.print("right position: ");
  //   Serial.println(right_currPOS);

  //   right_currPOS += servo_scale;
  //   ledcWrite(right, right_currPOS);
  //   delay(servo_relay);
  // }

  if (!digitalRead(rightSwitch))
  {
    Serial.println("Switch press");
    gotoPOS(middle, 5030);
    gotoPOS(claw, 2340);
    gotoPOS(left, 2600);
    gotoPOS(right, 6100);
    gotoPOS(left, 3800);
    gotoPOS(claw, 5160);

    gotoPOS(right, 5800);
    gotoPOS(left, 2540);
    gotoPOS(right, 3940);
    gotoPOS(middle, 2410);
    
    gotoPOS(right, 2800);
    gotoPOS(left, 5400);
    gotoPOS(right, 4520);
    gotoPOS(claw, 2340);

    gotoPOS(right, 2440);
    gotoPOS(left, 3580);
    gotoPOS(middle, 3670);


    while (!digitalRead(rightSwitch))
    {
    }
  }
}

void gotoPOS(int servo, int position)
{
  switch (servo)
  {
  case middle:
    if (position > middle_currPOS && position < middleLimit_HIGH)
    {
      while (middle_currPOS < position)
      {
        middle_currPOS += servo_scale;
        ledcWrite(middle, middle_currPOS);
        delay(servo_relay);
      }
    }
    else if (position < middle_currPOS && position > middleLimit_LOW)
    {
      while (middle_currPOS > position)
      {
        middle_currPOS -= servo_scale;
        ledcWrite(middle, middle_currPOS);
        delay(servo_relay);
      }
    }
    else
    {
    }
    break;

  case left:
    if (position > left_currPOS && position < leftLimit_HIGH)
    {
      while (left_currPOS < position)
      {
        left_currPOS += servo_scale;
        ledcWrite(left, left_currPOS);
        delay(servo_relay);
      }
    }
    else if (position < left_currPOS && position > leftLimit_LOW)
    {
      while (left_currPOS > position)
      {
        left_currPOS -= servo_scale;
        ledcWrite(left, left_currPOS);
        delay(servo_relay);
      }
    }
    else
    {
    }
    break;

  case right:
    if (position > right_currPOS && position < rightLimit_HIGH)
    {
      while (right_currPOS < position)
      {
        right_currPOS += servo_scale;
        ledcWrite(right, right_currPOS);
        delay(servo_relay);
      }
    }
    else if (position < right_currPOS && position > rightLimit_LOW)
    {
      while (right_currPOS > position)
      {
        right_currPOS -= servo_scale;
        ledcWrite(right, right_currPOS);
        delay(servo_relay);
      }
    }
    else
    {
    }
    break;

  case claw:
    if (position > claw_currPOS && position < clawLimit_HIGH)
    {
      while (claw_currPOS < position)
      {
        claw_currPOS += servo_scale;
        ledcWrite(claw, claw_currPOS);
        delay(servo_relay);
      }
    }
    else if (position < claw_currPOS && position > clawLimit_LOW)
    {
      while (claw_currPOS > position)
      {
        claw_currPOS -= servo_scale;
        ledcWrite(claw, claw_currPOS);
        delay(servo_relay);
      }
    }
    else
    {
    }
    break;
  }
}

