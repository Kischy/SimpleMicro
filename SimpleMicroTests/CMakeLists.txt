cmake_minimum_required(VERSION 3.19)

project(SimpleMicroTests) 

add_subdirectory(googletest) 
include_directories(googletest/include)
include_directories(googlemock/include)

add_executable(SimpleMicroTests main.cpp TimerTests.cpp ../Timer.cpp LListTests.cpp) 

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  target_compile_options(SimpleMicroTests PRIVATE -std=c++11 -Wall -Wextra -Wpedantic -Werror)# --coverage)
  #target_link_options (SimpleMicroTests PRIVATE --coverage)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  target_compile_options(SimpleMicroTests PRIVATE /W3 /WX)
endif()

target_link_libraries(SimpleMicroTests PRIVATE gtest) 

