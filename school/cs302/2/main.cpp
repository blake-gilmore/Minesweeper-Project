#include <string>
#include <iostream>

//Global variable to keep track of whose turn it is in bowling game
bool turn(true);
bool bowl(std::string);
bool lastMove(std::string);
void changeTurn();
int main()
{
    std::string initGame;
    std::cout << "Enter pin formation: ";
    std::cin >> initGame;
    if (bowl(initGame))
        std::cout << "You win";
    else
        std::cout << "You lose";
    return 0;
}

bool bowl(std::string pins)
{
    std::string pinsAfterMove;
    bool bowlResult;
    bool tempTurn;
    //Loop for moves
    //Loop singular turns
    for (int i = 0; i < pins.size(); i++)
    {
        if (pins[i] == 'I')
        {
            pinsAfterMove = pins;
            pinsAfterMove[i] = 'X';
            if (lastMove(pinsAfterMove))
            {
                tempTurn = turn;
                changeTurn();
                return tempTurn;
            }
            changeTurn();
            bowlResult = bowl(pinsAfterMove);

            if (bowlResult && turn)
            {
                changeTurn();
                return true;
            }

            else if (!bowlResult && !turn)
            {
                changeTurn();
                return false;
            }
        }
    }

    //Loop for double turns
    for (int i = 0; i < pins.size() - 1; i++)
    {
        if (pins[i] == 'I' && pins[i+1] == 'I')
        {
            pinsAfterMove = pins;
            pinsAfterMove[i] = 'X';
            pinsAfterMove[i+1] = 'X';
            if (lastMove(pinsAfterMove))
            {
                tempTurn = turn;
                changeTurn();
                return tempTurn;
            }
            changeTurn();
            bowlResult = bowl(pinsAfterMove);

            if (bowlResult && turn)
            {
                changeTurn();
                return true;
            }

            else if (!bowlResult && !turn)
            {
                changeTurn();
                return false;
            }
        }
    }
    return bowlResult;
}

bool lastMove(std::string pins)
{
    for (int i = 0; i < pins.size(); i++)
        if (pins[i] == 'I')
            return false;
    return true;
}

void changeTurn()
{
    turn = !turn;
    return;
}