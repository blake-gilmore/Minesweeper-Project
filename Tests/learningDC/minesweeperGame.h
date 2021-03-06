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
    void updateFlags(mineSquare&);
    void updatePossibilities(mineSquare&);
    bool isRed(int);
    int bytesBetweenSquares;
    int squareHeight;
    void clearClicks();
    void moveToRightEdge(mineSquare&, int&);
    void simulate(mineSquare&);
    bool findAdjacentSquare(mineSquare**, int);
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
    bool isBlue(int);
    void clickEmpties(mineSquare&);
    void clickSquare(mineSquare&);
    char getColor(int);
    void checkBlue(mineSquare&, int);
    void checkRed(mineSquare&, int);
    void checkGreen(mineSquare&, int);
    void moveBottomEdge(mineSquare&, int&);
    void moveTopEdge(mineSquare&, int&);
    bool isWhiteLineAbove(int byteValue, mineSquare& mineIn);
    bool isWhiteLine(int byteValue, mineSquare& mineIn);
    bool needToUpdateSurrounding(mineSquare&);

    std::vector<mineSquare*> coordsOfClicks;
};
#endif