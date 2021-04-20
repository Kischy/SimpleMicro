cmake_minimum_required(VERSION 3.19)

project(SimpleMicroTests) 

add_subdirectory(googletest) 
include_directories(googletest/include)

add_executable(SimpleMicroTests main.cpp TimerTests.cpp) 

target_link_libraries(SimpleMicroTests PRIVATE gtest) 

