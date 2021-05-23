cmake_minimum_required(VERSION 3.19)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

if(WIN32) 
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

project(SimpleMicroTests) 

include_directories(../src)


add_executable(
  SimpleMicroTests 
../src/Event/Timer.cpp 
../src/Event/ButtonEvent.cpp 
 ./EventTests/TimerTests.cpp 
 ./EventTests/EventTestsHelper.cpp 
 ./EventTests/ButtonEventTests.cpp  
 ./EventTests/EventListenerTests.cpp 
 ./ListTests/LListTests.cpp 
 ./ListTests/LListBaseCommonTests.cpp 
 ./ListTests/StaticLListTests.cpp) 

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  target_compile_options(SimpleMicroTests PRIVATE -std=c++11 -Wall -Wextra -Wpedantic -Werror)# --coverage)
  #target_link_options (SimpleMicroTests PRIVATE --coverage)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  target_compile_options(SimpleMicroTests PRIVATE /W3 /WX)
endif()

target_link_libraries(SimpleMicroTests PRIVATE gtest_main)

