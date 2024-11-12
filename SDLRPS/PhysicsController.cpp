#include "PhysicsController.h"
#include "Particle.h"
#include "RigidBody.h"
#include "Renderer.h"

PhysicsController::PhysicsController()
{
	m_gravity = -9.81f;
	m_force = glm::vec2{ 0,0 };
	Particle::Pool = new ObjectPool<Particle>();
	RigidBody::Pool = new ObjectPool<RigidBody>();
}

PhysicsController::~PhysicsController()
{
	delete Particle::Pool;
	delete RigidBody::Pool;
}

void PhysicsController::Reflect(glm::vec2& _out, const glm::vec2& _incident, const glm::vec2& _normal)
{
	_out = _incident - 2.f * glm::dot(_incident, _normal) * _normal;
}

void PhysicsController::HandleCollision(RigidBody* _b1, RigidBody* _b2, float _distance)
{
	glm::vec2 x = _b1->GetPosition() - _b2->GetPosition();
	glm::vec2 v = _b1->GetVelocity() - _b2->GetVelocity();
	glm::vec2 v1 = _b1->GetVelocity();
	v1 -= (2 * _b2->GetMass() / (_b1->GetMass() + _b2->GetMass())) * (glm::dot(v, x) / ((float)pow((glm::length(x)), 2))) * x;
	_b1->SetVelocity(v1);

	x *= -1;
	v *= -1;
	glm::vec2 v2 = _b2->GetVelocity();
	v2 -= (2 * _b1->GetMass() / (_b1->GetMass() + _b2->GetMass())) * (glm::dot(v, x) / ((float)pow((glm::length(x)), 2))) * x;
	_b2->SetVelocity(v2);
}

void PhysicsController::Update(float _deltaTime)
{
	for (int count = 0; count < m_particles.size(); count++)
	{
		Particle* P = m_particles[count];
		m_force.y = P->GetMass() * m_gravity;
		P->Update(_deltaTime, m_force);
		if (!P->GetDead()) { continue; }
		P->Reset();
		Particle::Pool->ReleaseResource(P);
		m_particles.erase(m_particles.begin() + count);
		count--;
	}

	Point p = Renderer::Instance().GetWindowSize();
	glm::vec2 out;
	for (int count = 0; count < m_bodies.size(); count++)
	{
		RigidBody* b = m_bodies[count];
		m_force.y = m_gravity;
		b->Update(_deltaTime, m_force);
		if (b->GetPosition().y >= 200)
		{
			glm::vec2 p = b->GetPosition();
			p.y = 200;
			b->setPosition(p);
			b->SetVelocity(glm::vec2(0, 0));
		}
	}

	if (m_bodies.empty()) { return; }
	for (int c1 = 0; c1 < m_bodies.size() - 1; c1++)
	{
		for (int c2 = c1 + 1; c2 < m_bodies.size(); c2++)
		{
			RigidBody* b1 = m_bodies[c1];
			RigidBody* b2 = m_bodies[c2];
			float dist = glm::distance(b1->GetPosition(), b2->GetPosition());
			if (dist <= 32)
			{
				HandleCollision(b1, b2, dist);
				do
				{
					b1->Update(_deltaTime, glm::vec2{ 0,0 });
					b2->Update(_deltaTime, glm::vec2{ 0,0 });
				} while (glm::distance(b1->GetPosition(), b2->GetPosition()) <= 32);
			}
		}
	}
}

Particle* PhysicsController::AddParticle(glm::vec2 _position, float _lifeTime)
{
	Particle* particle = Particle::Pool->GetResource();
	particle->setPosition(_position);
	particle->SetLifeTime(_lifeTime);
	particle->SetMass(1);
	m_particles.push_back(particle);
	return particle;
}

RigidBody* PhysicsController::AddRigidBody(glm::vec2 _position, glm::vec2 _direction, float _mass)
{
	RigidBody* body = RigidBody::Pool->GetResource();
	body->setPosition(_position);
	body->SetVelocity(_direction);
	body->SetMass(_mass);
	m_bodies.push_back(body);
	return body;
}

string PhysicsController::ToString()
{
	string retVal = "Particles: " + to_string(m_particles.size());
	retVal += " RigidBodies: " + to_string(m_bodies.size());
	return retVal;
}

