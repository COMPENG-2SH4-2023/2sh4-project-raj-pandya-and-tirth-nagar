#include <iostream>
#include "objPos.h"
#include "player.h"
#include "GameMechs.h"
#include "MacUILib.h"



using namespace std;

#define DELAY_CONST 100000

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

    objPos pos;
    player->getPlayerPos(pos);

    objPos food;
    GameMechsp->getFoodPos(food);

    for (int i = 0; i < GameMechsp->getBoardSizeX(); i++)
    {
        for (int j = 0; j < GameMechsp->getBoardSizeY(); j++)
        {
            if(i == 0 || i == GameMechsp->getBoardSizeX() - 1 || j == 0 || j == GameMechsp->getBoardSizeY() - 1){
                MacUILib_printf("#");
            }
            else if(i == pos.x && j == pos.y){
                MacUILib_printf("*");
            }
            else if (i == food.x && j == food.y){
                MacUILib_printf("%c", food.symbol);
            }
            else{
                MacUILib_printf(" ");
            }
        }
        cout << "\n";
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  
    delete GameMechsp;  
  
    MacUILib_uninit();
}