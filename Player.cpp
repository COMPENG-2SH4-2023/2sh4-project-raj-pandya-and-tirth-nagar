#include "Player.h"
#include "objPos.h"
#include "objPosArrayList.h"

#include <iostream>

// Constructor for the Player class
Player::Player(GameMechs* thisGMRef)
{
    // Initialize member variables
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Set the initial position of the player in the middle of the game board
    playerPos = objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    
    // Insert the initial position into the player's position list
    playerPosList.insertHead(playerPos);
}

// Destructor for the Player class
Player::~Player()
{
    // Delete any dynamically allocated memory
    delete mainGameMechsRef;
}

// Get the current direction of the player
int Player::getPlayerDir()
{
    return myDir;
}

// Get the current position of the player
void Player::getPlayerPos(objPos &returnPos)
{
    playerPosList.getHeadElement(returnPos);
}

// Get the list of positions representing the player's body
void Player::getPlayerPosList(objPosArrayList &returnPos)
{
    int size = playerPosList.getSize();
    for (int i = 0; i < size; i++)
    {
        objPos pos;
        playerPosList.getElement(pos, i);
        returnPos.insertTail(pos);
    }
}

// Update the direction of the player based on user input
void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    
    if(input != 0)  
    {
        // Process input to set the direction or exit the game

        switch(input)
        {
            case 27: // ASCII code for the ESC key
                mainGameMechsRef->setExitTrue();
                
                break;
            case 'w':
            case 'W':
                mainGameMechsRef->setInput('w');
                if (myDir != DOWN)
                    myDir = UP;
                break;
            case 'a':
            case 'A':
                mainGameMechsRef->setInput('a');
                if (myDir != RIGHT)
                    myDir = LEFT;
                break;
            case 's':
            case 'S':
                mainGameMechsRef->setInput('s');
                if (myDir != UP)
                    myDir = DOWN;
                break;
            case 'd':
            case 'D':
                mainGameMechsRef->setInput('d');
                if (myDir != LEFT)
                    myDir = RIGHT;
                break;
        }
    }

    mainGameMechsRef->clearInput();
}

// Move the player on the game board
void Player::movePlayer()
{
    // Get the position of the food on the game board
    objPos food;
    mainGameMechsRef->getFoodPos(food);

    // Get the current head and tail positions of the player's body
    objPos headpos;
    playerPosList.getHeadElement(headpos);

    // Variable to check if the player intersects with the food
    bool intersect = false;

    // Check if the player is moving (not in STOP state)
    if (myDir != STOP){
        // Update player's position based on the current direction
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
        

        // Check if the player has hit the game board boundaries
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

        // Check if the head position is the same as the food position
        if (headpos.isPosEqual(&food)){
            intersect = true;
        }
        if (intersect == false){
            // If no intersection with food, remove the tail (move forward)
            playerPosList.removeTail();
        }
        else {
            // If intersection with food, generate new food, and increment score
            intersect = false;
            mainGameMechsRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
    }

    // Check for self-collision
    if (checkSelfCollision() == true){
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}

// Check for self-collision of the player's body
bool Player::checkSelfCollision(){
    objPos headpos;
    playerPosList.getHeadElement(headpos);

    for (int i = 1; i<playerPosList.getSize(); i++){
        objPos block;
        playerPosList.getElement(block, i);
        if (headpos.isPosEqual(&block) == 1){
            return true;
        }
    }
    return false;
}
