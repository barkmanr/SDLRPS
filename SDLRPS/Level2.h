#ifndef LEVEL2_H
#define LEVEL2_H

#include "BaseLevel.h"
class Player;

class Level2 : BaseLevel
{
public:
	Level2(string n1, string n2);
	virtual ~Level2();

	void Initialize();
	void ShutDown();
	void HandleInput();
	void HandleController();
	void SaveGame();
	void LoadGame();

	void RunGame();

private:
	TTFont* m_fArial20;

	SoundEffect* m_effects[MaxEffectChannels];

	Player* m_player1;
	Player* m_player2;

	int Saves;
	int Loads;
};

#endif

