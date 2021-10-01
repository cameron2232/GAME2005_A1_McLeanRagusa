#include "Particle.h"
#include "Util.h"
#include "Game.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include <stdlib.h>

Particle::Particle() : m_gravity(-9.8f), m_isGrounded(false), totalFlightTime(0.0f), initialVelocity(95.0f), pixelsPerMeter(40), launchAngleDeg(15.88963), spinAngle(0)
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
	TextureManager::Instance().draw("particle", getTransform()->position.x, getTransform()->position.y, spinAngle, 255, true);
}

void Particle::update()
{
	if (m_isBeingThrown) {
		//updates the angle that the particle is being drawn with, animation purposes only
		spinAngle += 6;

		//apply the PPM scale to the velocity and adjust it according to the x and y axis using COS and SIN
		getRigidBody()->velocity.x = (initialVelocity * pixelsPerMeter) * cos(Util::Deg2Rad * launchAngleDeg);
		getRigidBody()->velocity.y = (initialVelocity * pixelsPerMeter) * sin(Util::Deg2Rad * launchAngleDeg);

		//get the change in time between the previous and current frame, and add it to total time
		auto delta = Game::Instance().getDeltaTime();
		totalFlightTime += delta;

		//using the equations of projectile motion, determine the x and y positions of the particle in motion, and apply the PPM scale to gravity (y acceleration)
		float newXpos = initialPos.x + (getRigidBody()->velocity.x * totalFlightTime);
		float newYpos = initialPos.y - (getRigidBody()->velocity.y * totalFlightTime) - (0.5 * (getRigidBody()->acceleration.y * pixelsPerMeter) * pow(totalFlightTime, 2));

		//determine the change in distance between the previous position and current
		deltaX = newXpos - getTransform()->position.x;
		deltaY = newYpos - getTransform()->position.y;

		//update the particles position
		getTransform()->position.x = newXpos;
		getTransform()->position.y = newYpos;
	}
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

//determine the change of horizontal distance between the particles current position and its initial throwing point
float Particle::getDeltaTotalX()
{
	return getTransform()->position.x - initialPos.x;
}

//determine the change of vertical distance between the particles current position and its initial throwing point
float Particle::getDeltaTotalY()
{
	return getTransform()->position.y - initialPos.y;
}

glm::vec2 Particle::getInitialPos()
{
	return initialPos;
}

float Particle::getInitialVelocity()
{
	return initialVelocity;
}

float Particle::getLaunchAngle()
{
	return launchAngleDeg;
}

float Particle::getGravity()
{
	return getRigidBody()->acceleration.y;
}

float Particle::getTotalFlightTime()
{
	return totalFlightTime;
}

void Particle::setIsBeingThrown(bool beingThrown)
{
	m_isBeingThrown = beingThrown;
}

void Particle::setInitialPos(glm::vec2 pos)
{
	initialPos = pos;
}

void Particle::setInitialVelocity(float vel)
{
	initialVelocity = vel;
}

void Particle::setLaunchAngle(float angle)
{
	launchAngleDeg = angle;
}

void Particle::setGravity(float grav)
{
	getRigidBody()->acceleration.y = grav;
}

void Particle::clearThrownSettings()
{
	spinAngle = 0;
	totalFlightTime = 0;
	deltaX = 0;
	deltaY = 0;
}
