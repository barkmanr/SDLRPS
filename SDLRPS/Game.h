#ifndef GAME_H
#define GAME_H

#include "StandardIncludes.h"
class Game : public Singleton<Game>
{
public:
	Game();
	virtual ~Game();

	void Run();

private:
};

#endif

