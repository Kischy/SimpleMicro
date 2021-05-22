
#include <SimpleMicro.h>


// This are the functions that are called back, when the timer detects a timeout
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


// Defining the timer functionality. First parameter is the pointer to a function that measures the time. 
// Second parameter is a pointer to the callback function
// First parameter: unsigned long (*)()
// Second parameter: void (*)()
smpmcr::Timer timer1(&millis, &printT1);
smpmcr::Timer timer2(&millis, &printT2);
smpmcr::Timer timer3(&millis, &printT3);
smpmcr::Timer timer4(&millis, &printT4);
smpmcr::Timer timer5(&millis, &printT5);

smpmcr::EventListener<10> eventListener;



void setup() 
{
    Serial.begin(115200);

    eventListener.add(&timer1);
    eventListener.add(&timer2);
    eventListener.add(&timer3);
    eventListener.add(&timer4);
    eventListener.add(&timer5);

    // When starting a timer a timeout is given
    timer1.start(1000);
    timer2.start(2000);
    timer3.start(3000);
    timer4.start(4000);
    timer5.start(4500);
}

void loop() 
{
    // Whenever update is called on a timer, it checks for a timeout and calls the callback function if neccessary
    // Old way    
    /*timer1.update();
    timer2.update();
    timer3.update();
    timer4.update();
    timer5.update();*/

    // New way, call Update on the EventListener
    eventListener.updateAll();
}    
