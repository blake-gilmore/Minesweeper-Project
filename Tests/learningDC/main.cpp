#define UNICODE
#include <windows.h>
#include <Gdiplus.h>
#include <iostream>
#include "minesweeperGame.h"
#include "mineSquare.h"
#include <stdlib.h>


bool ButtonPress(int Key)
{
    bool button_pressed = false;

    while (GetAsyncKeyState(Key))
        button_pressed = true;

    return button_pressed;
}
void leftClick()
{
    INPUT input[2];
    //left down
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    //left up
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    UINT usent = SendInput(2, input, sizeof(INPUT));
    return;

}
int main()
{
    
    minesweeperGame game;
    POINT p;
    int tempNum, tempNum2;
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
            //std::cout << "Enter the number of mines on this map: ";
            //std::cin >> tempNum;
            Sleep(2000);
            game.setNumMines(tempNum);
            game.MapGame();
            game.initMap();
            //Make Random move and get position
            tempNum = rand() % game.getGameRows();
            tempNum2 = rand() % game.getGameColumns();
            
            SetCursorPos(game.mapSquares[0][1].getXCoord(), game.mapSquares[0][1].getYCoord());
            Sleep(50);
            leftClick();
            Sleep(500);
            game.MapGame();
         while(true)   
         {  
             Sleep(3000);
            std::cout << "Enter row: ";
            std::cin >> tempNum;
            std::cout << "Enter column: ";
            std::cin >> tempNum2;
            Sleep(3000);
            game.findSquareValue(game.mapSquares[tempNum][tempNum2]);
            std::cout << "Value in square is: ";
            std::cout << game.mapSquares[tempNum][tempNum2].getValue() << std::endl;
        }

            do
            {
                game.MapGame();
                game.MakeMove(tempNum, tempNum2);
            }while(game.getNumMines() > 0);

        }
    }
    std::cout << "You win!" << std::endl;
    return 0;
}