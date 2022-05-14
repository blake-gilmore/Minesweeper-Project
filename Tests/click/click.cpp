#include <windows.h>
#include <iostream>
void leftClick()
{
    INPUT input[4];
    //left down
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    //left up
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
     //left down
    input[2].type = INPUT_MOUSE;
    input[2].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    //left up
    input[3].type = INPUT_MOUSE;
    input[3].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    UINT usent = SendInput(3, input, sizeof(INPUT));
}
void printSelection()
{
    std::cout << "Select any number to have the computer click. Otherwise, select '9'.";

}

int main()
{
    int selection;
    printSelection();
    std::cin >> selection;
    while(selection != 9)
    {
        Sleep(5000);
        leftClick();
        printSelection();
        std::cin >> selection;
    }

    return 0;
}