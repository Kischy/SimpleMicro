
#include "ArdTimer.h"


ck::ArdTimer timer1(&millis);

void setup() 
{
    Serial.begin(115200);
}

void loop() 
{
    Serial.println("hello");
    delay(10000); 
}    
