#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

// Function prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Pointers to GameMechs and Player objects
GameMechs* GameMechsp;
Player* player;

int main(void)
{
    Initialize();

    // Main game loop
    while(GameMechsp->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

// Initialize the game components
void Initialize(void)
{
    // Create instances of GameMechs and Player
    GameMechsp = new GameMechs(15, 30);
    player = new Player(GameMechsp);

    // Get initial player position and create a list to track player positions
    objPos pos;
    player->getPlayerPos(pos);
    objPosArrayList playerPosList;
    player->getPlayerPosList(playerPosList);

    // Generate initial food position
    GameMechsp->generateFood(playerPosList);

    // Initialize MacUILib and clear the screen
    MacUILib_init();
    MacUILib_clearScreen();
}

// Get user input
void GetInput(void)
{
    char input = GameMechsp->getInput();
    GameMechsp->setInput(input);
}

// Run game logic (update player direction and move player)
void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
}

// Draw the game screen
void DrawScreen(void)
{
    MacUILib_clearScreen();

    // Get player head position and player position list
    objPos head;
    player->getPlayerPos(head);
    objPosArrayList playerPosList;
    player->getPlayerPosList(playerPosList);

    // Get food position
    objPos food;
    GameMechsp->getFoodPos(food);

    // Loop through each position on the game board and print characters
    for (int i = 0; i < GameMechsp->getBoardSizeX(); i++){
        for (int j = 0; j < GameMechsp->getBoardSizeY(); j++)
        {
            if(i == 0 || i == GameMechsp->getBoardSizeX() - 1 || j == 0 || j == GameMechsp->getBoardSizeY() - 1){
                MacUILib_printf("#"); // Draw the border
            }
            else
            {
                bool printPlayer = false;

                // Check if the current position is in the player's position list
                for (int k = 0; k < playerPosList.getSize(); k++)
                {
                    objPos pos;
                    playerPosList.getElement(pos, k);
                    if (i == pos.x && j == pos.y)
                    {
                        printPlayer = true;
                        break;
                    }
                }

                if (printPlayer)
                {
                    MacUILib_printf("*"); // Draw the player
                }
                else if (i == food.x && j == food.y){
                    MacUILib_printf("%c", food.symbol); // Draw the food
                }
                else
                {
                    MacUILib_printf(" "); // Draw an empty space
                }
            }
        }
        MacUILib_printf("\n");
    }

    // Display debug information
    MacUILib_printf("============ Debug info ============\nScore: %d\nBoard Size: %d x %d\n", GameMechsp->getScore(), GameMechsp->getBoardSizeY(), GameMechsp->getBoardSizeX());
    switch(player->getPlayerDir()){
        case 0:
            MacUILib_printf("Player Direction: Up");
            break;
        case 1:
            MacUILib_printf("Player Direction: Down");
            break;
        case 2:
            MacUILib_printf("Player Direction: Left");
            break;
        case 3:
            MacUILib_printf("Player Direction: Right");
            break;
        case 4:
            MacUILib_printf("Player Direction: None");
            break;
    }

    // Display player head position
    MacUILib_printf("\nPlayer Position: (%d, %d)", head.y, head.x);
}



// Introduce a delay in the game loop
void LoopDelay(void)
{
    MacUILib_Delay(100000); // 0.1s delay
}

// Clean up resources and display game over message
void CleanUp(void)
{
    MacUILib_clearScreen();  

    // Display game over message with the final score
    if (GameMechsp->getLoseFlagStatus() == true){
        MacUILib_printf("You Lose. You Scored: %d", GameMechsp->getScore());
    }
    MacUILib_uninit();
}
