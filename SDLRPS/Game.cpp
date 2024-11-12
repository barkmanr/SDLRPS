#include "Game.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "Texture.h"
#include "Level1.h"
#include "Level2.h"

Game::Game() 
{
	AssetController::Instance().Initialize(100000000);
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	Texture::Pool = new ObjectPool<Texture>();
}

Game::~Game()
{
		delete SpriteAnim::Pool;
		delete SpriteSheet::Pool;
		delete Texture::Pool;
}

void Game::Run()
{
	Level1* L1 = new Level1();
	L1->RunGame();
	if (!L1->getFQ())
	{

		Level2* L2 = new Level2(L1->getP1(), L1->getP2());
		L2->RunGame();
		delete L2;
	}
	delete L1;
}
//aded repo