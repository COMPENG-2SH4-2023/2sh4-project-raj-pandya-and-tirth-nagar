#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* GameMechsp;



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



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
    MacUILib_init();
    MacUILib_clearScreen();

    GameMechsp = new GameMechs(15, 30);
}

void GetInput(void)
{
   char input;
   if (MacUILib_hasChar() != 0){
	input =  MacUILib_getChar();	
   }
   GameMechsp->setInput(input);
}

void RunLogic(void)
{
    char input = GameMechsp->getInput();
    MacUILib_printf("%c", input);
    
    if(input != 0)  
    {
        switch(input)
        {                      
            case 27:  // exit
                GameMechsp->setExitTrue(); 
                break;
            default:
                break;
        }
        GameMechsp->setInput(0);
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    for (int i = 0; i < GameMechsp->getBoardSizeX(); i++)
    {
        for (int j = 0; j < GameMechsp->getBoardSizeY(); j++)
        {
            if(i == 0 || i == GameMechsp->getBoardSizeX() - 1 || j == 0 || j == GameMechsp->getBoardSizeY() - 1){
                MacUILib_printf("#");
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