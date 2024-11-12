#ifndef LEVEL1_H
#define LEVEL1_H

#include "BaseLevel.h"

class Level1 : BaseLevel
{

public:
	Level1();
	virtual ~Level1();

	void Initialize();
	void ShutDown();
	void HandleInput();

	string getP1() { return m_name1; }
	string getP2() { return m_name2; }
	bool getFQ() { return fullQuit; }

	void RunGame();

private:
	TTFont* m_fArial20;
	TTFont* m_fArial40;
	bool fullQuit;
	int m_section;
	string m_name1;
	string m_name2;
	string m_error;

};

#endif

