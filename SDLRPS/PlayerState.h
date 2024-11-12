#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "StandardIncludes.h"

class Player;
class IdleState;
class RollState;
class PaperState;
class ScissState;
class RockState;

class PlayerState
{
public:
	PlayerState() {};
	virtual ~PlayerState() {};

	static IdleState* GetIdle() { return &m_idle; }
	static RollState* GetRoll() { return &m_roll; }
	static PaperState* GetPaper() { return &m_paper; }
	static ScissState* GetSciss() { return &m_sciss; }
	static RockState* GetRock() { return &m_rock; }

	virtual void HandleInput(Player* _player, SDL_Event _event) = 0;
	virtual void Update(Player* _player, float _deltaTime) = 0;
	virtual PlayerState* GetState() = 0;


private:
	static IdleState m_idle;
	static RollState m_roll;
	static PaperState m_paper;
	static ScissState m_sciss;
	static RockState m_rock;

};

class IdleState : public PlayerState 
{
public:
	IdleState() {}
	virtual ~IdleState() {}

	void HandleInput(Player* _player, SDL_Event _event) override;
	void Update(Player* _player, float _deltaTime) override;
	PlayerState* GetState() override;
};

class RollState : public PlayerState
{
public:
	RollState() {}
	virtual ~RollState() {}

	void HandleInput(Player* _player, SDL_Event _event) override;
	void Update(Player* _player, float _deltaTime) override;
	PlayerState* GetState() override;
};

class PaperState : public PlayerState
{
public:
	PaperState() {}
	virtual ~PaperState() {}

	void HandleInput(Player* _player, SDL_Event _event) override;
	void Update(Player* _player, float _deltaTime) override;
	PlayerState* GetState() override;
};


class ScissState : public PlayerState
{
public:
	ScissState() {}
	virtual ~ScissState() {}

	void HandleInput(Player* _player, SDL_Event _event) override;
	void Update(Player* _player, float _deltaTime) override;
	PlayerState* GetState() override;
};

class RockState : public PlayerState
{
public:
	RockState() {}
	virtual ~RockState() {}

	void HandleInput(Player* _player, SDL_Event _event) override;
	void Update(Player* _player, float _deltaTime) override;
	PlayerState* GetState() override;
};
#endif

