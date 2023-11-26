#include "Player.h"
#include "objPos.h"
#include "objPosArrayList.h"

#include <iostream>

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos = objPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList.insertHead(playerPos);
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
}

int Player::getPlayerDir()
{
    // return the reference to the playerPos arrray list
    return myDir;
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    playerPosList.getHeadElement(returnPos);
}

void Player::getPlayerPosList(objPosArrayList &returnPos)
{
    // return the reference to the playerPos arrray list
    size_t size = playerPosList.getSize();
    for (int i = 0; i < size; i++)
    {
        objPos pos;
        playerPosList.getElement(pos, i);
        returnPos.insertTail(pos);
    }
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    
    if(input != 0)  
    {
        switch(input)
        {
            case 27:
                mainGameMechsRef->setExitTrue();
                break;
            case 'w':
            case 'W':
                mainGameMechsRef->setInput('w');
                break;
            case 'a':
            case 'A':
                mainGameMechsRef->setInput('a');
                break;
            case 's':
            case 'S':
                mainGameMechsRef->setInput('s');
                break;
            case 'd':
            case 'D':
                mainGameMechsRef->setInput('d');
                break;
        }
        
    }

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

    objPos food;
    mainGameMechsRef->getFoodPos(food);

    bool intersect = false;

    
    objPos headpos;
    playerPosList.getHeadElement(headpos);
        

    objPos tailpos;
    playerPosList.getTailElement(tailpos);


    if (myDir != STOP){

        switch (myDir)
        {
            case UP:
                playerPos.x--;
                playerPosList.insertHead(playerPos);
                break;
            case DOWN:
                playerPos.x++;
                playerPosList.insertHead(playerPos);
                break;
            case LEFT:
                playerPos.y--;
                playerPosList.insertHead(playerPos);
                break;
            case RIGHT:
                playerPos.y++;
                playerPosList.insertHead(playerPos);
                break;
        }

        int height = mainGameMechsRef->getBoardSizeY();
        int width = mainGameMechsRef->getBoardSizeX();

        if(playerPos.x <= 0)
        {
            playerPos.x = width - 2;
            playerPosList.insertHead(playerPos);
            playerPosList.removeTail();
        }

        else if(playerPos.x >= width-1)
        {
            playerPos.x = 1;
            playerPosList.insertHead(playerPos);
            playerPosList.removeTail();
        }

        else if(playerPos.y <= 0)
        {
            playerPos.y= height - 2;
            playerPosList.insertHead(playerPos);
            playerPosList.removeTail();
        }

        else if(playerPos.y >= height - 1)
        {
            playerPos.y = 1;
            playerPosList.insertHead(playerPos);
            playerPosList.removeTail();
        }

        playerPosList.getHeadElement(headpos);

        if (headpos.isPosEqual(&food)){
            intersect = true;
        }
        if (intersect == false){
            playerPosList.removeTail();
        }
        else {
            intersect = false;
            mainGameMechsRef->generateFood(headpos);
        }
    }
}
