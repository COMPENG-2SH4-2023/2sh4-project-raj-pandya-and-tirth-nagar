#include "GameMechs.h"
#include <time.h>
#include "MacUILib.h"
#include "objPosArrayList.h"
#include "player.h"

// Default constructor for GameMechs
GameMechs::GameMechs()
{
    // Set default values for the game board and flags
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = 0;
}

// Parameterized constructor for GameMechs
GameMechs::GameMechs(int boardX, int boardY)
{
    // Set values based on provided board dimensions
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = 0;
}

// Check if the exit flag is set
bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

// Check if the lose flag is set
bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

// Get user input from MacUILib (if available)
char GameMechs::getInput()
{
    if (MacUILib_hasChar() != 0){
        input =  MacUILib_getChar();	
    }
    return input;
}

// Get the size of the game board in the X dimension
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

// Get the size of the game board in the Y dimension
int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

// Set the exit flag to true
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

// Set the lose flag to true
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

// Set the input character received from the user
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

// Clear the stored input character
void GameMechs::clearInput()
{
    input = 0;
}

// Get the current score
int GameMechs::getScore(){
    return score;
}

// Increment the score
void GameMechs::incrementScore(){
    score++;
}

// Generate the position for the food on the game board
void GameMechs::generateFood(objPosArrayList &blocksOff) {
    // Use time and clock to seed the random number generator
    unsigned int seed = (unsigned int)time(NULL) + (unsigned int)clock();
    srand(seed);

    // Symbol for the food
    char symbol = 'n';
    int rand_x, rand_y;
    objPos tempPos;

    // Keep generating random positions until a valid position is found
    while (1) {
        bool found = false;

        // Generate random coordinates within the game board boundaries
        rand_x = (rand() % (boardSizeX - 2)) + 1;
        rand_y = (rand() % (boardSizeY - 2)) + 1;
        tempPos.setObjPos(rand_x, rand_y, symbol);

        // Check if the generated position conflicts with existing blocks
        for (int i = 0; i < blocksOff.getSize(); i++){
            objPos blockOff;
            blocksOff.getElement(blockOff, i);
            if (blockOff.isPosEqual(&tempPos) == 1){
                found = true;
            }
        }

        // Break the loop if a valid position is found
        if (found == false){
            break;
        }
    }

    // Set the position of the food
    foodPos.setObjPos(rand_x, rand_y, symbol);
}

// Get the current position of the food
void GameMechs::getFoodPos(objPos &returnPos){
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}
