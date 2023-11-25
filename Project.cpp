#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "player.h"
#include "GameMechs.h"


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

    MacUILib_init();
    MacUILib_clearScreen();
}

void GetInput(void)
{
   char input;
   if (MacUILib_hasChar() != 0){
	input =  MacUILib_getChar();	
    GameMechsp->setInput(input);
   }
}

void RunLogic(void)
{
    char input = GameMechsp->getInput();
    
    if(input != 0)  
    {
        switch(input)
        {
            case 27:
                GameMechsp->setExitTrue();
                break;
            case 'w':
            case 'W':
                GameMechsp->setInput('w');
                break;
            case 'a':
            case 'A':
                GameMechsp->setInput('a');
                break;
            case 's':
            case 'S':
                GameMechsp->setInput('s');
                break;
            case 'd':
            case 'D':
                GameMechsp->setInput('d');
                break;
        }
        
    }
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos pos;
    player->getPlayerPos(pos);

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
            else{
                MacUILib_printf(" ");
            }
        }
        cout << "\n";
    }
    MacUILib_printf("X: %d Y: %d\n", pos.x, pos.y);

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