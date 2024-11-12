#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "StandardIncludes.h"
#include "ObjectPool.h"

class RigidBody
{
public:
	RigidBody();
	virtual ~RigidBody();

	glm::vec2& GetPosition() { return m_position; }
	void setPosition(glm::vec2 _position) { m_position = _position; }
	glm::vec2& GetVelocity() { return m_velocity; }
	void SetVelocity(glm::vec2 _velocity) { m_velocity = _velocity; }
	float GetMass() { return m_mass; }
	void SetMass(float _mass) { m_mass = _mass; }
	bool GetDead() { return m_dead; }
	void SetDead(bool _dead) { m_dead = _dead; }

	glm::vec2& GetBuoyancy() { return m_buoyancy; }
	void SetBuoyancy(glm::vec2 _buoyancy) { m_buoyancy = _buoyancy; }
	glm::vec2& GetBuoyancyDecay() { return m_buoyancyDecay; }
	void SetBuoyancyDecay(glm::vec2 _buoyancyDecay) { m_buoyancyDecay = _buoyancyDecay; }
	glm::vec2& GetBuoyancyMin() { return m_buoyancyMin; }
	void SetBuoyancyMin(glm::vec2 _buoyancyMin) { m_buoyancyMin = _buoyancyMin; }
	glm::vec2& GetWind() { return m_wind; }
	void SetWind(glm::vec2 _wind) { m_wind = _wind; }
	glm::vec2& GetRandomForce() { return m_randomForce; }
	void SetRandomForce(glm::vec2 _random) { m_randomForce = _random; }

	virtual void Update(float _deltaTime, glm::vec2 _force);
	virtual void Reset();

	static ObjectPool<RigidBody>* Pool;

private:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	bool m_dead;

	glm::vec2 m_acceleration;
	glm::vec2 m_buoyancy;
	glm::vec2 m_buoyancyDecay;
	glm::vec2 m_buoyancyMin;
	glm::vec2 m_wind;
	glm::vec2 m_randomForce;
};

#endif