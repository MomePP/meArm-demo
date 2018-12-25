#include <Servo.h> 
Servo clawServo;
Servo leftServo;
Servo rightServo;
Servo middleServo;


#define middleLimit_LOW 0
#define middleLimit_HIGH 180
#define leftLimit_LOW 0
#define leftLimit_HIGH 180
#define rightLimit_LOW 0
#define rightLimit_HIGH 180
#define clawLimit_LOW 0
#define clawLimit_HIGH 180

#define TIMER_WIDTH 16

#define middle 1
#define left 2
#define right 3
#define claw 4

const int leftX = A0;
const int leftY = A1;
const int rightX = A2;
const int rightY = A3;
const int rightSwitch = A4;

int middle_currPOS = 3490;
int left_currPOS = 3600;
int right_currPOS = 3500;
int claw_currPOS = 2400;

int leftVRx = 0;
int leftVRy = 0;
int rightVRx = 0;
int rightVRy = 0;

const int servo_relay = 10;
const int servo_scale = 1;

void setup()
{
  Serial.begin(115200);

  pinMode(rightSwitch, INPUT_PULLUP);
  pinMode(leftX, INPUT);
  pinMode(leftY, INPUT);
  pinMode(rightX, INPUT);
  pinMode(rightY, INPUT);

  middleServo.attach(5);
  leftServo.attach(6);
  rightServo.attach(10);
  clawServo.attach(11);

  middleServo.write(50);
  // leftServo.write(90);
  // rightServo.write(90);
  // clawServo.write(90);
  


  // ledcSetup(middle, 50, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
  // ledcAttachPin(22, middle);          // GPIO 22 assigned to channel 1

  // ledcSetup(left, 50, TIMER_WIDTH); // channel 2, 50 Hz, 16-bit width
  // ledcAttachPin(19, left);          // GPIO 19 assigned to channel 2

  // ledcSetup(right, 50, TIMER_WIDTH); // channel 3, 50 Hz, 16-bit width
  // ledcAttachPin(23, right);          // GPIO 23 assigned to channel 3

  // ledcSetup(claw, 50, TIMER_WIDTH); // channel 4, 50 Hz, 16-bit width
  // ledcAttachPin(18, claw);          // GPIO 18 assigned to channel 4

  // ledcWrite(middle, middle_currPOS);
  // ledcWrite(left, left_currPOS);
  // ledcWrite(right, right_currPOS);
  // ledcWrite(claw, claw_currPOS);
}

void loop()
{
  // leftVRx = analogRead(leftX);
  // leftVRy = analogRead(leftY);
  // rightVRx = analogRead(rightX);
  // rightVRy = analogRead(rightY);

  // // Serial.print("VRx: ");
  // // Serial.println(leftVRx);
  // // Serial.print("VRy: ");
  // // Serial.println(leftVRy);

  // // analog left VRy
  // // CCW middle
  // if (leftVRy <= 10 && middle_currPOS > middleLimit_LOW)
  // {
  //   middle_currPOS -= servo_scale;
  //   middleServo.write(middle_currPOS);
  //   delay(servo_relay);
  // }

  // // CW middle
  // if (leftVRy >= 4090 && middle_currPOS < middleLimit_HIGH)
  // {
  //   middle_currPOS += servo_scale;
  //   middleServo.write(middle_currPOS);
  //   delay(servo_relay);
  // }

  // // analog left VRy
  // // UP left
  // if (rightVRx <= 10 && left_currPOS > leftLimit_LOW)
  // {
  //   left_currPOS -= servo_scale;
  //   leftServo.write(left_currPOS);
  //   delay(servo_relay);
  // }

  // // DOWN left
  // if (rightVRx >= 4090 && left_currPOS < leftLimit_HIGH)
  // {
  //   left_currPOS += servo_scale;
  //   leftServo.write(left_currPOS);
  //   delay(servo_relay);
  // }

  // // // analog right VRx
  // // // CCW claw
  // if (rightVRy <= 10 && claw_currPOS > clawLimit_LOW)
  // {
  //   claw_currPOS -= servo_scale;
  //   clawServo.write(claw_currPOS);
  //   delay(servo_relay);
  // }

  // // CW claw
  // if (rightVRy >= 4090 && claw_currPOS < clawLimit_HIGH)
  // {
  //   claw_currPOS += servo_scale;
  //   clawServo.write(claw_currPOS);
  //   delay(servo_relay);
  // }

  // // analog right VRy
  // // UP right
  // if (leftVRx >= 4090 && right_currPOS > rightLimit_LOW)
  // {
  //   right_currPOS -= servo_scale;
  //   rightServo.write(right_currPOS);
  //   delay(servo_relay);
  // }

  // // DOWN right
  // if (leftVRx <= 10 && right_currPOS < rightLimit_HIGH)
  // {
  //   right_currPOS += servo_scale;
  //   rightServo.write(right_currPOS);
  //   delay(servo_relay);
  // }

  // if (!digitalRead(rightSwitch))
  // {
  //   Serial.println("Switch press");
  //   gotoPOS(middle, 5030);
  //   gotoPOS(claw, 2340);
  //   gotoPOS(left, 2600);
  //   gotoPOS(right, 6100);
  //   gotoPOS(left, 3800);
  //   gotoPOS(claw, 5160);

  //   gotoPOS(right, 5800);
  //   gotoPOS(left, 2540);
  //   gotoPOS(right, 3940);
  //   gotoPOS(middle, 2410);
    
  //   gotoPOS(right, 2800);s
  //   gotoPOS(left, 5400);
  //   gotoPOS(right, 4520);
  //   gotoPOS(claw, 2340);

  //   gotoPOS(right, 2440);
  //   gotoPOS(left, 3580);
  //   gotoPOS(middle, 3490);


  //   while (!digitalRead(rightSwitch))
  //   {
  //   }
  // }
}