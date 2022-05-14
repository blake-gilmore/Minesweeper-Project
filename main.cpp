#include <Windows.h>
#include <iostream>
#include <winuser.h>
#include <chrono>
#include <thread>

int main()
{
    tagMOUSEINPUT myInput;
    
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(10s);
    std::this_thread::sleep_until(std::chrono::system_clock::now() + 1s);
    
    std::cout << "Hello Tiffanie.\n";
    return 0;
}