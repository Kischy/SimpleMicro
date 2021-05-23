#define SIMPLE_MICRO_FOR_ARDUINO //Has to be defined for convenience. The ButtonEvent is easier to use with this if used on an Arduino
#include "SimpleMicro.h"

void printTimer()
{
    Serial.print("Timer: ");
    Serial.println(millis());
}

void pressedButton()
{
    Serial.print("Single pressed");
}

void doublePressedButton()
{
    Serial.print("Double pressed");
}

const int buttonPin = 2;   
smpmcr::Timer timer(&millis, &printTimer);
smpmcr::ButtonEvent buttonEvent(&pressedButton,&doublePressedButton);
smpmcr::EventListener<10> eventListener;

 

void setup() {
  eventListener.add(&timer);
  eventListener.add(&buttonEvent);  
  buttonEvent.setPin(buttonPin);
  timer.start(5000);
}

void loop() {
  eventListener.updateAll();
}
