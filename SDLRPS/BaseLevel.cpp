#include "BaseLevel.h"
#include "Renderer.h"
#include "InputController.h"
#include "Timing.h"

Renderer* BaseLevel::m_renderer;
SDL_Event BaseLevel::m_sdlEvent;

BaseLevel::BaseLevel()
{
	m_sdlEvent = {};
	m_renderer = nullptr;
	m_quit = false;
	m_audio = nullptr;
	m_song = nullptr;
	m_input = nullptr;
	m_timing = nullptr;
}

BaseLevel::~BaseLevel()
{

}

void BaseLevel::Initialize()
{
	m_renderer = &Renderer::Instance();
	m_renderer->Initialize();
	m_audio = &AudioController::Instance();
	m_song = m_audio->LoadSong("../Assets/Audio/Music/Track1.mp3");
	m_input = &InputController::Instance();
	m_timing = &Timing::Instance();
}

void BaseLevel::HandleMusic()
{
	if (m_audio->MusicPosition() == 0)
	{
		m_audio->Play(m_song);
	}
}

