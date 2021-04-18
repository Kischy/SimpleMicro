cmake_minimum_required(VERSION 3.19)

project(SimpleTimerTests) 

add_subdirectory(googletest) 
include_directories(googletest/include)

add_executable(SimpleTimerTests main.cpp SimpleTimerTests.cpp) 

target_link_libraries(SimpleTimerTests PRIVATE gtest) 

