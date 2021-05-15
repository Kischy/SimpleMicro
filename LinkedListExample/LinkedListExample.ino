#include "StaticLList.h"

//#include "LList.h"

//smpmcr::LList<byte> exampleList;
smpmcr::StaticLList<String> exampleList;

const long BAUDRATE = 115200;
String command = "";

void setup() 
{
     Serial.begin(BAUDRATE);
}

void loop() 
{
    if(Serial.available()) 
    {
        command = Serial.readString()
    }

    if(command.length() >= 3 && command[0] == "a" && command[1] == "+")
    {
       exampleList.push_front(command.substr(2));
    }

    for(auto it = exampleList.begin(); it != exampleList.end(); ++it)
    {
        Serial.println(*it);
    }

    delay(1000);
}    
