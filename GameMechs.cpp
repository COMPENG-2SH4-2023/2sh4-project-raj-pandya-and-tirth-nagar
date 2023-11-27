#include "GameMechs.h"
#include <time.h>
#include "MacUILib.h"
#include "objPosArrayList.h"
#include "player.h"


GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = 0;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = 0;

}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
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

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore(){
    return score;
}

void GameMechs::incrementScore(){
    score++;
}



void GameMechs::generateFood(objPosArrayList &blocksOff) {
    unsigned int seed = (unsigned int)time(NULL) + (unsigned int)clock();
    srand(seed);

    char symbol = 'n';
    int rand_x, rand_y;
    objPos tempPos;
    while (1) {
        bool found = false;
        rand_x = (rand() % (boardSizeX - 2)) + 1;
        rand_y = (rand() % (boardSizeY - 2)) + 1;
        tempPos.setObjPos(rand_x, rand_y, symbol);
        for (int i = 0; i<blocksOff.getSize(); i++){
            objPos blockOff;
            blocksOff.getElement(blockOff, i);
            if (blockOff.isPosEqual(&tempPos) == 1){
                found = true;
            }
        }
        if (found == false){
            break;
        }
        
    } 
    // while (blockOff.isPosEqual(&tempPos) == 1);
    foodPos.setObjPos(rand_x, rand_y, symbol);
}

void GameMechs::getFoodPos(objPos &returnPos){
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);

}