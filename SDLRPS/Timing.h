#ifndef TIMING_H
#define TIMING_H

#include "StandardIncludes.h"

class Timing : public Singleton<Timing>
{
public:
	Timing();
	virtual ~Timing() {}

	unsigned int GetFPS() { return m_fpsLast; }
	float GetDeltaTime() { return m_deltaTime; }
	unsigned int getCurrentTime() { return m_currentTime; }

	void Tick();
	void SetFPS(int _fps);
	void CapFPS();

private:
	unsigned int m_currentTime;
	unsigned int m_lastTime;
	unsigned int m_fpsStart;
	unsigned int m_fpsCount;
	unsigned int m_fpsLast;
	float m_deltaTime;

	unsigned int m_targetFPS;
	unsigned int m_ticksPerFrame;
};

#endif

