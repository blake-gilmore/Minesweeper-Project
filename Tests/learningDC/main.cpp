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

    bitmapHandle = CreateDIBSection(virtualDC, &bitmap, DIB_RGB_COLORS, (void**)(&bitPointer), NULL, NULL);
    SelectObject(virtualDC, bitmapHandle);
    BitBlt(virtualDC, 0, 0, maxWidth, maxHeight, windowDC, 0, 0, SRCCOPY);

}

int main()
{
    minesweeperGame game;
    game.initializeGame();
    char selection;
    do
    {
        std::cout << "Please press 's' when you have opened the map: ";
        std::cin >> selection; 
    }while(selection != 's');



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