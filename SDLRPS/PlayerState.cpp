#include "PlayerState.h"
#include "InputController.h"
#include "Player.h"
#include "SpriteSheet.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Keyboard.h"

IdleState PlayerState::m_idle;
RollState PlayerState::m_roll;
PaperState PlayerState::m_paper;
ScissState PlayerState::m_sciss;
RockState PlayerState::m_rock;

void IdleState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		_player->SetState(PlayerState::GetRoll());
		_player->setRoll(-1);
		_player->setStatus("Rolling...");
	}
}

void IdleState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_IDLE, _deltaTime, _player->GetSrcRect());
}

PlayerState* IdleState::GetState()
{
	return GetIdle();
}

//


void RollState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		srand(time(NULL) + rand() % 1000); //random seed = more random
		int x = rand() % 3;
		if(x == 0)
		{
			_player->SetState(PlayerState::GetPaper());
			_player->setRoll(1);
		}
		else if (x == 1)
		{
			_player->SetState(PlayerState::GetSciss());
			_player->setRoll(2);
		}
		else 
		{
			_player->SetState(PlayerState::GetRock());
			_player->setRoll(3);
		}
	}
}

void RollState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_ROLL, _deltaTime, _player->GetSrcRect());
}

PlayerState* RollState::GetState()
{
	return GetRoll();
}

//


void PaperState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		_player->SetState(PlayerState::GetIdle());
		_player->setRoll(0);
		_player->setStatus("Wating to start...");
	}
}

void PaperState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_PAPER, _deltaTime, _player->GetSrcRect());
}

PlayerState* PaperState::GetState()
{
	return GetPaper();
}
//


void ScissState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		_player->SetState(PlayerState::GetIdle());
		_player->setRoll(0);
		_player->setStatus("Wating to start...");
	}
}

void ScissState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_SCISS, _deltaTime, _player->GetSrcRect());
}

PlayerState* ScissState::GetState()
{
	return GetSciss();
}


//


void RockState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE))
	{
		_player->SetState(PlayerState::GetIdle());
		_player->setRoll(0);
		_player->setStatus("Wating to start...");
	}
}

void RockState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_ROCK, _deltaTime, _player->GetSrcRect());
}

PlayerState* RockState::GetState()
{
	return GetRock();
}
