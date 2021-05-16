#include <SimpleMicro.h>


// LList is a dynamic linked list and StaticLList i a static linked list (the second parameter is the maximum size)
// The dynamic linked list can lead to heap fragmentation on a microcontroller, therefore prefer the StaticLList.
//smpmcr::LList<String> exampleList; 
smpmcr::StaticLList<String,50> exampleList;

const long BAUDRATE = 115200;
String command = "";


bool compareStrings(const String& l, const String& r)
{
    return l == r;
}


void setup() 
{
     Serial.begin(BAUDRATE);
}

void loop() 
{
    if(Serial.available()) 
    {
        command = Serial.readString();
    }

    if(command.length() >= 3 && command[0] == 'a' && command[1] == '+')
    {
       // Add something to the front. You can pop the front via popFront. 
       // Access the front via front (front is undefined, when size() == 0)
       exampleList.pushFront(command.substring(2));
       command = "";
       Serial.println("Added: " + command.substring(2));
    }

    if(command.length() == 2 && command[0] == 'c' && command[1] == '+')
    {
       // Clearing a list
       exampleList.clear();
       Serial.println("Cleared list.");
       command = "";
    }
        
    if(command.length() >= 3 && command[0] == 'd' && command[1] == '+')
    {
       // Erase the first element with a specific value found in a list
       bool removed = exampleList.eraseFirstFound(command.substring(2),compareStrings);
       if(removed == true)
       {
          Serial.println("Deleted: " + command.substring(2));
       }
       command = "";
    }
        
    if(command.length() >= 4 && command[0] == 'd' && command[1] == 'a' && command[2] == '+')
    {
       // Erase all the elements with a specific value found in a list
       size_t removedNo = exampleList.eraseAllFound(command.substring(3),compareStrings);
       if(removedNo > 0)
       {
          Serial.print("Deleted ");
          Serial.print(removedNo);
          Serial.print(" items. ");
          Serial.println("Deleted all:" + command.substring(2));
       }
       command = "";
    }

    // Here the lst is printed to the Serial Monitor via iterators
    int index = 0;
    for(auto it = exampleList.begin(); it != exampleList.end(); ++it,++index)
    {
        Serial.print(index);
        Serial.print(":");
        Serial.println(*it);
    }
    
    delay(1000);
    Serial.println("-----------------------------------------");

}    
