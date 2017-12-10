#include <Bounce2.h>
#include <stdint.h>

Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();

  int running = 0;
  int32_t startTime = 0;
  int down = 0;
  int down2 = 0;
  int32_t timeDelay = 45000;
  int led45 = 2;
  int led90 = 3;
  int led180 = 4;
  int led360 = 5;
  int motorPin = 6;
  int timerButton = 7; //D7
  int startButton = 8; //D8

void setup() {

    Serial.begin(9600);
    
    pinMode(led45,OUTPUT); //D2 45s LED
    pinMode(led90,OUTPUT); //D3 90
    pinMode(led180,OUTPUT); //D4 180
    pinMode(led360,OUTPUT); //D5 360 
    pinMode(motorPin,OUTPUT); //D6 Motor relay
    pinMode(timerButton, INPUT_PULLUP);
    pinMode(startButton, INPUT_PULLUP);
    
    debouncer1.attach(timerButton);
    debouncer1.interval(50);
    
    debouncer2.attach(startButton);
    debouncer2.interval(50);
    
    digitalWrite(led45, HIGH);
    digitalWrite(led90, LOW);
    digitalWrite(led180, LOW);
    digitalWrite(led360, LOW);
    digitalWrite(motorPin, LOW);
}

void loop() {
    
    debouncer1.update();
    debouncer2.update();

    int value1 = debouncer1.read();
    int value2 = debouncer2.read();

    if(value1 == LOW && down == 0)
        {
            down = 1;
            switch (timeDelay)
            {
                case 45000:
                timeDelay = 90000;
                digitalWrite(led45, LOW);
                digitalWrite(led90, HIGH);
                break;
            case 90000:
                timeDelay = 180000;
                digitalWrite(led90, LOW);
                digitalWrite(led180, HIGH);
                break;
            case 180000:
                timeDelay = 360000;
                digitalWrite(led180, LOW);
                digitalWrite(led360, HIGH);
                break;
            case 360000:
                timeDelay = 45000;
                digitalWrite(led360, LOW);
                digitalWrite(led45, HIGH);
                break;
                };
            }else if(value1 == HIGH)
            {
              down = 0;
            }

    if(value2 == LOW && down2 == 0)
        {
            if(running == 0)
            {
                startTime = millis();
                running = 1;
                digitalWrite(motorPin, HIGH);
                Serial.println("Motor on");
                down2 = 1;
            }else 
            {
                digitalWrite(motorPin, LOW);
                running = 0;
                Serial.println("Motor off 1");
                down2 = 1;
            }
        }else if(value2 == HIGH)
        {
          down2 = 0;
        }

        

    if(((millis() - startTime) >= timeDelay) && running == 1)
    {
        Serial.println("Motor Off 2");
        digitalWrite(motorPin, LOW);
        running = 0;
        down2 = 0;
    }

}
