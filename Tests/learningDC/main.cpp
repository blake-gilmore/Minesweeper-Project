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
    void printColor(POINT*);
    void SearchFor(int, int, int);
    void findSquare();
private:
    //LPCWSTR windowName = L"Microsoft Minesweeper";
    BYTE* bitPointer;
    int ScreenX;
    int ScreenY;
    bool gameWin;
    int TopY;
    int RightX;
    inline int PosB(int, int);
    inline int PosG(int, int);
    inline int PosR(int, int);
    void FindTop();
    void FindRight();
};


void minesweeperGame::SearchFor(int inR, int inG, int inB)
{
    for (int i = 0; i < (ScreenX * ScreenY * 4); i+=4)
    {
        if ((int)bitPointer[i] == inB && (int)bitPointer[i+1] == inG && (int)bitPointer[i+2] == inR)
        {
            i /= 4;
            SetCursorPos((i%ScreenX) ,(i /ScreenX));
            std::cout << "Screenx = " << ScreenX << " ScreenY  = " << ScreenY << std::endl;
            std::cout << "i = " << i << "  X| " <<  i % (ScreenX * 4) << "  Y| " << i / (ScreenX * 4) << std::endl;
            break;
        }
    }
}

void minesweeperGame::findSquare()
{
    //Go to middle of actual map
    //Check a portion of 20 pixels(80 bytes) every Y value increasing by 1 Y value each time
    //Once Y value of first row is found, map out length of square and document
    //Calculate center of square
    //Move left until no more squares
    //Document that location
    //Move right until no more squares
    //Move down until no more squares
    //Save dimensions into a pointer of squares
}


inline int minesweeperGame::PosB(int x, int y)
{
    return bitPointer[4*((y*ScreenX) + x)];
}
inline int minesweeperGame::PosG(int x, int y)
{
    return bitPointer[4*((y*ScreenX) + x) + 1];
}
inline int minesweeperGame::PosR(int x, int y)
{
    return bitPointer[4*((y*ScreenX) + x) + 2];
}
void minesweeperGame::printColor(POINT* p)
{
    int blue = PosB(p->x, p->y);
    int green = PosG(p->x, p->y);
    int red = PosR(p->x, p->y);

    std::cout << "At x: " << p->x << " At y: " << p->y << std::endl;

    std::cout << "Red: " << red << "  Green: " << green << "  Blue: " << blue << std::endl;
    return;
}
minesweeperGame::minesweeperGame()
{
    ScreenX = 0;
    ScreenY = 0;
    bitPointer = 0;
    gameWin = false;
    return;
}
void minesweeperGame::initializeGame()
{/*
    initWindow = FindWindow(NULL, windowName);
    while (initWindow == NULL)
    {
        std::cout << "Please start the game. Window cannot be found.";
        Sleep(1000);
        initWindow = FindWindow(NULL, windowName);
    }
    std::cout << "Window Found!\n";*/
    return;
}
bool minesweeperGame::MapGame()
{   
    //Creates a bitmap for the current desktop window
    SetProcessDPIAware();
    HDC windowDC = GetDC(GetDesktopWindow());
    HDC virtualDC = CreateCompatibleDC(windowDC);
    ScreenX = GetDeviceCaps(windowDC, HORZRES);
    ScreenY = GetDeviceCaps(windowDC, VERTRES);
    HBITMAP bitmapHandle = CreateCompatibleBitmap(windowDC, ScreenX, ScreenY);
    HGDIOBJ hOld = SelectObject(virtualDC, bitmapHandle);
    BitBlt(virtualDC, 0, 0, ScreenX, ScreenY, windowDC, 0, 0, SRCCOPY);    Sleep(2000);
    BITMAPINFOHEADER bitmap = {0};
    bitmap.biSize = sizeof(BITMAPINFOHEADER);
    bitmap.biPlanes = 1;
    bitmap.biBitCount = 32;
    bitmap.biWidth = ScreenX;
    bitmap.biHeight = -ScreenY;
    bitmap.biCompression = BI_RGB;
    bitmap.biSizeImage = 0;

    //bitPointer points to new array of color information
    if (bitPointer)
    free(bitPointer);
    bitPointer =  (BYTE*)malloc(4 * ScreenX * ScreenY);
    GetDIBits(virtualDC, bitmapHandle, 0, ScreenY, bitPointer, (BITMAPINFO*)&bitmap, DIB_RGB_COLORS);
    ReleaseDC(GetDesktopWindow(), windowDC);
    DeleteDC(virtualDC);
    DeleteObject(bitmapHandle);


    //Find TopEnd and document
    FindTop();

    //Find RightStart and document
    FindRight();

    return true;
}     
void minesweeperGame::FindTop()
{
    //Start at bitPointer[0];
    //Add ScreenX * 4 to bitPointer until RGB isn't 255 255 255
    int index(0);
    while(bitPointer[index] > 100)
    {
        index += (ScreenX * 4);
    }
    index /= 4;
    TopY = index / ScreenX;
    return;
}
void minesweeperGame::FindRight()
{
    //start at Y = TopY, and move right pixel by pixel until it finds a Blue value
    //Record X value into RightX
    int index(TopY * ScreenX * 4);
    while(bitPointer[index] < 100)
    {
        index += 4;
    }
    SetCursorPos((index / 4) % ScreenX, (index / 4) / ScreenX);
    Sleep(2000);
    index /= 4;
    RightX = index % ScreenX;
    return;
}
void minesweeperGame::printDimensions()
{
    std::cout << "Width: " << ScreenX;
    std::cout << "Height: " << ScreenY << std::endl;
    return;
}
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
            game.findSquare();
        }
        if (ButtonPress(VK_NUMPAD4))
        {
            game.MapGame();
            game.PointCorner();
        }
    }
    std::cout << "You win!" << std::endl;
    return 0;
}