#ifndef MINESQUARE_H
#define MINESQUARE_H
#include <windows.h>
class mineSquare
{
public:

    mineSquare();
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
private:
    int xCoord;
    int yCoord;
    char value;
    mineSquare* topLeft;
    mineSquare* top;
    mineSquare* topRight;
    mineSquare* left;
    mineSquare* right;
    mineSquare* bottomLeft;
    mineSquare* bottom;
    mineSquare* bottomRight;
};
#endif