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

bool minesweeperGame::needToUpdateSurrounding(mineSquare& mineIn)
{
    mineSquare* minePtr;
    for (int i = 0; i < 8; i++)
    {
        minePtr = *(mineIn.adjacents[i]);
        if (minePtr != nullptr && minePtr->getPossibilities() > 0)
            return true;
    }
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

    if (!mineIn.getClicked())
        updatePossibilities(mineIn);
    //Check top left to see if new value
    //If new value, call MakeMove(xCoord, yCoord);

    for (int i = 0; i < 8; i++)
    {
        minePtr = *(mineIn.adjacents[i]);
        if (minePtr != nullptr && minePtr->getValue() == 'e')
            MakeMove(*minePtr);
    }
    
    if (mineIn.getValue() != 'w')
        findPossibilities(mineIn);  
    return;
}
void minesweeperGame::flagPossibilities(mineSquare& mineIn)
{

    //Checks each square around minIn
    //If the square checked is an 'e' square and not NULL
    //flags the square
    mineSquare* minePtr;
    
    for (int i = 0; i < 8; i++)
    {
        minePtr = *(mineIn.adjacents[i]);
        if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
            flagSquare(*minePtr);
    }
    return;
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
    Sleep(100);
    return;
}
void minesweeperGame::updatePossibilities(mineSquare& mineIn)
{
    mineSquare* minePtr;
    
    for (int i = 0; i < 8; i++)
    {
        minePtr = *(mineIn.adjacents[i]);
        if (minePtr != nullptr && minePtr->getValue() != 'e' && minePtr->getValue() != 'w')
        {
            if (minePtr->possibilities > 0)
            {
                    minePtr->possibilities--;
                if (minePtr->readyToFlag())
                    flagPossibilities(*minePtr);
            }

            //Check flag condition
            //if (minePtr->readyToFlag())
            //  flagPossibilities(*minePtr);
        }
    }
    return;
}
void minesweeperGame::updateFlags(mineSquare& mineIn)
{
    mineSquare* minePtr;
    for (int i = 0; i < 8; i++)
    {
        minePtr = *(mineIn.adjacents[i]);
        if (minePtr != nullptr && minePtr->getValue() != 'w')
        {
            minePtr->flagsNear++;
            if (minePtr->possibilities > 0)
                    minePtr->possibilities--;
        }
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

    
    for (int i = 0; i < 8; i++)
    {
        minePtr = *(mineIn.adjacents[i]);
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
    return;
}
void minesweeperGame::findPossibilities(mineSquare& mineIn)
{
    //Only initialized once. If already initialized, return
    //Checks each surrounding square for an 'e' value. If so, increments mineIn possibilities
    if (mineIn.possibilities != 0)
        return;
    
    mineSquare* minePtr;

    
    for (int i = 0; i < 8; i++)
    {
        minePtr = *(mineIn.adjacents[i]);
        if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
            mineIn.possibilities++;
    }

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
    
    for (int i = 0; i < 8; i++)
    {
        minePtr = *(mineIn.adjacents[i]);
        if (minePtr != nullptr && minePtr->getValue() == 'e' && minePtr->getClicked() == false)
            clickSquare(*minePtr);
    }
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
    Sleep(100);
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


    for (int i = 0; i < 8; i++)
    {
        minePtr = *(mineIn.adjacents[i]);
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
    return;
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

void minesweeperGame::moveToRightEdge(mineSquare& mineIn, int& byteValue)
//Precondition: mineIn is an initialized mineSquare object
//the calling minesweeperGame must have successfully initialized its map and mine values
//byteValue is a valid integer within the range of the calling minesweeperGame's bitPointer bitMap
//
//Postcondition: sets the byteValue to the center-Y value and rightmost edge of the mineIn square
{
    byteValue = getXYByte(mineIn.getXCoord(), mineIn.getYCoord());
    //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(50);
    byteValue += (bytesBetweenSquares / 2);
    //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
   // Sleep(50);
    while (byteValue % 4 != 0)
        byteValue--;
    do
    {
        byteValue-=4;
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
        //Sleep(50);
    }while (bitPointer[byteValue] < 100);
    return;
}

void minesweeperGame::checkBlue(mineSquare& mineIn, int byteValue)
//Precondition: mineIn is of a valid initialized mineSquare object
//byteValue is number of a pixel within the range of the calling minesweeperGame's bitPointer byte array
//PostCondition: assigns mineIn's "value" variable to either '1' or '4'
{
    moveToRightEdge(mineIn, byteValue);
    while (isWhite(byteValue - 4))
    {
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
        //Sleep(50);
        byteValue -= 4;
    }
    while (isWhite(byteValue) && !isWhite(byteValue - 4))
    {
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
       //Sleep(50);
        byteValue += (ScreenX * 4);
    }
    if (isWhite(byteValue) || isWhite(byteValue + (ScreenX * 4)))
        mineIn.setValue('1');
    else
        mineIn.setValue('4');

    return;
}
void minesweeperGame::moveTopEdge(mineSquare& mineIn, int& byteValue)
{
    byteValue = getXYByte(mineIn.getXCoord(), mineIn.getYCoord());
    //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
   // Sleep(300);
    byteValue -= bytesToPixelsX(bytesBetweenSquares / 2) * ScreenX * 4;
   // SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(2000);
    while (byteValue % 4 != 0)
        byteValue--;
    do
    {
        byteValue+=ScreenX * 4;
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
        //Sleep(50);
    }while (bitPointer[byteValue] < 100);
    return;
}
void minesweeperGame::moveBottomEdge(mineSquare& mineIn, int& byteValue)
{
    byteValue = getXYByte(mineIn.getXCoord(), mineIn.getYCoord());
    //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
   //Sleep(300);
    byteValue += bytesToPixelsX(bytesBetweenSquares / 2) * ScreenX * 4;
   //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(2000);
    while (byteValue % 4 != 0)
        byteValue--;
    do
    {
        byteValue-=ScreenX * 4;
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
        //Sleep(50);
    }while (bitPointer[byteValue] < 100);
    return;
}
bool minesweeperGame::isWhiteLine(int byteValue, mineSquare& mineIn)
{
    bool whiteLine(true);
    do
    {
        byteValue += (ScreenX * 4);
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
        //Sleep(300);
        if (!isWhite(byteValue))
        {
            whiteLine = false;
            break;
        }
    }while (bytesToPixelsY(byteValue) < mineIn.getYCoord());

    return whiteLine;
}
bool minesweeperGame::isWhiteLineAbove(int byteValue, mineSquare& mineIn)
{
    bool whiteLine(true);
    do
    {
        byteValue -= (ScreenX * 4);
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
       // Sleep(300);
        if (!isWhite(byteValue))
        {
            whiteLine = false;
            break;
        }
    }while (bytesToPixelsY(byteValue) > mineIn.getYCoord());

    return whiteLine;
}
void minesweeperGame::checkRed(mineSquare& mineIn, int byteValue)
{
    moveTopEdge(mineIn, byteValue);
    do
    {
        byteValue += (ScreenX * 4);
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
        //Sleep(300);
    }while (isWhite(byteValue + (ScreenX * 4)));

    int curveAmount(0);
    //Move down
    do
    {
        if (!isWhite(byteValue))
        {
            byteValue -= ScreenX * 4;
            curveAmount++;
        }
        if (isWhite(byteValue + (ScreenX * 4)))
        {
            byteValue += ScreenX * 4;
            curveAmount++;
            //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
            //Sleep(300);
        }
        byteValue += 4;
    }while (!isWhiteLine(byteValue, mineIn));
   
    if (curveAmount >= 1)
        mineIn.setValue('3');
    else
        mineIn.setValue('5');
    
    return;
}
void minesweeperGame::checkGreen(mineSquare& mineIn, int byteValue)
{
    moveBottomEdge(mineIn, byteValue);
    do
    {
        byteValue -= (ScreenX * 4);
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
        //Sleep(300);
    }while (isWhite(byteValue - (ScreenX * 4)));

    int curveAmount(0);
    //Move up
    do
    {
        if (isWhite(byteValue - (ScreenX * 4)))
        {
            byteValue -= ScreenX * 4;
            curveAmount++;
            //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
            //Sleep(300);
        }
        byteValue += 4;
    }while (!isWhiteLineAbove(byteValue, mineIn));
   
    if (curveAmount > 1)
        mineIn.setValue('6');
    else
        mineIn.setValue('2');
    return;
}
void minesweeperGame::findSquareValue(mineSquare& mineIn)
{
    //Find value of current square
    
    if (mineIn.getValue() != 'e')
        return;

    int byteValue = getXYByte(mineIn.getXCoord(), mineIn.getYCoord());
    
    //Move pixel to 5/6th of the way into the square
    byteValue += (bytesBetweenSquares / 3);
    //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
    //Sleep(50);
    while (byteValue % 4 != 0)
        byteValue--;

    if (!isWhite(byteValue))
        return;
    
    while(true)
    {
        byteValue -= 4;
        //SetCursorPos(bytesToPixelsX(byteValue), bytesToPixelsY(byteValue));
        //Sleep(50);
        if (!isWhite(byteValue))
            break;
        if (bytesToPixelsX(byteValue) < mineIn.getXCoord())
        {
            mineIn.setValue('w');
            return;
        }
    }
    
    if (isRed(byteValue))
        checkRed(mineIn, byteValue);
    else if (isBlue(byteValue))
        checkBlue(mineIn, byteValue);
    else 
        checkGreen(mineIn, byteValue);
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
    // SetCursorPos(bytesToPixelsX(centerDifference), bytesToPixelsY(centerDifference));
    //    Sleep(500);
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
                // SetCursorPos(bytesToPixelsX(index), bytesToPixelsY(index));
                // Sleep(50);
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
                
    int middleOfFirstSquare = topOfFirstSquare + pixelsToBytesY(((bytesToPixelsY(BottomOfFirstSquare) - bytesToPixelsY(topOfFirstSquare)) / 2));
    
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
    squareHeight = bytesToPixelsY(BottomOfFirstSquare - topOfFirstSquare);
    int startOfGapY = mark;
    do
    {
        // std::cout << mark;
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
        // SetCursorPos(bytesToPixelsX(index), bytesToPixelsY(index));
        // Sleep(100);
        index += (ScreenX * 4);
    }
    index /= 4;

    // SetCursorPos(bytesToPixelsX(index), bytesToPixelsY(index));
    // Sleep(50);
    TopY = (index + (20 * (ScreenX * 4))) / ScreenX;
    return;
}
void minesweeperGame::FindRight()
{
    //start at Y = TopY, and move right pixel by pixel until it finds a Blue value
    //Record X value into RightX
    int index(TopY * ScreenX * 4 );
    while(bitPointer[index] > 100)
    {
        // SetCursorPos(bytesToPixelsX(index), bytesToPixelsY(index));
        // Sleep(2);
        index += 4;
    }
    
    index /= 4;
    RightX = ScreenX;
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

bool minesweeperGame::findAdjacentSquare(mineSquare** minePtr, int sizeOfArray)
{
//Precondition: minePtr is an initialized array of mineSquare pointers
//sizeOfArray is the number of mineSquare pointers within minePtr
//Postcondition:
//Determines if every mineSquare within the minePtr array shares at least one adjacent mine. If not, returns nullptr, otherwise 
//checks if that adjacent mine would be paradoxical if sizeOfArray flags was added to its flag count
//If not, loops to find another adjacent square
//If so, returns a pointer to that mine
//If none were found within the loop, then return nullptr
    std::vector<mineSquare*> allAdjacents;
    bool sharedAdjacentExists;
    mineSquare** currentSquare;
    if (sizeOfArray == 0)
        return false;
    //Loop through adjacent squares of first member of array
    for (int i = 0; i < 8; i++)
    {
        //Checks all mines in the minePtr array for matching adjacent
        currentSquare = minePtr[0]->adjacents[i];
        if (*currentSquare == nullptr)
            continue;
        if (currentSquare != nullptr && (**currentSquare).getValue() != 'w' && (**currentSquare).getValue() != 'e')
        {
            for (int j = 1; j < sizeOfArray; j++)
            {
                sharedAdjacentExists = false;
                for (int k = 0; k < 8; k++)
                {
                    if (*minePtr[j]->adjacents[k] == *currentSquare)
                        sharedAdjacentExists = true;
                }
                if (!sharedAdjacentExists)
                    break;
    
                allAdjacents.push_back(*currentSquare);
            }
        }
    }
    if (allAdjacents.empty())
        return false;

    for (int i = 0; i < allAdjacents.size(); i++)
    {
        if (allAdjacents[i]->flagsNear + sizeOfArray > (allAdjacents[i]->getValue() - '0'))
            return true;
    }
    return false;

    /*std::cout << "Mine number " << i << ":\n";
    std::cout << "Row: " << minePtr[i]->row << std::endl << "Column: " << minePtr[i]->column << std::endl;
    std::cout << std::endl << std::endl;*/
}

void minesweeperGame::simulate(mineSquare& mineIn)
{
//Precondition: Pass in an initialized mineSquare value
//Postcondition: For each adjacent square of mineIn, simulates a "what-if" scenario for if a flag were to exist at that square.
//Checks: if a flag exists at an adjacent square, does that force a paradoxical state in the game. If so, then a flag 
//cannot exist at that square, and thus clicks the square

    mineSquare* flagSimulate;
    mineSquare* testAdjacent;
    for (int i = 0; i < 8; i++)
    {
        //Selects one adjacent square to "flag" in the 'what-if' scenario
        //this square must not be null, and must be empty
        flagSimulate = *(mineIn.adjacents[i]);
        if (flagSimulate == nullptr)
            continue;
        if (flagSimulate->getValue() == 'e')
        {
            mineSquare** minePtr = new mineSquare*[mineIn.possibilities - 1];
            int count(0);
            for (int j = 0; j < 8; j++)
            {

                if (j != i)
                {
                    testAdjacent = *(mineIn.adjacents[j]);
                    if (testAdjacent == nullptr)
                        continue;
                    if (testAdjacent->getValue() == 'e')
                    {
                        minePtr[count] = testAdjacent;
                        count++;
                    }
                    if (count == mineIn.possibilities - 1)
                        break;
                }
            }
            if(findAdjacentSquare(minePtr, count))
            {
                flagSquare(*flagSimulate);
            }
            delete[] minePtr;
        }
    }
    /*if (coordsOfClicks.size() == 0)
    {
        //Simulate if adjacents contain value - flagsNear flags if fulfills adjacent value
        //Collect all adjacents of the square that are empty
        int emptyCount(0);
        for (int i = 0; i < 8; i++)
        {
            if ((*(mineIn.adjacents[i]))->getValue() == 'e')
            {
                
            }
        }

    }*/
    
    return;
}

void minesweeperGame::clearClicks()
{
    if (coordsOfClicks.empty())
    {
        for (int i = 0; i < gameRows; i++)
        {
            for (int j = 0; j < gameColumns; j++)
            {
                mineSquare tempMine = mapSquares[i][j];
                if (tempMine.possibilities > 0)
                {
                    if ((tempMine.possibilities - (tempMine.getValue() - '0' - tempMine.flagsNear)) == 1)
                    {
                        simulate(tempMine);
                        SetCursorPos(0,0);
                        Sleep(50);
                        MapGame();
                        Sleep(50);
                    }
                    //else if ()
                }
            }
        }
    }

    for (int i = (coordsOfClicks.size() - 1); i >= 0; i--)
    {
        MakeMove(*coordsOfClicks[i]);
        coordsOfClicks.erase(coordsOfClicks.begin() + i);
    }

}