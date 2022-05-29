#include "mineSquare.h"
mineSquare::mineSquare()
{
    topLeft = top = topRight = left = right = bottomLeft = bottom = bottomRight = nullptr;
}
void mineSquare::setTopLeft(mineSquare* ptrIn)
{
    topLeft = ptrIn;
    return;
}
void mineSquare::setTop( mineSquare* ptrIn)
{
    top = ptrIn;
    return;
}
void mineSquare::setTopRight( mineSquare* ptrIn)
{
    topRight = ptrIn;
    return;
}
void mineSquare::setLeft( mineSquare* ptrIn)
{
    left = ptrIn;
    return;
}
void mineSquare::setRight( mineSquare* ptrIn)
{
    right = ptrIn;
    return;
}
void mineSquare::setBottomLeft( mineSquare* ptrIn)
{
    bottomLeft = ptrIn;
    return;
}
void mineSquare::setBottom( mineSquare* ptrIn)
{
    bottom = ptrIn;
    return;
}
void mineSquare::setBottomRight( mineSquare* ptrIn)
{
    bottomRight = ptrIn;
    return;
}

void mineSquare::setXCoord(int xIn)
{
    xCoord = xIn;
}
void mineSquare::setYCoord(int yIn)
{
    yCoord = yIn;
}