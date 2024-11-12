#ifndef PARTICLE_H
#define PARTICLE_H

#include "RigidBody.h"
#include "ObjectPool.h"

class Particle : public RigidBody
{
public:
	Particle();
	virtual ~Particle();

	float GetLifeTime() { return m_lifeTime; }
	void SetLifeTime(float _lifeTime) { m_lifeTime = _lifeTime; }
	float GetStartSize() { return m_startSize; }
	void SetStartSize(float _size) { m_startSize = _size; }
	float GetEndSize() { return m_endSize; }
	void SetEndSize(float _size) { m_endSize = _size; }
	float GetCurrentSize() { return m_currentSize; }
	void SetCurrentSize(float _size) { m_currentSize = _size; }

	void Update(float _deltaTime, glm::vec2 _force) override;
	void Reset() override;

	static ObjectPool<Particle>* Pool;

private:
	float m_currentTime;
	float m_lifeTime;
	float m_startSize;
	float m_endSize;
	float m_currentSize;
};

#endif