#include "Player.h"
#include "objPos.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.x = (mainGameMechsRef->getBoardSizeX() - 2)/2;
    playerPos.y = (mainGameMechsRef->getBoardSizeY() - 2)/2;
    playerPos.symbol = '*';
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();

    // Update the direction state
    if(input != 0){
        switch(input){                      
            case 'w':
            case 'W':
                if (myDir != DOWN)
                    myDir = UP;
                break;
            case 'a':
            case 'A':
                if (myDir != RIGHT)
                    myDir = LEFT;
                break;
            case 's':
            case 'S':
                if (myDir != UP)
                    myDir = DOWN;
                break;
            case 'd':
            case 'D':
                if (myDir != LEFT)
                    myDir = RIGHT;
                break;
        }
    }
    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    if (myDir != STOP){
        switch (myDir)
        {
            case UP:
                playerPos.x--;
                break;
            case DOWN:
                playerPos.x++;
                break;
            case LEFT:
                playerPos.y--;
                break;
            case RIGHT:
                playerPos.y++;
                break;
        }

        int height = mainGameMechsRef->getBoardSizeY();
        int width = mainGameMechsRef->getBoardSizeX();

        if(playerPos.x <= 0)
        {
            playerPos.x = width - 2;
        }

        else if(playerPos.x >= width-1)
        {
            playerPos.x = 1;
        }

        else if(playerPos.y <= 0)
        {
            playerPos.y= height - 2;
        }

        else if(playerPos.y >= height - 1)
        {
            playerPos.y = 1;
        }
    }
}
