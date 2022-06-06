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
    mineSquare* minePtr;
    minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        flagSquare(*minePtr);

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        flagSquare(*minePtr);

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        flagSquare(*minePtr);

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        flagSquare(*minePtr);

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        flagSquare(*minePtr);

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        flagSquare(*minePtr);

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        flagSquare(*minePtr);

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        flagSquare(*minePtr);
}
void RightClick()
{
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
    Sleep(500);
    return;
}
void minesweeperGame::flagSquare(mineSquare& mineIn)
{
    mineSquare* minePtr;
    if (mineIn.getValue() == 'f')
        return;
    mineIn.setValue('f');
    SetCursorPos(mineIn.getXCoord(),mineIn.getYCoord());
    RightClick();
    
    //Update possibilities of all surrounding mines
    minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);
    }

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }
}
void minesweeperGame::findPossibilities(mineSquare& mineIn)
{
    if (mineIn.possibilities != 0)
        return;
    mineIn.possibilities = 0;
    /*if (mineIn.flagsNear == (mineIn.getValue() - '0'))
        return;*/
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

    if (mineIn.getPossibilities() == (mineIn.getValue() - '0'))
            flagPossibilities(mineIn);  

    if (mineIn.flagsNear == (mineIn.getValue() - '0') && mineIn.getPossibilities() != 0)
        clickEmpties(mineIn);

    return;
}
void minesweeperGame::clickEmpties(mineSquare& mineIn)
{
    mineSquare* minePtr;
    minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        clickSquare(*minePtr);

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        clickSquare(*minePtr);

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        clickSquare(*minePtr);

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        clickSquare(*minePtr);

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        clickSquare(*minePtr);

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        clickSquare(*minePtr);

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
        clickSquare(*minePtr);

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() == 'e')
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
    Sleep(500);
    return;

}
void minesweeperGame::clickSquare(mineSquare& mineIn)
{

mineSquare* minePtr;
    mineIn.setClicked(true);
    SetCursorPos(mineIn.getXCoord(),mineIn.getYCoord());
    LeftClick();
    
    
    //Update possibilities of all surrounding mines
    minePtr = mineIn.getTopLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getTop();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
       // minePtr->flagsNear++;
       if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getTopRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
       // minePtr->flagsNear++;
       if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getBottomLeft();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getBottom();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
       // minePtr->flagsNear++;
       if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);

    }

    minePtr = mineIn.getBottomRight();
    if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
    {
        //minePtr->flagsNear++;
        if (minePtr->possibilities > 0)
            minePtr->possibilities--;
        else
            findPossibilities(*minePtr);
        if (minePtr->flagsNear == minePtr->getValue() - '0' && minePtr->possibilities > 0)
            clickEmpties(*minePtr);
        if (minePtr->possibilities == ((minePtr->getValue() - '0') - (minePtr->flagsNear)))
            flagPossibilities(*minePtr);
    }
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
    while (byteValue % 4 != 0)
        byteValue--;
    
    SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    ////Sleep(10);
    do
    {
        byteValue-=4;
        SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    ////Sleep(10);
    }while (bitPointer[byteValue] < 50);
    if (!isWhite(byteValue-8))
        return;

    do
    {
        byteValue -= (ScreenX * 4);
        SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    ////Sleep(10);
    } while (bitPointer[byteValue] > 25);

    //Have top right, now go diagonally down left while white

    //Move until isWhite
    do
    {
        byteValue -= 4;
        byteValue += (ScreenX * 4);
        SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    ////Sleep(10);
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
        SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    ////Sleep(10);
    }
    
    if (bytesToPixelsX(byteValue) < mineIn.getXCoord())
    {
        mineIn.setValue('w');
        return;
    }

    bool isCurved(false);
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
    //If 2, then the next movements should be in a straight line
    //Otherwise, it's a 3
    if (isWhite(byteValue + 12 + (ScreenX * 4) * 3))
        mineIn.setValue('3');

    else
        mineIn.setValue('2');
    return;
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
                postX --;
                SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
            }
            if (postX < -2)
            {
                isCurved = true;
                negativeChange = true;
            }
        }
        else
        {
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
                    postX++;
                    SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
                }
                else if (isWhite(byteValue + 8 + (ScreenX * 4)))
                {
                    byteValue += 8 + (ScreenX * 4);
                    postX+= 2;
                    SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(10);
                }
                if (postX > 2)
                    isCurved = true;
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
    

    //Find bottom of the first square
    int BottomOfFirstSquare = topOfFirstSquare;
    do
    {
        BottomOfFirstSquare += (ScreenX * 4);
    } while (bitPointer[BottomOfFirstSquare] >= 100); 

    int middleOfFirstSquare = topOfFirstSquare + ((BottomOfFirstSquare - topOfFirstSquare) / 2);
    while ((middleOfFirstSquare % 4) != 0)
        middleOfFirstSquare--;

    //Find Left of first Square
    int mark = middleOfFirstSquare;
    
    do
    {
        mark -= 4;
    } while (bitPointer[mark] >= 100);
    int leftOfFirstSquare = mark;

    //Find length of the black lines
    int startOfGap = mark;
    do
    {
        mark -= 4;

    } while (bitPointer[mark] <= 100);
    mark += 4;
    int bytesOfGaps = startOfGap - mark;

    
    mark = leftOfFirstSquare;
    
    //Find Right of First Square
    do
    {
        mark += 4;
    }while(bitPointer[mark] >= 100);
    int rightOfFirstSquare = mark;
    

    //Refind top of square
    mark =leftOfFirstSquare + ((rightOfFirstSquare - leftOfFirstSquare)/2);
    while ((mark % 4) != 0)
        mark--;
    do
    {
        mark -= (ScreenX * 4);
    }while(bitPointer[mark] >= 100);
    topOfFirstSquare = mark;
    

    //Refind bottom of first square
    do
    {
        mark += (ScreenX * 4);
    } while (bitPointer[mark] >= 100);
    BottomOfFirstSquare = mark;

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