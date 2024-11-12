#include "Level1.h"
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

Level1::Level1()
{
	m_fArial20 = nullptr;
	m_fArial40 = nullptr;
	m_section = 0;
	fullQuit = false;
}

Level1::~Level1() 
{
	ShutDown();
}

void Level1::Initialize()
{
	BaseLevel::Initialize();
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_fArial40 = new TTFont();
	m_fArial40->Initialize(40);
}

void Level1::ShutDown()
{
	if (m_fArial20 != nullptr)
	{
		delete m_fArial20;
		m_fArial20 = nullptr;
	}
	if (m_fArial40 != nullptr) 
	{
		delete m_fArial40;
		m_fArial40 = nullptr;
	}
}

void Level1::HandleInput() 
{
	string temp;
	if ((getEvent()->type == SDL_QUIT) || (getInput()->KB()->KeyUp(*getEvent(), SDLK_ESCAPE)))
	{
		setQuit(true);
		fullQuit = true;
	}

	else if ((temp = getInput()->KB()->TextInput(*getEvent())) != "")
	{
		if(m_section == 0)
		{
			if(m_name1.size() < 20) //less that 21 characters
			{
				m_name1 += temp;
			}
		}
		else if (m_section == 1)
		{
			if (m_name2.size() < 20)
			{
				m_name2 += temp;
			}
		}
	}

	else if (getInput()->KB()->KeyDown(*getEvent(), SDLK_BACKSPACE))
	{
			if (m_section == 0  && m_name1.size())
			{
				m_name1.pop_back();
			}
			else if (m_section == 1 && m_name2.size())
			{
				m_name2.pop_back();
			}
	} 

	else if (getInput()->KB()->KeyUp(*getEvent(), SDLK_RETURN))
	{
		if (m_section == 0 && m_name1.size() == 0) 
		{
			m_error = "Player 1 Nickname cannot be empty";
			return;
		}
		else if (m_section == 1 && m_name2.size() == 0) 
		{
			m_error = "Player 2 Nickname cannot be empty";
			return;
		}
		else if (m_section == 1 && m_name2 == m_name1)
		{
			m_error = "Player 2 Nickname cannot be the same as player 1";
			return;
		}
		
		m_section++;
		m_error = "";
		if (m_section > 1) 
		{
			setQuit(true);
		}
	}
}

void Level1::RunGame() 
{
	Initialize();
	Texture* texture = Texture::Pool->GetResource();
	texture->Load("../Assets/Textures/Background.tga");
	Point ws = getRenderer()->GetWindowSize();

	while (!getQuit())
	{
		getTiming()->Tick();

		while (SDL_PollEvent(getEvent()) != 0)
		{
			HandleInput();
		}
		HandleMusic();
		getRenderer()->RenderTexture(texture, Rect{0,0,ws.X,ws.Y}); //Background Image
		m_fArial40->Write(getRenderer()->GetRenderer(), m_name1.c_str(), SDL_Color{255,255,0}, SDL_Point{45,65}); //player 1
		m_fArial40->Write(getRenderer()->GetRenderer(), m_name2.c_str(), SDL_Color{ 255,255,0 }, SDL_Point{ 45,205 }); //player 2
		m_fArial40->Write(getRenderer()->GetRenderer(), m_error.c_str(), SDL_Color{ 255,0,0 }, SDL_Point{ 45,300 }); //error message
		string temp = "Quit [ESC]   Next NickName [Return]";
		m_fArial20->Write(getRenderer()->GetRenderer(), temp.c_str(), SDL_Color{ 255,255,255 }, SDL_Point{ 0,(int)ws.Y - 20 });
		

		SDL_RenderPresent(getRenderer()->GetRenderer());
		getTiming()->CapFPS();
	}
}
