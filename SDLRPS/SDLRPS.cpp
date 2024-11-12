#include "GameController.h"
#include "Game.h"
int main()
{
	Game::Instance().Run(); 
	return 0;
	//when going to the second level, just minimize the console.
}