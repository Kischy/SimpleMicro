
#include "Timer.h"


void printT1()
{
    Serial.print("Timer 1: ");
    Serial.println(millis());
}

void printT2()
{
    Serial.print("Timer 2: ");
    Serial.println(millis());
}

void printT3()
{
    Serial.print("Timer 3: ");
    Serial.println(millis());
}

void printT4()
{
    Serial.print("Timer 4: ");
    Serial.println(millis());
}

void printT5()
{
    Serial.print("Timer 5: ");
    Serial.println(millis());
}


smpmcr::Timer timer1(&millis, &printT1);
smpmcr::Timer timer2(&millis, &printT2);
smpmcr::Timer timer3(&millis, &printT3);
smpmcr::Timer timer4(&millis, &printT4);
smpmcr::Timer timer5(&millis, &printT5);



void setup() 
{
    Serial.begin(115200);

    timer1.start(1000);
    timer2.start(2000);
    timer3.start(3000);
    timer4.start(4000);
    timer5.start(4500);
}

void loop() 
{
    timer1.listen();
    timer2.listen();
    timer3.listen();
    timer4.listen();
    timer5.listen();
}    
