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
    void printDimensions();
    HWND initWindow;
private:
    LPCWSTR windowName = L"Microsoft Minesweeper";
    BYTE bitPointer;
        HDC windowDC;
    HDC virtualDC;
    int maxWidth;
    int maxHeight;
    RECT rect;
    bool gameWin;
    BITMAPINFO bitmap;
    HBITMAP bitmapHandle;
};


minesweeperGame::minesweeperGame()
{
    windowDC == NULL;
    maxWidth = 0;
    maxHeight = 0;
    gameWin = false;
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
    if (windowDC != NULL)
    {
        ReleaseDC(initWindow, windowDC);
        ReleaseDC(initWindow, virtualDC);
    }

    windowDC = GetDC(initWindow);
    virtualDC = CreateCompatibleDC(windowDC);
    GetWindowRect(initWindow, &rect);
    maxWidth = rect.right;
    maxHeight = rect.bottom;

    bitmap.bmiHeader.biSize = sizeof(bitmap.bmiHeader);
    bitmap.bmiHeader.biWidth = maxWidth;
    bitmap.bmiHeader.biHeight = maxHeight;
    bitmap.bmiHeader.biPlanes = 1;
    bitmap.bmiHeader.biBitCount = 32;
    bitmap.bmiHeader.biCompression = BI_RGB;
    bitmap.bmiHeader.biSizeImage = maxWidth * 4 * maxHeight;
    bitmap.bmiHeader.biClrUsed = 0;
    bitmap.bmiHeader.biClrImportant = 0;

    bitmapHandle = CreateDIBSection(virtualDC, &bitmap, DIB_RGB_COLORS, (void**)(&bitPointer), NULL, 0);
    SelectObject(virtualDC, bitmapHandle);
    BitBlt(virtualDC, 0, 0, maxWidth, maxHeight, windowDC, 0, 0, SRCCOPY);
    return true;
}

void minesweeperGame::printDimensions()
{
    std::cout << "Width: " << maxWidth;
    std::cout << "Height: " << maxHeight << std::endl;
    return;
}

int main()
{
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    minesweeperGame game;
    game.initializeGame();
    game.MapGame();
    char selection;
    Sleep(5000);
    ShowWindow(game.initWindow, SW_SHOWMAXIMIZED);

    POINT p;
    p.x = 0; 
    p.y = 0;
    ClientToScreen(game.initWindow, &p);
    std::cout << "X| " << p.x << " Y| " << p.y << std::endl;
    return 0;
}