#ifndef BASE_LEVEL_H
#define BASE_LEVEL_H

class Renderer;
class TTFont;
class InputController;
class AudioController;
class SoundEffect;
class Song;
class WavDraw;
class PhysicsController;
class SpriteSheet;
class Timing;

#include "StandardIncludes.h"
#include "AudioController.h"


class BaseLevel
{
public:
	BaseLevel();
	virtual ~BaseLevel();
	virtual void Initialize();

	SDL_Event* getEvent() { return &m_sdlEvent; }
	Renderer* getRenderer() { return m_renderer; }
	bool getQuit() { return m_quit; }
	void setQuit(bool _quit) { m_quit = _quit; }
	AudioController* getAudioC() { return m_audio; }
	Song* getSong() { return m_song; }
	InputController* getInput() { return m_input; }
	Timing* getTiming() { return m_timing; }


	void HandleMusic();


private:
	static SDL_Event m_sdlEvent;
	static Renderer* m_renderer;
	bool m_quit;

	AudioController* m_audio;
	Song* m_song;

	InputController* m_input;
	Timing* m_timing;
};

#endif

