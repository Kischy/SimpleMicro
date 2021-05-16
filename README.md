# Simple Micro library

A lightweight library I use in one of my Arduino projects. It provides Timer funcionality, Event/Listener (not yet) functionality and a linked List. I only implement the parts I need ^^.


# Getting started
To use the library simply clone this repository to your Arduino libraries ("Arduino Install Path"\libraries). One can have a look at the examples or simply `#include <SimpleMicro.h>`

## Timer
To use a timer use e.g. 
```c++
smpmcr::Timer timer(&millis, &callbackFunction); // Initialize timer.
timer.start(1000); // Start timer with timeoutTime 1000.
timer.update(); // Checks if the timer has a timeout and calls the callbackFunction if it does.
timer.stop(); // Stops timer from running.
timer.isRunning(); // Checks if timer is running.
```
Here `millis` is a function that measures time. `callbackFunction` is the callback that is called when the timer has a timeout. `1000` is the timeout time in whatever unit the time function uses. Every time `update()` is called it is checked if the timer has a timeout and the callback function is called.

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
The dynamic linked list has all the functionality of the static linked list except for the `maxSize` function. Do use this class with care. Using dynamic memory allocation on a microcontroller can lead to heap fragmentation.


ToDo list:

 - Add Timer Listener

 - Add Example for Timer Listener

 - Add EventListener

 - Add Example for EventListener

 - Add custom Events

 - Add Examples for custom Events

 - Add Examples to Readme

 - Add keylist with syntax highlighting

 - Add const iterator to Linked List classes
