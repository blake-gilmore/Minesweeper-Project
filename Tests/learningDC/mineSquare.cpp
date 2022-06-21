#include "mineSquare.h"
#include <iostream>
#include <windows.h>
mineSquare::mineSquare()
{
    topLeft = top = topRight = left = right = bottomLeft = bottom = bottomRight = nullptr;
    value = 'e';
    possibilities = 0;
    flagsNear = 0;
    clicked = false;
    adjacents = new mineSquare*[8];
    adjacents[0] = topLeft;
    adjacents[1] = top;
    adjacents[2] = topRight;
    adjacents[3] = left;
    adjacents[4] = right;
    adjacents[5] = bottomLeft;
    adjacents[6] = bottom;
    adjacents[7] = bottomRight;
    
    return;
}
void mineSquare::printSquare()
{
    std::cout << "Value: " << value << std::endl;
    std::cout << "Possibilities: " << possibilities << std::endl;
    std::cout << "Flags Near: " << flagsNear << std::endl;
    
}
void mineSquare::setClicked(bool clickIn)
{
    clicked = clickIn;
    return;
}   
int mineSquare::getPossibilities()
{
    return possibilities;
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
    return;
}
void mineSquare::setYCoord(int yIn)
{
    yCoord = yIn;
    return;
}
void mineSquare::setValue(char valueIn)
{
    value = valueIn;
    return;
}
int mineSquare::getXCoord()
{
    return xCoord;
}
int mineSquare::getYCoord()
{
    return yCoord;
}

char mineSquare::getValue()
{
    return value;
}

mineSquare* mineSquare::getTopLeft()
{
    return topLeft;
}
mineSquare* mineSquare::getTop()
{
    return top;
}
mineSquare* mineSquare::getTopRight()
{
    return topRight;
}
mineSquare*mineSquare:: getLeft()
{
    return left;
}
mineSquare* mineSquare::getRight()
{
    return right;
}
mineSquare*mineSquare:: getBottomLeft()
{
    return bottomLeft;
}
mineSquare* mineSquare::getBottom()
{
    return bottom;
}
mineSquare* mineSquare::getBottomRight()
{
    return bottomRight;
}
