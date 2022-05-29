#define UNICODE
#include <windows.h>
#include <Gdiplus.h>
#include <iostream>
#include "minesweeperGame.h"
#include "mineSquare.h"


bool ButtonPress(int Key)
{
    bool button_pressed = false;

    while (GetAsyncKeyState(Key))
        button_pressed = true;

    return button_pressed;
}
int main()
{
    minesweeperGame game;
    POINT p;
    //SShowWindow(game.initWindow, SW_SHOWMAXIMIZED);
            //game.initializeGame();

    while (true)
    {
        if (ButtonPress(VK_NUMPAD0))
        {
            game.MapGame();
            GetCursorPos(&p);
            game.printColor(&p);
            Sleep(50);
        }
        if (ButtonPress(VK_NUMPAD1))
        {
            game.MapGame();
            game.SearchFor(28, 187, 222);
        }
        if (ButtonPress(VK_NUMPAD2))
        {
            game.MapGame();
            game.SearchFor(118, 154, 33);
        }
        if (ButtonPress(VK_NUMPAD3))
        {
            game.MapGame();
            game.initMap();
        }
    }
    std::cout << "You win!" << std::endl;
    return 0;
}