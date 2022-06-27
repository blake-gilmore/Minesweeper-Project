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

    input[0].mi.time = 0;
    input[1].mi.time = 0;

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
    std::cout << "Enter number of mines for your game: ";
            int num;
            std::cin >> num; 
            game.setNumMines(num);
    while (true)
    {
        if (ButtonPress(VK_NUMPAD3))
        {
            game.MapGame();
            game.initMap();
            //Make Random move and get position
            tempNum = rand() % game.getGameRows();
            tempNum2 = rand() % game.getGameColumns();
            
            SetCursorPos(game.mapSquares[tempNum][tempNum2].getXCoord(), game.mapSquares[tempNum][tempNum2].getYCoord());
            Sleep(50);
            leftClick();
            Sleep(1000);
            int dummyValue;
            /*while(true)
            {
                std::cout << "Enter row: ";
                std::cin >> tempNum;
                std::cout << "Enter column: ";
                std::cin >> tempNum2;
                game.MapGame();
                game.findSquareValue(game.mapSquares[tempNum][tempNum2]);
                std::cout << "Value in square is: ";
                std::cout << game.mapSquares[tempNum][tempNum2].getValue() << std::endl;
                game.mapSquares[tempNum][tempNum2].printSquare();
            }
*/
            while(game.getNumMines() > 0)   
            {  /*
                Sleep(3000);
                
                game.MapGame();
                std::cout << "Enter row: ";
                std::cin >> tempNum;
                std::cout << "Enter column: ";
                std::cin >> tempNum2;
                Sleep(3000);
                game.findSquareValue(game.mapSquares[tempNum][tempNum2]);
                std::cout << "Value in square is: ";
                std::cout << game.mapSquares[tempNum][tempNum2].getValue() << std::endl;
                */
                //std::cout << "Enter number of mines for your game: ";
                //int num;
                //std::cin >> num; 
                //game.setNumMines(num);
                //Sleep(4000);
                game.MapGame();
                //make initial move
                game.MakeMove(game.mapSquares[tempNum][tempNum2]);
                char input;
                
                do 
                {
                    //Clear clicks made from last set of moves
                    
                    do 
                    {
                        std::cout << "y/n to check values";
                        std::cin >> input;
                        if (input == 'y')
                        {
                            std::cout << "Enter row: ";
                            std::cin >> tempNum;
                            std::cout << "Enter column: ";
                            std::cin >> tempNum2;
                            //Sleep(3000);
                            game.findSquareValue(game.mapSquares[tempNum][tempNum2]);
                            std::cout << "Value in square is: ";
                            std::cout << game.mapSquares[tempNum][tempNum2].getValue() << std::endl;
                            game.mapSquares[tempNum][tempNum2].printSquare();
                        }
                    }
                    while(input == 'y');
                    SetCursorPos(0,0);
                    Sleep(50);
                    game.MapGame();
                    game.clearClicks();
                    do 
                    {
                        std::cout << "y/n to check values";
                        std::cin >> input;
                        if (input == 'y')
                        {
                            std::cout << "Enter row: ";
                            std::cin >> tempNum;
                            std::cout << "Enter column: ";
                            std::cin >> tempNum2;
                            //Sleep(3000);
                            game.findSquareValue(game.mapSquares[tempNum][tempNum2]);
                            std::cout << "Value in square is: ";
                            std::cout << game.mapSquares[tempNum][tempNum2].getValue() << std::endl;
                            game.mapSquares[tempNum][tempNum2].printSquare();
                        }
                    }
                    while(input == 'y');

                } while (game.getNumMines() > 0);
            }
        }
        if (game.getNumMines() == 0)
            break;
    }
    std::cout << "You win!" << std::endl;
    return 0;
}   