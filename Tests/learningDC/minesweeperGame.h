#ifndef MINESWEEPERGAME_H
#define MINESWEEPERGAME_H
#include "mineSquare.h"
class minesweeperGame
{
public:
    minesweeperGame();
    void initializeGame();
    bool MapGame();
    void printDimensions();
    void printColor(POINT*);
    void SearchFor(int, int, int);
    void initMap();
private:
    //LPCWSTR windowName = L"Microsoft Minesweeper";
    int numMines;
    BYTE* bitPointer;
    int ScreenX;
    int ScreenY;
    bool gameWin;
    int TopY;
    int RightX;
    int leftCorner;
    int gameRows;
    int gameColumns;
    int pixelsBetweenSquares;
    inline int PosB(int, int);
    inline int PosG(int, int);
    inline int PosR(int, int);
    void FindTop();
    void FindRight();
    mineSquare** mapSquares;
    int pixelsToBytesX(int);
    int pixelsToBytesY(int);
    int bytesToPixelsX(int);
    int bytesToPixelsY(int);
};
#endif