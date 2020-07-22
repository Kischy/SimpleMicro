
#include "Timer.h"


Timer timer1([](){return millis();}]);

void setup() 
{
    Serial.begin(115200);
}

void loop() 
{
    Serial.println("hello");
    delay(10); 
}    
