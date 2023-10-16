#ifndef MINESQUARE_H
#define MINESQUARE_H
#include <windows.h>
class mineSquare
{
public:

    mineSquare();
    void printSquare();
    void setTopLeft(mineSquare*);
    void setTop(mineSquare*);
    void setTopRight( mineSquare*);
    void setLeft( mineSquare*);
    void setRight( mineSquare*);
    void setBottomLeft( mineSquare*);
    void setBottom( mineSquare*);
    void setBottomRight( mineSquare*);
    void setXCoord(int);
    void setYCoord(int);
    int getXCoord();
    int getYCoord();
    char getValue();
    void setValue(char);
    void setClicked(bool);
    bool getClicked() {return clicked;};
    mineSquare* getTopLeft();
    mineSquare* getTop();
    mineSquare* getTopRight( );
    mineSquare* getLeft( );
    mineSquare* getRight( );
    mineSquare* getBottomLeft( );
    mineSquare* getBottom( );
    mineSquare* getBottomRight( );
    int getPossibilities();
    int possibilities;
    int flagsNear;
    int column;
    int row;
    mineSquare*** adjacents;
    bool readyToFlag();
private:
    int xCoord;
    int yCoord;
    char value;
    bool clicked;
    
    mineSquare* topLeft;
    mineSquare* top;
    mineSquare* left;
    mineSquare* topRight;
    mineSquare* right;
    mineSquare* bottomLeft;
    mineSquare* bottom;
    mineSquare* bottomRight;
    
};
#endif