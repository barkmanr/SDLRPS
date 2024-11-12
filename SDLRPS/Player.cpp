#include "Player.h"
#include "SpriteSheet.h"
#include "Renderer.h"
#include "TTFont.h"


Player::Player()
{
	m_state = PlayerState::GetIdle();

	m_position = { 0,0 };
	m_animations = SpriteSheet::Pool->GetResource();
	m_animations->Load("../Assets/Textures/RockPaperScissors.tga");
	m_animations->SetSize(4, 4, 280, 170); //Had to switch from byte to int in sprite sheet :( took a while to find ):
	m_animations->AddAnimation(EN_AN_IDLE, 0, 1, 2.0f);
	m_animations->AddAnimation(EN_AN_ROLL, 0, 4, 2.0f);
	m_animations->AddAnimation(EN_AN_PAPER, 4, 4, 2.0f);
	m_animations->AddAnimation(EN_AN_SCISS, 8, 4, 2.0f);
	m_animations->AddAnimation(EN_AN_ROCK, 12, 4, 2.0f);
	m_animations->SetBlendMode(SDL_BLENDMODE_BLEND);
	m_status = "Waiting to start...";
	m_wins = 0;
	m_losses = 0;
	roll = 0;
	m_moveVert = 0;
	m_moveHor = 0;
}

Player::~Player() {}

void Player::HandleInput(SDL_Event _event, float _deltaTime)
{
	m_state->HandleInput(this, _event);
}

void Player::Update(float _deltaTime,Point ws)
{
	m_position.y += m_moveVert;
	m_position.x += m_moveHor;
	m_state->Update(this, _deltaTime);
	if (m_position.x + 280 > ws.X) 
	{
		m_position.x = ws.X - 280;
	}
	if (m_position.x < 0.0f)
	{
		m_position.x = 0;
	}
	if (m_position.y + 170 > ws.Y)
	{
		m_position.y = ws.Y - 170;
	}
	if (m_position.y < 0.0f)
	{
		m_position.y = 0;
	}
	
}

void Player::Render(Renderer* _renderer, TTFont* _font)
{
	glm::vec2 p = m_position;
	Rect destRect = Rect(p.x, p.y, p.x + 280, p.y + 170);
	_renderer->RenderTexture(m_animations, m_srcRect, destRect);
	_font->Write(_renderer->GetRenderer(), m_name.c_str(), SDL_Color{ 0,255,0 }, SDL_Point{(int)p.x,(int)p.y});
	_font->Write(_renderer->GetRenderer(), m_status.c_str(), SDL_Color{ 255,0,0 }, SDL_Point{ (int)p.x,(int)p.y + 20 });
	_font->Write(_renderer->GetRenderer(), ("Wins: " + to_string(m_wins)).c_str(), SDL_Color{0,0,255}, SDL_Point{(int)p.x,(int)p.y + 40});
	_font->Write(_renderer->GetRenderer(), ("Losses: " + to_string(m_losses)).c_str(), SDL_Color{0,0,255}, SDL_Point{(int)p.x,(int)p.y + 60});
}

void Player::CheckWin(Player* _other) 
{
	if (roll == _other->roll) //drae
	{
		m_status = "DRAW!";
		_other->m_status = "DRAW!";
	}

	else if (roll == 1) //paper
	{
		if (_other->roll == 2) //scissors
		{
			addLoss();
			_other->addWin();
			m_status = "LOSER!";
			_other->m_status = "WINNER!";
		}
		else //rock
		{
			_other->addLoss();
			addWin();
			_other->m_status = "LOSER!";
			m_status = "WINNER!";
		}
	}

	else if (roll == 2) 
	{
		if (_other->roll == 3)
		{
			addLoss();
			_other->addWin();
			m_status = "LOSER!";
			_other->m_status = "WINNER!";
		}
		else
		{
			_other->addLoss();
			addWin();
			_other->m_status = "LOSER!";
			m_status = "WINNER!";
		}
	}

	else
	{
		if (_other->roll == 1)
		{
			addLoss();
			_other->addWin();
			m_status = "LOSER!";
			_other->m_status = "WINNER!";
		}
		else
		{
			_other->addLoss();
			addWin();
			_other->m_status = "LOSER!";
			m_status = "WINNER!";
		}
	}

	roll = 0;
	_other->roll = 0;
}

void Player::Serialize(ostream& _stream)
{
	PlayerState* state = m_state->GetState();
	_stream.write(reinterpret_cast<char*>(&state), sizeof(state));
	_stream.write(reinterpret_cast<char*>(&m_srcRect), sizeof(m_srcRect));
	_stream.write(reinterpret_cast<char*>(&m_position), sizeof(m_position));
	_stream.write(reinterpret_cast<char*>(&roll), sizeof(roll));
	unsigned int size = m_status.size();
	_stream.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (unsigned int i = 0; i < size; i++)
	{
		_stream.write(reinterpret_cast<char*>(&(m_status[i])), sizeof(m_status[i]));
	}
	_stream.write(reinterpret_cast<char*>(&m_wins), sizeof(m_wins));
	_stream.write(reinterpret_cast<char*>(&m_losses), sizeof(m_losses));
	m_animations->Serialize(_stream);
}

void Player::Deserialize(istream& _stream)
{
	PlayerState* state;
	_stream.read(reinterpret_cast<char*>(&state), sizeof(state)); 
	m_state = state;
	_stream.read(reinterpret_cast<char*>(&m_srcRect), sizeof(m_srcRect));
	_stream.read(reinterpret_cast<char*>(&m_position), sizeof(m_position));
	_stream.read(reinterpret_cast<char*>(&roll), sizeof(roll));
	unsigned int size = 0;
	_stream.read(reinterpret_cast<char*>(&size), sizeof(size));
	m_status = "";
	for (unsigned int i = 0; i < size; i++)
	{
		char c;
		_stream.read(reinterpret_cast<char*>(&c), sizeof(c));
		m_status.push_back(c);
	}
	_stream.read(reinterpret_cast<char*>(&m_wins), sizeof(m_wins));
	_stream.read(reinterpret_cast<char*>(&m_losses), sizeof(m_losses));
	m_animations->Deserialize(_stream);
}
