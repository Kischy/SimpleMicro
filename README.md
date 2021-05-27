# Simple Micro library

A lightweight library I use in one of my Arduino projects. It provides Timer funcionality, Event/Listener (not yet) functionality and a linked List. I only implement the parts I need ^^.


# Getting started
To use the library simply clone this repository to your Arduino libraries ("Arduino Install Path"\libraries). One can have a look at the examples or simply `#include <SimpleMicro.h>`.

## EventListener
Events, e.g. the Timer, can be added to a EventListener. To use the EventListener do
```c++
smpmcr::EventListener<10> eventListener; // Initialize eventListener with a maximum of 10 Events
// Adds two objects of type class Timer to the eventListener
eventListener.add(&timer1); 
eventListener.add(&timer2);
//call updateAll in the eventLoop to check if an event has occured
eventListener.updateAll(); 

eventListener.remove(&timer2); //Removes the event from the eventListener, so if updateAll is called the event will not trigger
```

Also see the Timer.ino example.

## Timer
To use a timer use e.g. 
```c++
smpmcr::Timer timer(&millis, &callbackFunction); // Initialize timer via Timer(unsigned long (*getTime)(), void (*timeOutCallback)() = nullptr); constructor.
timer.start(1000); // Start timer with timeoutTime 1000.
// Checks if the timer has a timeout and calls the callbackFunction if it does. If multiple timers or events are used one can add them to a EventListener and call updateAll()
timer.update(); 
timer.stop(); // Stops timer from running.
timer.isRunning(); // Checks if timer is running.
```
Here `millis` is a function that measures time (signature:`unsigned long (*getTime)()`). `callbackFunction` is the callback that is called when the timer has a timeout (signature:`void (*timeOutCallback)()`). `1000` is the timeout time in whatever unit the time function uses. Every time `update()` is called it is checked if the timer has a timeout and the callback function is called. 

## Linked list
To use a static linked list use e.g.
```c++
smpmcr::StaticLList<int,50> list; // Initializes a list of integers with a maximum size of 50.
list.pushFront(99); // Pushes 99 to the front of the list.
list.popFront(); // Removes the first element from a list.
list.clear(); // Clears the list
int front = list.front();  // Returns the value at the front of the list. This call is undefined, if the list is empty.
bool isListEmpty = list.empty(); // Checks whether the list is empty.
size_t currentSize = list.size(); // Returns the size of the list.
list.maxSize(); // Returns the maximum size of the lost.
smpmcr::StaticLList<int,50>::Iterator it = list.begin(); // Returns a iterator to the first element
auto it = list.begin(); // Returns a iterator to the first element
list.end(); // Returns a iterator that is past the last element
// The iterator can be incremented, two iterators can be compared for equality and unequality. 
// See for loop in LinkedList Example.


// Removes the first element that has value 99 and returns true. If no element is found with that value it returns false.
// The second parameter is a comparison function: bool (*isEqualComparisonFunc)(const T&, const T&).
bool wasRemoved = list.eraseFirstFound(99,isEqualComparisonFunc);

// Removes all elements that have 99 and returns the number of elements removed.
// The second parameter is a comparison function: bool (*isEqualComparisonFunc)(const T&, const T&).
size_t numberOfRemovedElements = list.eraseAllFound(99,isEqualComparisonFunc); 
```

To use a dynamic linked list use e.g.

```c++
smpmcr::LList<int> list; // Initializes a list of integers
```
The dynamic linked list has all the functionality of the static linked list except for the `maxSize` function. Do use this class with care. Also see the LinkedList.ino example.


### ToDo list:

 - Test Button Event with real button. Update example.
 
 - Add Examples to Readme

 - Add keylist with syntax highlighting

 - Add const iterator to Linked List classes
