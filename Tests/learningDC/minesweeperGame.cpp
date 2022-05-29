#include <windows.h>
#include <iostream>
#include "minesweeperGame.h"

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

void minesweeperGame::initMap()
{
    //Go to middle of actual map
    /*
    1. Find difference between 0 and (RightX*4)
    2. Divide the difference by 2
    3. if (difference / 2) is not divisible by 4
        a. add 1 until it is
    4. Subtract 20 from (difference/2) and set as leftLim
    5. loop
        a. add one whole Y value of bytes to the leftmost value
        b. check all bytes between leftmost value and (leftLim + 40) for a
           blue value above 100
        c. If found, mark as TopOfSquares and exit loop
    6. Loop
        a. Add one Y value of bytes to topOfSquares
        b. if B of currentPixel drops below 100, mark as BottomOfFirstSquare and exit loop
    7. Find difference between TopOfSquares and BottomOfFirstSquare and set as MiddleOfFirstSquare
    8. Go to middleOfFirstSquare
    9. Loop
        a. Subtract 4 bytes
        b. If blue value drops below 100, mark as LeftOfFirstSquare and exit
    10. Loop
        a. Add 4 bytes
        b. If blue value drops below 100, mark as RightOfFirstSquare and exit
    11. Move to midpoint between Left and MiddleOfFirstSquare
    12.Loop
        a. Subtract Y value 
        b. If blue value drops below 100, reinitialize as topOfFirstSquare
    13. Loop
        a. Add Y value
        b. If blue value drops below 100, reinitialize as BottomOfFirstSquare
    14. Go to midpoint between Top,Bottom, Left, and Right
    15. Reinitialize as MiddleOfFirstSquare
    16. Loop
        a. jump (rightOfFirstSquare - LeftOfFirstSquare) pixels to the left
        b. If blue value drops below 100, mark coord of top left square as LeftCorner
    17. Set Counter to 1 and jump one square to the right
    18. Loop
        a. if blue value drops below 100, exit loop
        b. counter++
        c. jump one square to the right
    19. Set counter as gameColumns
    20. Jump back one square, reset counter, and jump one square down
    21. Loop
        a. If blue value drops below 100, exit loop
        b. counter++
        c. Jump one square down
    22. Set counter as gameRows
    23. Initialize mapSquares pointer with gameRows rows and gameColumns columns
    24. set indexes row and column to [0][0]
    25. Loop 
        a. Set xCoord and yCoord of mineSquare at [row][column]
        b. Set all pointers of current mineSquare to appropriate addresses of mapSquares
            i. Check every pointer if the nextSquare is out of the row and column of mapSquares, if it is, assign NULL instead
    */

   //Find difference between 0 and (RightX*4) and make divisible by 4
    int centerDifference = (RightX * 4)/2;
    while ((centerDifference % 4) != 0)
        centerDifference--;

    //Set centerDifference as leftmost value for map checking
    centerDifference -= 20;
    centerDifference += (TopY * ScreenX * 4);
    int topOfFirstSquare = 0;

    //Find top of the first square
    do
    {
        centerDifference += (ScreenX * 4);
        for (int index = centerDifference; index < (centerDifference + 40); index += 4)
        {
            if (bitPointer[index] >= 100)
            {
                topOfFirstSquare = index;
                break;
            }
        }
    }while(topOfFirstSquare == 0);
    
    SetCursorPos(bytesToPixelsX(topOfFirstSquare), bytesToPixelsY(topOfFirstSquare));
    Sleep(5000);

    //Find bottom of the first square
    int BottomOfFirstSquare = topOfFirstSquare;
    do
    {
        BottomOfFirstSquare += (ScreenX * 4);
    } while (bitPointer[BottomOfFirstSquare] >= 100);

    SetCursorPos(bytesToPixelsX(BottomOfFirstSquare), bytesToPixelsY(BottomOfFirstSquare));
    Sleep(5000);

    int middleOfFirstSquare = topOfFirstSquare + ((BottomOfFirstSquare - topOfFirstSquare) / 2);
    while ((middleOfFirstSquare % 4) != 0)
        middleOfFirstSquare--;

    //Find Left of first Square
    int mark = middleOfFirstSquare;
    SetCursorPos(bytesToPixelsX(middleOfFirstSquare), bytesToPixelsY(middleOfFirstSquare));
    Sleep(5000);
    do
    {
        mark -= 4;
    } while (bitPointer[mark] >= 100);
    int leftOfFirstSquare = mark;

    SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
    Sleep(5000);
    
    //Find Right of First Square
    do
    {
        mark += 4;
    }while(bitPointer[mark] >= 100);
    int rightOfFirstSquare = mark;

    SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
    Sleep(5000);

    //Refind top of square
    mark =rightOfFirstSquare + ((rightOfFirstSquare - leftOfFirstSquare)/2);
    while ((mark % 4) != 0)
        mark--;
    do
    {
        mark -= (ScreenX * 4);
    }while(bitPointer[mark] >= 100);
    topOfFirstSquare = mark;

    SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
    Sleep(5000);

    //Refind bottom of first square
    do
    {
        mark += (ScreenX * 4);
    } while (bitPointer[mark] >= 100);
    BottomOfFirstSquare = mark;

    SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
    Sleep(5000);

    int yMark = topOfFirstSquare + ((BottomOfFirstSquare - topOfFirstSquare) / 2);
    while ((yMark % 4) != 0)
        middleOfFirstSquare--;
    yMark /= 4;
    yMark /= ScreenX;

    int xMark =rightOfFirstSquare + ((rightOfFirstSquare - leftOfFirstSquare)/2);
    while ((xMark % 4) != 0)
        xMark--;
    xMark /= 4;
    xMark %= ScreenX;

    mark = (yMark * 4) + (xMark * 4);

    SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
    Sleep(5000);

    middleOfFirstSquare = mark;
    do
    {
        middleOfFirstSquare -= (rightOfFirstSquare - leftOfFirstSquare);
    } while (bitPointer[middleOfFirstSquare] >= 100);
    middleOfFirstSquare += (rightOfFirstSquare - leftOfFirstSquare);
    
    leftCorner = middleOfFirstSquare;

    //Count squares in entire map
    int counter(0);
    mark = leftCorner;
    int amountToJumpSide = (rightOfFirstSquare - leftOfFirstSquare);
    do
    {   counter++;
        mark += amountToJumpSide;

        SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
        Sleep(5000);
    } while (bitPointer[mark] >= 100);
    
    mark -= amountToJumpSide;

    gameColumns = counter;
    counter = 0;

    int amountToJumpUp = BottomOfFirstSquare - topOfFirstSquare;
    do
    {
        counter++;
        mark += amountToJumpUp;
        SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
        Sleep(5000);
    } while (bitPointer[mark] >= 100);
    mark -= amountToJumpUp;
    gameRows = counter;

    //Initialize mineSquare pointer
    mapSquares = new mineSquare*[gameRows];
    for (int i = 0; i < gameRows; i++)
    {
        mapSquares[i] = new mineSquare[gameColumns];
    }
    mineSquare* minePtr;
    pixelsBetweenSquares = ((rightOfFirstSquare - leftOfFirstSquare) / 4);
    mark  = leftCorner;
    for (int row = 0; row < gameRows; row++)
    {
        mark = leftCorner;
        mark += (pixelsToBytesY(pixelsBetweenSquares) * row);
        for (int column = 0; column < gameColumns; column++)
        {
            //Determine placement in array and assign NULL if on edges, and the addresses of
            //near squares otherwise
            if (row == 0)
            {
                mapSquares[row][column].setTopLeft(nullptr);
                mapSquares[row][column].setTop(nullptr);
                mapSquares[row][column].setTopRight(nullptr);
            }
            else
            {
                minePtr = &mapSquares[row-1][column];
                mapSquares[row][column].setTop(minePtr);
            }

            if (column == 0)
            {
                mapSquares[row][column].setTopLeft(nullptr);
                mapSquares[row][column].setLeft(nullptr);
                mapSquares[row][column].setBottomLeft(nullptr);
            }
            else
            {
                minePtr = &mapSquares[row][column-1];
                mapSquares[row][column].setLeft(minePtr);
            }

            if (row == (gameRows-1))
            {
                mapSquares[row][column].setBottom(nullptr);
                mapSquares[row][column].setBottomRight(nullptr);
                mapSquares[row][column].setBottomLeft(nullptr);
            }
            else
            {
                minePtr = &mapSquares[row+1][column];
                mapSquares[row][column].setBottom(minePtr);
            }

            if (column == (gameColumns - 1))
            {
                mapSquares[row][column].setTopRight(nullptr);
                mapSquares[row][column].setRight(nullptr);
                mapSquares[row][column].setBottomRight(nullptr);
            }
            else
            {
                minePtr = &mapSquares[row][column+1];
                mapSquares[row][column].setRight(minePtr);
            }

            if (row != 0 && column != 0)
            {
                minePtr = &mapSquares[row-1][column-1];
                mapSquares[row][column].setTopLeft(minePtr);
            }

            if (row != 0 && column != (gameColumns-1))
            {
                minePtr = &mapSquares[row-1][column+1];
                mapSquares[row][column].setTopRight(minePtr);
            }

            if (row != (gameRows - 1) && column != 0)
            {
                minePtr = &mapSquares[row+1][column-1];
                mapSquares[row][column].setBottomLeft(minePtr);
            }

            if (row != (gameRows - 1) && column != (gameColumns - 1))
            {
                minePtr = &mapSquares[row+1][column+1];
                mapSquares[row][column].setBottomRight(minePtr);
            }

            //Set xCoord and yCoords of current mark
            mapSquares[row][column].setXCoord(bytesToPixelsX(mark));
            mapSquares[row][column].setYCoord(bytesToPixelsY(mark));

            mark += pixelsToBytesX(pixelsBetweenSquares);
        }

        
    }

    
    


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


int minesweeperGame::pixelsToBytesX(int pixelsIn)
{
    return (pixelsIn * 4);
}
int minesweeperGame::pixelsToBytesY(int pixelsIn)
{
    return (pixelsIn * (ScreenX * 4));
}
int minesweeperGame::bytesToPixelsX(int bytesIn)
{
    return (bytesIn % (ScreenX * 4));
}
int minesweeperGame::bytesToPixelsY(int bytesIn)
{
    return (bytesIn / (ScreenX * 4));
}