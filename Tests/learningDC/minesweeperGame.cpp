#include <windows.h>
#include <iostream>
#include "minesweeperGame.h"
#include <cmath>
void minesweeperGame::setNumMines(int numIn)
{
    numMines = numIn;
}
int minesweeperGame::getNumMines()
{
    return numMines;
}
int minesweeperGame::getGameRows()
{
    return gameRows;
}
int minesweeperGame::getGameColumns()
{
    return gameColumns;
}
bool isLost()
{
    return false;
}
void minesweeperGame::MakeMove(mineSquare& mineIn)
{
    mineSquare* minePtr;
    int numEmptyNear;
    //Recursive function that sends the location of a recently identified square that has changed its value
    //Has just been recently mapped, so start at current

    //Find new value of current square
    findSquareValue(mineIn);
    if (mineIn.getValue() == 'e')
        return;

    //Check top left to see if new value
    //If new value, call MakeMove(xCoord, yCoord);
    minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        MakeMove(*minePtr);

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        MakeMove(*minePtr);

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        MakeMove(*minePtr);

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        MakeMove(*minePtr);

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        MakeMove(*minePtr);

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        MakeMove(*minePtr);

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        MakeMove(*minePtr);

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        MakeMove(*minePtr);
    
    //No more new squares around
    if (mineIn.getValue() != 'w')
    {
        findPossibilities(mineIn);  

        testCases(mineIn);
    }
    return;
}
void minesweeperGame::testCases(mineSquare& mineIn)
{
    return;
}
void minesweeperGame::flagPossibilities(mineSquare& mineIn)
{

    //Checks each square around minIn
    //If the square checked is an 'e' square and not NULL
    //flags the square
    mineSquare* minePtr;
    minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        flagSquare(*minePtr);

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        flagSquare(*minePtr);

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        flagSquare(*minePtr);

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        flagSquare(*minePtr);

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        flagSquare(*minePtr);

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        flagSquare(*minePtr);

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        flagSquare(*minePtr);

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        flagSquare(*minePtr);
}
void RightClick()
{
    //Right clicks for the user at the current mouse position

    INPUT input[2];
    //left down
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    //left up
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    input[0].mi.time = 0;
    input[1].mi.time = 0;

    UINT usent = SendInput(2, input, sizeof(INPUT));
    Sleep(300);
    return;
}
void minesweeperGame::updatePossibilities(mineSquare& mineIn)
{
    mineSquare* minePtr;/*
    mineSquare** newMinePtr = mineIn.adjacents;
    for (int i = 0; i < 8; i++)
    {
        minePtr = newMinePtr[i];
        if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
        {
            if (minePtr->possibilities > 0)
                    minePtr->possibilities--;
        }
    }*/


        minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }
    return;
}
void minesweeperGame::updateFlags(mineSquare& mineIn)
{
    mineSquare* minePtr;
        minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
                minePtr->possibilities--;
    }
    return;
}

void minesweeperGame::flagSquare(mineSquare& mineIn)
{
    //Sets the value of current mineIn square to 'f'
    //sets cursor position to mineIn and right clicks
    //Checks all surrounding squares
    //  Adds one to each squares flagsNear variable
    //  If surrounding square has had its possibilities checked before, then decrease possibility by one
    //  If the new flag/possibilities values allow the surrounding square to click or flag, it does so
    //  by calling clickEmpties or flagPossibilities

    mineSquare* minePtr;
    if (mineIn.getValue() == 'f')
        return;
    mineIn.setValue('f');
    SetCursorPos(mineIn.getXCoord(),mineIn.getYCoord());
    RightClick();
    numMines--;
    
    updateFlags(mineIn);
    //Update possibilities of all surrounnding mines

    minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
        {
            if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
                clickEmpties(*minePtr);
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)) && minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }
    }

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
        {
            if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
                clickEmpties(*minePtr);
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)) && minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
        {
            if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
                clickEmpties(*minePtr);
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)) && minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
        {
            if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
                clickEmpties(*minePtr);
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)) && minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
        {
            if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
                clickEmpties(*minePtr);
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)) && minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
        {
            if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
                clickEmpties(*minePtr);
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)) && minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
        {
            if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
                clickEmpties(*minePtr);
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)) && minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        if (minePtr->possibilities > 0)
        {
            if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
                clickEmpties(*minePtr);
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)) && minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }
}
void minesweeperGame::findPossibilities(mineSquare& mineIn)
{
    //Only initialized once. If already initialized, return
    //Checks each surrounding square for an 'e' value. If so, increments mineIn possibilities
    if (mineIn.possibilities != 0)
        return;
    
    mineSquare* minePtr;
    minePtr = mineIn.getTopLeft();
     if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        mineIn.possibilities++;

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        mineIn.possibilities++;
    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        mineIn.possibilities++;

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        mineIn.possibilities++;

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        mineIn.possibilities++;

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        mineIn.possibilities++;

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        mineIn.possibilities++;

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        mineIn.possibilities++;

    if ((mineIn.getPossibilities() + mineIn.flagsNear) == (mineIn.getValue() - '0'))
            flagPossibilities(mineIn);  

    if (mineIn.flagsNear == (mineIn.getValue() - '0') && mineIn.getPossibilities() != 0)
        clickEmpties(mineIn);

    //Check for new cases. Are possibilities of adjacent squares exclusively in this squares space?
    


    return;
}
void minesweeperGame::clickEmpties(mineSquare& mineIn)
{
    //Checks each surrounding square of mineIn, if not already clicked and value is 'e', click that square
    mineSquare* minePtr;
    minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        clickSquare(*minePtr);

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        clickSquare(*minePtr);

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        clickSquare(*minePtr);

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        clickSquare(*minePtr);

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        clickSquare(*minePtr);

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        clickSquare(*minePtr);

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        clickSquare(*minePtr);

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
        clickSquare(*minePtr);
    return;
}
void LeftClick()
{
    INPUT input[2];
    //left down
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    //left up
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    input[0].mi.time = 0;
    input[1].mi.time = 0;

    UINT usent = SendInput(2, input, sizeof(INPUT));
    Sleep(300);
    return;

}
void minesweeperGame::clickSquare(mineSquare& mineIn)
{
    //Moves cursor to mineIn and left clicks
    //For each surrounding square
    //  decrease possibilites if initialized already

    mineSquare* minePtr;
    mineIn.setClicked(true);
    SetCursorPos(mineIn.getXCoord(),mineIn.getYCoord());
    LeftClick();
    //Update vector to add this one to it
    coordsOfClicks.push_back(&mineIn);
    updatePossibilities(mineIn);
    //Update possibilities of all surrounding mines
    minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
        {
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear))&& minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
       // minePtr->flagsNear++;
       if (minePtr->possibilities > 0)
       {
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear))&& minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
        {
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear))&& minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
        {
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear))&& minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
       // minePtr->flagsNear++;
       if (minePtr->possibilities > 0)
       {
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear))&& minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
        {
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear))&& minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
       // minePtr->flagsNear++;
       if (minePtr->possibilities > 0)
       {
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear))&& minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }

    }

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
        {
            if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear))&& minePtr->possibilities > 0)
                flagPossibilities(*minePtr);
        }
    }
}

char minesweeperGame::getColor(int byteValue)
{
    if (bitPointer[byteValue] > bitPointer[byteValue+1] && bitPointer[byteValue] > bitPointer[byteValue+1])
        return 'b';
    else if (bitPointer[byteValue+1] > bitPointer[byteValue] && bitPointer[byteValue+1] > bitPointer[byteValue+2])
        return 'g';
    else
        return 'r';
}
void minesweeperGame::checkBlue(mineSquare& mineIn, int byteValue)
{
    while (!isWhite(byteValue-4) || !isWhite(byteValue + ScreenX * 4))
        byteValue += (ScreenX * 4);

    if (isWhite(byteValue - 4))
        mineIn.setValue('1');
    else
        mineIn.setValue('4');
    return;
}
void minesweeperGame::checkRed(mineSquare& mineIn, int byteValue)
{
    return;
}
void minesweeperGame::checkGreen(mineSquare& mineIn, int byteValue)
{
    return;
}
void minesweeperGame::findSquareValue(mineSquare& mineIn)
{
    //Find value of current square
    
    if (mineIn.getValue() != 'e')
        return;

    //Check for any white on one line


    //Calculate byte value of pixels
    //1: R 25, G 188, B 223
    //2: 117, 151, 32
    //3: 228, 74, 134

    //To Check for white, rgb over 200

    //For one, go to rightmost side, and trace down
    //For 2, follow straightness of bottom 

    //For 3, 

    //Start at top right corner of square
    //Get right, get top
    int byteValue = getXYByte(mineIn.getXCoord(), mineIn.getYCoord());
    byteValue += (bytesBetweenSquares / 2);
    //std::cout << bytesBetweenSquares << std::endl;
    while (byteValue % 4 != 0)
        byteValue--;
    
    SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
    do
    {
        byteValue-=4;
        SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
    }while (bitPointer[byteValue] < 100);
    if (!isWhite(byteValue-8))
        return;

    do
    {
        byteValue -= (ScreenX * 4);
        SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
    } while (bitPointer[byteValue] > 100);
    int topSquare = bytesToPixelsY(byteValue);
    //Have top right, now go diagonally down left while white

    //Move until isWhite
    do
    {
        byteValue -= 8;
        byteValue += (ScreenX * 4);
        SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
    }while (!isWhite(byteValue));

    while(isWhite((byteValue - 4) + ScreenX*4))
    {
        byteValue -= 4;
        byteValue += (ScreenX * 4);
        if (bytesToPixelsX(byteValue) < mineIn.getXCoord())
        {
            mineIn.setValue('w');
            return;
        }
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
    }
    
    if (bytesToPixelsX(byteValue) < mineIn.getXCoord())
    {
        mineIn.setValue('w');
        return;
    }

    char color = getColor((byteValue - 4) + ScreenX*4);
    if (color == 'b')
        checkBlue(mineIn, byteValue);
    else if (color == 'g')
        checkGreen(mineIn, byteValue);
    else
        checkRed(mineIn, byteValue);

    bool isCurved(false);
    int postX(0);
    if (!isWhite(byteValue + (ScreenX * 4)))
    {
        while (!isWhite(byteValue + (ScreenX * 4)))
        {
            do
            {
                byteValue += 4;
                postX++;
            }while (!isWhite(byteValue + (ScreenX * 4)));
            byteValue += (ScreenX * 4);
            SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));

            /*if (isWhite(byteValue + 4 + (ScreenX * 4)))
            {
                byteValue += 4 + (ScreenX * 4);
                SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
Sleep(10);
            }
            else if (isWhite(byteValue + 8 + (ScreenX * 4)))
            {
                byteValue += 8 + (ScreenX * 4);
                //postX+= 2;
                SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
Sleep(10);
            }*/
        }
    }
    if (postX > 1)
        isCurved = true;
    moveDownNumber(byteValue, isCurved);

    //Check for number 1
    //isXChanged is no, is Curved is no
    //Next y value down should be white, otherwise it's a 4
    if (isCurved == false)
    {
        if (isWhite(byteValue + (ScreenX * 4)))
        {
            mineIn.setValue('1');
        }
        else
            mineIn.setValue('4');
        return;
    }

    //Check for 2 and 3
    //If 2, then byteValue should be below half of the square should be greater than top plus bytesBetweenSquares * ScreenX * 4
    //Otherwise, it's a 3
    //if (isWhite(byteValue + 12 + (ScreenX * 4) * 3))

    //std::cout << bytesToPixelsY(byteValue) << std::endl;
    //std::cout << topSquare << std::endl;
    //std::cout << squareHeight / 2;
    if ((!isWhite(byteValue + (ScreenX * 4))) &&  !isRed(byteValue + (ScreenX * 4)))
    {
        mineIn.setValue('2');
    }
    else
        mineIn.setValue('3');
    return;
}
bool minesweeperGame::isRed(int byteValue)
{
    return (bitPointer[byteValue+2] > bitPointer[byteValue+1]);
}
bool minesweeperGame::isBlue(int byteValue)
{
    return (bitPointer[byteValue] > bitPointer[byteValue+1]);
}

void minesweeperGame::moveDownNumber(int& byteValue, bool& isCurved)
{
    int initX = bytesToPixelsX(byteValue);
    int postX = 0;
    bool negativeChange(false);

    //Move down by Y
    //If white, try moving left 2 pixels to find a non-white value
    //  If not possible, then this is a 1 value, return
    //  If possible, then make negativeChange = true
    //  check if postX differs by 2 or more pixels, if it does, change isCurved to true
    //and loop again
    //If nonwhite, try moving right 2 pixels to find white value
    //  if possible, check if negativeChange == true
    //      if false, then move and loop
    //      if true, then return
    //  if not possible, return
    do
    {
        //byteValue += (ScreenX * 4);
        if (isWhite(byteValue + (ScreenX * 4)))
        {
            byteValue += ScreenX * 4;
            SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
            if (isWhite(byteValue - 12))
                return;
            else if (isWhite(byteValue - 8))
            {
                byteValue -= 8;
                postX -= 2;
                SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
            }
            else if (isWhite(byteValue - 4))
            {
                byteValue -= 4;
                postX--;
                SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
            }
            if (postX < -1)
            {
                isCurved = true;
                negativeChange = true;
            }
        }
        else
        {
            if (isBlue(byteValue -8))
                return;
            if (negativeChange == true)
            {
                return;
            }
            else
            {
                if (!isWhite(byteValue + 12 + (ScreenX * 4)))
                {
                    return;
                }
                if (isWhite(byteValue + 4 + (ScreenX * 4)))
                {
                    byteValue += 4 + (ScreenX * 4);
                    //postX++;
                    SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
                }
                else if (isWhite(byteValue + 8 + (ScreenX * 4)))
                {
                    byteValue += 8 + (ScreenX * 4);
                    //postX+= 2;
                    SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
                }
                //if (postX > )
                   // isCurved = true;
            }
        }

    } while (true);
    return;
}

void minesweeperGame::SearchFor(int inR, int inG, int inB)
{
    for (int i = 0; i < (ScreenX * ScreenY * 4); i+=4)
    {
        if ((int)bitPointer[i] == inB && (int)bitPointer[i+1] == inG && (int)bitPointer[i+2] == inR)
        {
            i /= 4;
            std::cout << "Screenx = " << ScreenX << " ScreenY  = " << ScreenY << std::endl;
            std::cout << "i = " << i << "  X| " <<  i % (ScreenX * 4) << "  Y| " << i / (ScreenX * 4) << std::endl;
            break;
        }
    }
}
bool minesweeperGame::isWhite(int byteValue)
{
    int difference;
    if (bitPointer[byteValue] > 50 && bitPointer[byteValue+1] > 50 && bitPointer[byteValue+2] > 50)
        if ((abs(bitPointer[byteValue] - bitPointer[byteValue+1]) < 50) && abs(bitPointer[byteValue] - bitPointer[byteValue+2]) < 50)
        {
            return true;
        }
        return false;
    return false;
}

void minesweeperGame::initMap()
{

   //Find difference between 0 and (RightX*4) and make divisible by 4
    int centerDifference = (RightX * 4)/2;
    while ((centerDifference % 4) != 0)
        centerDifference--;

    //Set centerDifference as leftmost value for map checking
    centerDifference -= 20;
    centerDifference += (TopY * ScreenX * 4);
    //SetCursorPos(bytesToPixelsX(centerDifference), bytesToPixelsY(centerDifference));
       // //Sleep(500);
    int topOfFirstSquare = 0;

    //Find top of the first square
    do
    {
        centerDifference += (ScreenX * 4);
       // SetCursorPos(bytesToPixelsX(centerDifference), bytesToPixelsY(centerDifference));
               // Sleep(100);
        for (int index = centerDifference; index < (centerDifference + 40); index += 4)
        {
            if (bitPointer[index] >= 100)
            {
                //SetCursorPos(bytesToPixelsX(index), bytesToPixelsY(index));
                //Sleep(50);
                topOfFirstSquare = index;
                break;
            }
        }
    }while(topOfFirstSquare == 0);
    

    //Find bottom of the first square
    int BottomOfFirstSquare = topOfFirstSquare;
    do
    {
        //SetCursorPos(bytesToPixelsX(BottomOfFirstSquare), bytesToPixelsY(BottomOfFirstSquare));
               // Sleep(50);
        BottomOfFirstSquare += (ScreenX * 4);
    } while (bitPointer[BottomOfFirstSquare] >= 100); 
                /*SetCursorPos(bytesToPixelsX(topOfFirstSquare), bytesToPixelsY(topOfFirstSquare));
                Sleep(2000);
                SetCursorPos(bytesToPixelsX(BottomOfFirstSquare), bytesToPixelsY(BottomOfFirstSquare));
                Sleep(2000);*/
    int middleOfFirstSquare = topOfFirstSquare + pixelsToBytesY(((bytesToPixelsY(BottomOfFirstSquare) - bytesToPixelsY(topOfFirstSquare)) / 2));
    //SetCursorPos(bytesToPixelsX(middleOfFirstSquare), bytesToPixelsY(middleOfFirstSquare));
                //Sleep(2000);
    while ((middleOfFirstSquare % 4) != 0)
        middleOfFirstSquare--;

    //Find Left of first Square
    int mark = middleOfFirstSquare;
    
    do
    {
        //SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
                //Sleep(50);
        mark -= 4;
    } while (bitPointer[mark] >= 100);
    int leftOfFirstSquare = mark;

    //Find length of the black lines
    int startOfGap = mark;
    do
    {
        //SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
                //Sleep(50);
        mark -= 4;

    } while (bitPointer[mark] <= 100);
    mark += 4;
    int bytesOfGaps = startOfGap - mark;

    
    mark = leftOfFirstSquare;
    
    //Find Right of First Square
    do
    {
       // SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
                //Sleep(50);
        mark += 4;
    }while(bitPointer[mark] >= 100);
    int rightOfFirstSquare = mark;
    

    //Refind top of square
    mark =leftOfFirstSquare + ((rightOfFirstSquare - leftOfFirstSquare)/2);
    while ((mark % 4) != 0)
        mark--;
    do
    {
       // Sleep(50);
        //SetCursorPos(bytesToPixelsX(mark), bytesToPixelsY(mark));
        mark -= (ScreenX * 4);
    }while(bitPointer[mark] >= 100);
    topOfFirstSquare = mark;
    

    //Refind bottom of first square
    do
    {
        mark += (ScreenX * 4);
    } while (bitPointer[mark] >= 100);
    BottomOfFirstSquare = mark;
    squareHeight = bytesToPixelsY(BottomOfFirstSquare - topOfFirstSquare);
    int startOfGapY = mark;
    do
    {
        mark += (ScreenX * 4);
    } while (bitPointer[mark]<=100);
    mark -= (ScreenX * 4);
    int yGap = mark - startOfGapY; 

    int yMark = bytesToPixelsY(topOfFirstSquare) + ((bytesToPixelsY(BottomOfFirstSquare) - bytesToPixelsY(topOfFirstSquare)) / 2);

    int xMark =leftOfFirstSquare + ((rightOfFirstSquare - leftOfFirstSquare)/2);
    while ((xMark % 4) != 0)
        xMark--;

    mark = pixelsToBytesY(yMark) + (xMark % (ScreenX * 4));
    
    middleOfFirstSquare = mark;
    do
    {
        middleOfFirstSquare -= (rightOfFirstSquare - leftOfFirstSquare + bytesOfGaps);
    } while (bitPointer[middleOfFirstSquare] >= 100);
    middleOfFirstSquare += (rightOfFirstSquare - leftOfFirstSquare + bytesOfGaps);
    leftCorner = middleOfFirstSquare;

    //Count squares in entire map
    int counter(0);
    mark = leftCorner;

    int amountToJumpSide = (rightOfFirstSquare - leftOfFirstSquare + bytesOfGaps);
    do
    {   counter++;
        mark += amountToJumpSide;
    } while (bitPointer[mark] >= 100);
    
    mark -= amountToJumpSide;

    gameColumns = counter;
    counter = 0;

    int amountToJumpUp = BottomOfFirstSquare - topOfFirstSquare + yGap;

    do
    {
        counter++;
        mark += amountToJumpUp;
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
    bytesBetweenSquares = rightOfFirstSquare - leftOfFirstSquare;
    mark  = leftCorner;
    for (int row = 0; row < gameRows; row++)
    {

        mark = leftCorner;
        
        for (int i = 0; i < row; i++)
        {
            mark += amountToJumpUp;
            mark = findCenterY(mark);
            

        }
        for (int column = 0; column < gameColumns; column++)
        {
            mark = findCenterX(mark);
            //Determine placement in array and assign NULL if on edges, and the addresses of
            //near squares otherwise
            mapSquares[row][column].row = row;
            mapSquares[row][column].column = column;
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
            mark += amountToJumpSide;
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
    coordsOfClicks.clear();
    return;
}
bool minesweeperGame::MapGame()
{   
    //Creates a bitmap for the current desktop window
    //Sleep(100);
    SetProcessDPIAware();
    HDC windowDC = GetDC(GetDesktopWindow());
    HDC virtualDC = CreateCompatibleDC(windowDC);
    ScreenX = GetDeviceCaps(windowDC, HORZRES);
    ScreenY = GetDeviceCaps(windowDC, VERTRES);
    HBITMAP bitmapHandle = CreateCompatibleBitmap(windowDC, ScreenX, ScreenY);
    HGDIOBJ hOld = SelectObject(virtualDC, bitmapHandle);
    BitBlt(virtualDC, 0, 0, ScreenX, ScreenY, windowDC, 0, 0, SRCCOPY);
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
        //SetCursorPos(bytesToPixelsX(index), bytesToPixelsY(index));
        //Sleep(50);
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
        //SetCursorPos(bytesToPixelsX(index), bytesToPixelsY(index));
        //Sleep(50);
        index += 4;
    }
    
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
    return ((bytesIn / 4) % ScreenX);
}
int minesweeperGame::bytesToPixelsY(int bytesIn)
{
    return ((bytesIn / 4) / ScreenX);
}
int minesweeperGame::findCenterX(int byteIn)
{
    do 
    {
        byteIn -= 4;
    }while(bitPointer[byteIn] >= 100);
    int leftCoord = byteIn;
    do
    {
        byteIn += 4;
    } while(bitPointer[byteIn] >= 100);

    int rightCoord = byteIn;

    return (leftCoord + ((rightCoord - leftCoord)/2));
}
int minesweeperGame::findCenterY(int byteIn)
{
    do 
    {
        byteIn -= (4 * ScreenX);
    }while(bitPointer[byteIn] >= 100);
    int topCoord = byteIn;
    
    do
    {
        byteIn += (4 * ScreenX);
    } while(bitPointer[byteIn] >= 100);

    int bottomCoord = byteIn;
    int pixelsDown = (bytesToPixelsY(bottomCoord) - bytesToPixelsY(topCoord)) / 2;
    topCoord = topCoord + (pixelsDown * 4 * ScreenX);
    while (topCoord % 4 != 0)
    {
        topCoord--;
    }
    
    return (topCoord);
}
int minesweeperGame::getXYByte(int x, int y)
{
    return (pixelsToBytesX(x) + pixelsToBytesY(y));
}
void minesweeperGame::clearClicks()
{
    if (coordsOfClicks.size() == 0)
        exit;
    for (int i = (coordsOfClicks.size() - 1); i >= 0; i--)
    {
        MakeMove(*coordsOfClicks[i]);
        coordsOfClicks.erase(coordsOfClicks.begin() + i);
    }
    
}