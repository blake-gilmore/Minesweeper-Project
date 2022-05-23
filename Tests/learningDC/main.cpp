#define UNICODE
#include <windows.h>
#include <Gdiplus.h>
#include <iostream>
class minesweeperGame
{
public:
    minesweeperGame();
    void initializeGame();
    bool MapGame();
private:
    LPCWSTR windowName = L"Microsoft Minesweeper";
    BYTE bitPointer;
    HWND initWindow;
    HDC windowDC;
    HDC virtualDC;
    int maxWidth;
    int maxHeight;
    RECT rect;
};
minesweeperGame::minesweeperGame()
{
    maxWidth = 0;
    maxHeight = 0;
    return;
}
void minesweeperGame::initializeGame()
{
    initWindow = FindWindow(NULL, windowName);
    while (initWindow == NULL)
    {
        std::cout << "Please start the game. Window cannot be found.";
        Sleep(1000);
        initWindow = FindWindow(NULL, windowName);
    }
    std::cout << "Window Found!\n";
    return;
}
bool minesweeperGame::MapGame()
{
    windowDC = GetDC(initWindow);
    virtualDC = CreateCompatibleDC(windowDC);
    
}

int main()
{
    minesweeperGame game;
    game.initializeGame();



    BYTE* bitPointer;
    RECT rect;
    LPCWSTR windowName = L"Microsoft Minesweeper";
    HWND hWND = FindWindow(NULL, windowName);
    //Get the window. Got it.
    HDC windowDC = GetDC(hWND);
    HDC virtualDC = CreateCompatibleDC(windowDC);
    int width = GetDeviceCaps(windowDC, HORZRES);
    int height = GetDeviceCaps(windowDC, VERTRES);

    HBITMAP mainBitmap = CreateCompatibleBitmap(windowDC, width, height);
    HGDIOBJ newDC = SelectObject(virtualDC, mainBitmap);
    
    ReleaseDC()
    return 0;
}