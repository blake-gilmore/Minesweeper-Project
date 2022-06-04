#ifndef MINESWEEPERGAME_H
#define MINESWEEPERGAME_H
#include "mineSquare.h"
#include <vector>

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
    void setNumMines(int);
    int getNumMines();
    bool isLost();
    void MakeMove(mineSquare&);
    int getGameRows();
    int getGameColumns();
    void findPossibilities(mineSquare&);
    void flagPossibilities(mineSquare&);
    void testCases(mineSquare&);
    mineSquare** mapSquares;
    void findSquareValue(mineSquare&);
    void flagSquare(mineSquare&);
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
    int bytesBetweenSquares;
    inline int PosB(int, int);
    inline int PosG(int, int);
    inline int PosR(int, int);
    void FindTop();
    void FindRight();
    int pixelsToBytesX(int);
    int pixelsToBytesY(int);
    int bytesToPixelsX(int);
    int bytesToPixelsY(int);
    int findCenterX(int);
    int findCenterY(int);
    int getXYByte(int x, int y);
    bool isWhite(int);
    void moveDownNumber(int&, bool&);
    void clickEmpties(mineSquare&);
    void clickSquare(mineSquare&);

    //std::vector<std::vector<>> coordsOfClicks;
};
#endif