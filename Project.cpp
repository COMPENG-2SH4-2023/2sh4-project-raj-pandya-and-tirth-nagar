#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs* GameMechsp;
Player* player;


int main(void)
{

    Initialize();

    while((*GameMechsp).getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    GameMechsp = new GameMechs(15, 30);
    player = new Player(GameMechsp);
    objPos pos;

    player->getPlayerPos(pos);
    GameMechsp->generateFood(pos);

    MacUILib_init();
    MacUILib_clearScreen();
}

void GetInput(void)
{
    char input = GameMechsp->getInput();
    GameMechsp->setInput(input);
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();

}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos head;
    player->getPlayerPos(head);

    objPosArrayList playerPosList;
    player->getPlayerPosList(playerPosList);

    objPos food;
    GameMechsp->getFoodPos(food);

    for (int i = 0; i < GameMechsp->getBoardSizeX(); i++){
        for (int j = 0; j < GameMechsp->getBoardSizeY(); j++)
        {
            if(i == 0 || i == GameMechsp->getBoardSizeX() - 1 || j == 0 || j == GameMechsp->getBoardSizeY() - 1){
                MacUILib_printf("#");
            }
            else if (i == food.x && j == food.y){
                MacUILib_printf("n");
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
                    MacUILib_printf("*");
                }
                else
                {
                    MacUILib_printf(" ");
                }
            
           }
        }
        cout << "\n";
    }

    cout << "============ Debug info ============" << endl;
    cout << "Board Size: " << GameMechsp->getBoardSizeY() << " x " << GameMechsp->getBoardSizeX() << endl;
    
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

    MacUILib_printf("\nPlayer Position: (%d, %d)", head.y, head.x);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  
    MacUILib_uninit();
}