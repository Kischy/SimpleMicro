#include "EventTestsHelper.h"


#include <chrono>
#include <thread>

namespace test_helper
{
    unsigned long timeMilliSeconds() 
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        return static_cast<unsigned long>(value.count());
    }


}
