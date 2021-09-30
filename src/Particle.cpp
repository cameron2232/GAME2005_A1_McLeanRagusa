#include "Particle.h"
#include "Util.h"
#include "Game.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include <stdlib.h>

Particle::Particle() : m_gravity(-9.8f), m_isGrounded(false), totalFlightTime(0.0f), initialVelocity(95.0f), pixelsPerMeter(40), launchAngleDeg(45)
{
	TextureManager::Instance().load("../Assets/textures/thermaldetonator.png", "particle");

	auto size = TextureManager::Instance().getTextureSize("particle");
	setWidth(size.x);
	setHeight(size.y);

	getRigidBody()->acceleration = glm::vec2(0.0f, m_gravity);
	m_isBeingThrown = false;

	getTransform()->position = initialPos = glm::vec2(400.0f, 464.0f);

	setType(OBSTACLE);
	getRigidBody()->isColliding = false;
	deltaX = 0;
	deltaY = 0;
}

Particle::~Particle()
= default;

void Particle::draw()
{
	TextureManager::Instance().draw("particle",
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);

	//const float DEG_TO_RADIANDS = (double)M_PI / (double)180.0;

	//float vx = cos(-launchAngleDeg * DEG_TO_RADIANDS) * PixelsPerSec;
	//float vy = cos(-launchAngleDeg * DEG_TO_RADIANDS) * PixelsPerSec;

	//float simTime = 0.0f;
	//float timeStep = totalSimDuration / (float)numPoints;
	//glm::vec2 nextPoint;
	//glm::vec2 lastPoint = glm::vec2(75.0f, 500.0f);

	//for (int i = 0; i < numPoints; i++)
	//{
	//	nextPoint.x = 75.0f + vx * simTime;
	//	nextPoint.y = 450.0f + vy * simTime + 0.5 * 981 * pow(simTime, 2);

	//	//std::cout << "(" << lastPoint.x <<", " << lastPoint.y << ") | (" << nextPoint.x << ", " << nextPoint.y << "\n";
	//	TextureManager::Instance().draw("particle", nextPoint.x, nextPoint.y, 0, 255, true);

	//	simTime += timeStep;
	//}
}

void Particle::update()
{
	//float simTime = 0.0f;
	//float timeStep = totalSimDuration / (float)numPoints;
	//glm::vec2 nextPoint = glm::vec2(75.0f, 500.0f);
	//glm::vec2 lastPoint;
	//
	//for(int i = 0; i < numPoints; i++)
	//{
	//	nextPoint.x = 75.0f - getRigidBody()->velocity.x * simTime;
	//	nextPoint.y = 450.0f - getRigidBody()->velocity.y * simTime + 0.5*981 * pow(simTime, 2);

	//	//std::cout << "(" << lastPoint.x <<", " << lastPoint.y << ") | (" << nextPoint.x << ", " << nextPoint.y << "\n";
	//	TextureManager::Instance().draw("particle", nextPoint.x, nextPoint.y, 0, 255, true);
	//	
	//	simTime += timeStep;
	//}

	if (m_isBeingThrown) {
		getRigidBody()->velocity.x = (initialVelocity * pixelsPerMeter) * cos(Util::Deg2Rad * launchAngleDeg);
		getRigidBody()->velocity.y = (initialVelocity * pixelsPerMeter) * sin(Util::Deg2Rad * launchAngleDeg);

		auto delta = Game::Instance().getDeltaTime();
		totalFlightTime += delta;

		float newXpos = initialPos.x + (getRigidBody()->velocity.x * totalFlightTime);
		float newYpos = initialPos.y - (getRigidBody()->velocity.y * totalFlightTime) - (0.5 * (getRigidBody()->acceleration.y * pixelsPerMeter) * pow(totalFlightTime, 2));

		deltaX = newXpos - getTransform()->position.x;
		deltaY = newYpos - getTransform()->position.y;

		getTransform()->position.x = newXpos;
		getTransform()->position.y = newYpos;
	}
	
	/*if(!m_isGrounded)
	{
		getRigidBody()->velocity.y += getRigidBody()->acceleration.y + m_gravity * 0.025f;
		getRigidBody()->velocity.y = std::min(std::max(getRigidBody()->velocity.y, m_force), m_gravity);
		getTransform()->position.y += getRigidBody()->velocity.y;
		getRigidBody()->acceleration.y = 0.0f;
	}

	if(getTransform()->position.y >= 500.0f)
	{
		m_isGrounded = true;
		getRigidBody()->acceleration.y = 0.0f;
		getTransform()->position.y = 500.0f;
	}
	else
	{
		m_isGrounded = false;
	}*/
}

void Particle::clean()
{
}

bool Particle::isBeingThrown()
{
	return m_isBeingThrown;
}

float Particle::getDeltaX()
{
	return deltaX;
}

float Particle::getDeltaY()
{
	return deltaY;
}

glm::vec2 Particle::getInitialPos()
{
	return initialPos;
}

void Particle::setIsBeingThrown(bool beingThrown)
{
	m_isBeingThrown = beingThrown;
}

void Particle::setInitialPos(glm::vec2 pos)
{
	initialPos = pos;
}
