#include "GameMechs.h"
#include <time.h>
#include "MacUILib.h"

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    input = 0;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    input = 0;

}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar() != 0){
        input =  MacUILib_getChar();	
    }
    return input;

}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}



void GameMechs::generateFood(objPos blockOff) {
    unsigned int seed = (unsigned int)time(NULL) + (unsigned int)clock();
    srand(seed);

    char symbol = 'n';
    int rand_x, rand_y;
    objPos tempPos;
    do {
        rand_x = (rand() % (boardSizeX - 1)) + 1;
        rand_y = (rand() % (boardSizeY - 1)) + 1;
        tempPos.setObjPos(rand_x, rand_y, symbol);
        
    } while (blockOff.isPosEqual(&tempPos) == 1);
    foodPos.setObjPos(rand_x, rand_y, symbol);
}

void GameMechs::getFoodPos(objPos &returnPos){
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);

}