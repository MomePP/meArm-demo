#define DIR D4         // StepMotor connect NodeMCU PIN D4
#define STP D3         // StepMotor connect NodeMCU PIN D3
#define magnet D2      // Electromagnet Pin D2
#define limitSwitch D0 // limitSwitch Pin D0
#define enable D1

void setup()
{
    Serial.begin(115200);

    pinMode(DIR, OUTPUT);
    pinMode(STP, OUTPUT);
    pinMode(enable, OUTPUT);
    pinMode(magnet, OUTPUT);
    pinMode(limitSwitch, INPUT);

    digitalWrite(magnet, LOW);
    digitalWrite(enable, LOW);
    delay(5);

    while (digitalRead(limitSwitch))
    {
        digitalWrite(DIR, LOW);
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
        // Serial.print("doing calibrate");
    }
    Serial.print("done");
}

void loop()
{
    digitalWrite(enable, LOW);
    delay(50);
    digitalWrite(DIR, HIGH);
    delay(50);
    for (int i = 0; i < 250; i++)
    {
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }

    delay(1000);

    digitalWrite(magnet, HIGH);
    delay(500);

    for (int i = 0; i < 750; i++)
    {
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }
    delay(500);
    digitalWrite(magnet, LOW);

    delay(1000);

    digitalWrite(DIR, LOW);
    delay(50);
    while (digitalRead(limitSwitch))
    {
        digitalWrite(DIR, LOW);
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }
    // finish first object

    delay(1000);

    digitalWrite(magnet, HIGH);
    delay(500);

    digitalWrite(DIR, HIGH);
    delay(50);
    for (int i = 0; i < 750; i++)
    {
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }
    delay(500);
    digitalWrite(magnet, LOW);

    delay(1000);

    ///////////////////////////////////////////////////////////////////////////////////////////
    digitalWrite(DIR, LOW);
    delay(50);
    while (digitalRead(limitSwitch))
    {
        digitalWrite(DIR, LOW);
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }

    delay(1000);

    digitalWrite(DIR, HIGH);
    delay(50);
    for (int i = 0; i < 750; i++)
    {
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }
    delay(500);

    digitalWrite(DIR, LOW);
    delay(50);

    digitalWrite(magnet, HIGH);
    delay(500);

    while (digitalRead(limitSwitch))
    {
        digitalWrite(DIR, LOW);
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }

    delay(500);
    digitalWrite(magnet, LOW);
    delay(1000);

    digitalWrite(DIR, HIGH);
    delay(50);
    for (int i = 0; i < 1000; i++)
    {
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }
    delay(500);
    digitalWrite(magnet, HIGH);

    delay(500);

    digitalWrite(DIR, LOW);
    delay(50);
    for (int i = 0; i < 750; i++)
    {
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }
    delay(500);
    digitalWrite(magnet, LOW);
    delay(500);

    while (digitalRead(limitSwitch))
    {
        digitalWrite(DIR, LOW);
        digitalWrite(STP, HIGH);
        delayMicroseconds(600);
        digitalWrite(STP, LOW);
        delayMicroseconds(600);
    }
    // finish

    digitalWrite(enable, HIGH);
    delay(2000);
}