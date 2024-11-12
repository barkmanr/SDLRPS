#include "Level2.h"
#include "Renderer.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "RenderTarget.h"
#include "Keyboard.h"
#include "InputController.h"
#include "Mouse.h"
#include "Controller.h"
#include "AudioController.h"
#include "SoundEffect.h"
#include "Song.h"
#include "PhysicsController.h"
#include "RigidBody.h"
#include "Particle.h"
#include "Player.h"

Level2::Level2(string n1, string n2) //names form level 1
{
	m_fArial20 = nullptr;

	memset(m_effects, 0, sizeof(SoundEffect*) * MaxEffectChannels);
	m_player1 = new Player();
	m_player1->SetPosition({ 20,30 });
	m_player1->setName(n1);
	m_player2 = new Player();
	m_player2->SetPosition({ 20,330 });
	m_player2->setName(n2);
	Saves = 0;
	Loads = 0;
}

Level2::~Level2()
{
	ShutDown();
}

void Level2::Initialize()
{
	BaseLevel::Initialize();
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_effects[0] = getAudioC()->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");
	m_effects[1] = getAudioC()->LoadEffect("../Assets/Audio/Effects/DistantGunshot.mp3");
}

void Level2::ShutDown()
{
	if (m_player1 != nullptr) 
	{
		delete m_player1;
	}
	if (m_player2 != nullptr)
	{
		delete m_player2;
	}
	if (m_fArial20 != nullptr)
	{
		delete m_fArial20;
		m_fArial20 = nullptr;
	}
}

void Level2::HandleInput()
{
	if ((getEvent()->type == SDL_QUIT) || (getInput()->KB()->KeyUp(*getEvent(), SDLK_ESCAPE)))
	{
		setQuit(true);
		return;
	}
	else if (getInput()->KB()->KeyUp(*getEvent(), SDLK_F5))
	{
		SaveGame();
	}
	else if (getInput()->KB()->KeyUp(*getEvent(), SDLK_F7))
	{
		LoadGame();
	}

	m_player1->HandleInput(*getEvent(), getTiming()->GetDeltaTime());
	m_player2->HandleInput(*getEvent(), getTiming()->GetDeltaTime());

	glm::vec2 p1 = m_player1->GetPosition();
	if (getInput()->KB()->KeyDown(*getEvent(), SDLK_w))
	{
		m_player1->SetVert(-3.5f);
	}
	if (getInput()->KB()->KeyDown(*getEvent(), SDLK_s))
	{
		m_player1->SetVert(3.5f);
	}
	if (getInput()->KB()->KeyDown(*getEvent(), SDLK_a))
	{
		m_player1->SetHor(-3.5f);
	}
	if (getInput()->KB()->KeyDown(*getEvent(), SDLK_d))
	{
		m_player1->SetHor(3.5f);
	}

	glm::vec2 p2 = m_player2->GetPosition();
	if (getInput()->KB()->KeyDown(*getEvent(), SDLK_UP))
	{
		m_player2->SetVert(-3.5f);
	}
	if (getInput()->KB()->KeyDown(*getEvent(), SDLK_DOWN))
	{
		m_player2->SetVert(3.5f);
	}
	if (getInput()->KB()->KeyDown(*getEvent(), SDLK_LEFT))
	{
		m_player2->SetHor(-3.5f);
	}
	if (getInput()->KB()->KeyDown(*getEvent(), SDLK_RIGHT))
	{
		m_player2->SetHor(3.5f);
	}
	//
	if (getInput()->KB()->KeyUp(*getEvent(), SDLK_w))
	{
		m_player1->SetVert(0);
	}
	if (getInput()->KB()->KeyUp(*getEvent(), SDLK_s))
	{
		m_player1->SetVert(0);
	}
	if (getInput()->KB()->KeyUp(*getEvent(), SDLK_a))
	{
		m_player1->SetHor(0);
	}
	if (getInput()->KB()->KeyUp(*getEvent(), SDLK_d))
	{
		m_player1->SetHor(0);
	}

	if (getInput()->KB()->KeyUp(*getEvent(), SDLK_UP))
	{
		m_player2->SetVert(0);
	}
	if (getInput()->KB()->KeyUp(*getEvent(), SDLK_DOWN))
	{
		m_player2->SetVert(0);
	}
	if (getInput()->KB()->KeyUp(*getEvent(), SDLK_LEFT))
	{
		m_player2->SetHor(0);
	}
	if (getInput()->KB()->KeyUp(*getEvent(), SDLK_RIGHT))
	{
		m_player2->SetHor(0);
	}

	getInput()->MS()->ProcessButtons(*getEvent());
	if (getInput()->MS()->Moved(*getEvent()))
	{
		Point* ms = getInput()->MS()->GetPos();
		if (getInput()->MS()->GetButLDown())
		{
			p1.x = (int)ms->X - 140;
			p1.y = (int)ms->Y - 85;
			m_player1->SetPosition(p1);
		}
		if (getInput()->MS()->GetButRDown())
		{
			p2.x = (int)ms->X - 140;
			p2.y = (int)ms->Y - 85;
			m_player2->SetPosition(p2);
		}
	}


	else if ((getInput()->CT()->Added(*getEvent())) || (getInput()->CT()->Removed(*getEvent()))
		|| (getInput()->CT()->ProcessButtons(*getEvent())) || (getInput()->CT()->ProcessMotion(*getEvent())))
		{
		}
}

void Level2::HandleController() 
{
	if(!getInput()->CT()->GetControllers().empty())
	{
		glm::vec2 p1 = m_player1->GetPosition();
		glm::vec2 p2 = m_player2->GetPosition();
		Position L = getInput()->CT()->GetControllers()[0].LeftAxis;
		Position R = getInput()->CT()->GetControllers()[0].RightAxis;

		if (L.X > 1000 || L.X < -1000)
		{
			p1.x = p1.x + (L.X / 10000);
			m_player1->SetPosition(p1);
		}
		if (L.Y > 1000 || L.Y < -1000)
		{
			p1.y = p1.y + (L.Y / 10000);
			m_player1->SetPosition(p1);
		}

		if (R.X > 1000 || R.X < -1000)
		{
			p2.x = p2.x + (R.X / 10000);
			m_player2->SetPosition(p2);
		}
		if (R.Y > 1000 || R.Y < -1000)
		{
			p2.y = p2.y + (R.Y / 10000);
			m_player2->SetPosition(p2);
		}
	}
}

void Level2::SaveGame() 
{
	ofstream writeStream("level.bin", ios::out | ios::binary);
	m_player1->Serialize(writeStream);
	m_player2->Serialize(writeStream);
	writeStream.close();
	Saves++;
}

void Level2::LoadGame()
{
	if(Saves > 0)
	{
		ifstream readStream("level.bin", ios::out | ios::binary);
		m_player1->Deserialize(readStream);
		m_player2->Deserialize(readStream);
		readStream.close();
		Loads++;
	}
}

void Level2::RunGame()
{
	Initialize();
	Point ws = getRenderer()->GetWindowSize();
	getInput()->CT()->DetectControllers();

	while (!getQuit())
	{
		getTiming()->Tick();
		getRenderer()->SetDrawColor(Color(255, 255, 255, 255));
		getRenderer()->ClearScreen();

		while (SDL_PollEvent(getEvent()) != 0)
		{
			HandleInput();
		}
		HandleMusic();
		if (m_player1->getRoll() > 0)
		{
			m_player1->CheckWin(m_player2);
			getAudioC()->Play(m_effects[1]);
		}
		else if(m_player1->getRoll() == -1)
		{
			getAudioC()->Play(m_effects[0]);
			m_player1->setRoll(0);
		}
		m_player1->Update(getTiming()->GetDeltaTime(), ws);
		m_player1->Render(getRenderer(),m_fArial20);
		m_player2->Update(getTiming()->GetDeltaTime(), ws);
		m_player2->Render(getRenderer(),m_fArial20);
		HandleController();

		string line = "Frames Per Second: " + to_string(getTiming()->GetFPS()) + "    Game Time: " + to_string((float)getTiming()->getCurrentTime() / 1000) + "    Saves: " + to_string(Saves) + "    Loads: " + to_string(Loads);
		m_fArial20->Write(getRenderer()->GetRenderer(), line.c_str(), SDL_Color{ 0,0,255 }, SDL_Point{ 0,(int)ws.Y-40 });
		line = "Quit [ESC]   Next Game State [Space]   Save [F5]   Load [F7]";
		m_fArial20->Write(getRenderer()->GetRenderer(), line.c_str(), SDL_Color{ 0,0,255 }, SDL_Point{ 0,(int)ws.Y - 20 });

		SDL_RenderPresent(getRenderer()->GetRenderer());
		getTiming()->CapFPS();
	}
}

