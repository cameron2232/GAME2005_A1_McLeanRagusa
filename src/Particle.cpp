#include "Particle.h"


#include "SoundManager.h"
#include "TextureManager.h"

Particle::Particle() : m_gravity(9.8f), m_force(-20.0f), m_isGrounded(false)
{
	TextureManager::Instance().load("../Assets/textures/thermaldetonator.png", "particle");

	auto size = TextureManager::Instance().getTextureSize("particle");
	setWidth(size.x);
	setHeight(size.y);

	getRigidBody()->velocity = glm::vec2(95 * cos(15.88963), 95 * sin(15.88963));
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	m_isGrounded = false;

	getTransform()->position = glm::vec2(75.0f, 500.0f);

	setType(OBSTACLE);
	getRigidBody()->isColliding = false;

	m_currentAngle = 15.88963;
	m_drag = 0.88f;

}

Particle::~Particle()
= default;

void Particle::draw()
{
	TextureManager::Instance().draw("particle",
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);

	const float DEG_TO_RADIANDS = (double)M_PI / (double)180.0;

	float vx = cos(-launchAngleDeg * DEG_TO_RADIANDS) * PixelsPerSec;
	float vy = cos(-launchAngleDeg * DEG_TO_RADIANDS) * PixelsPerSec;

	float simTime = 0.0f;
	float timeStep = totalSimDuration / (float)numPoints;
	glm::vec2 nextPoint;
	glm::vec2 lastPoint = glm::vec2(75.0f, 500.0f);

	for (int i = 0; i < numPoints; i++)
	{
		nextPoint.x = 75.0f + vx * simTime;
		nextPoint.y = 450.0f + vy * simTime + 0.5 * 981 * pow(simTime, 2);

		//std::cout << "(" << lastPoint.x <<", " << lastPoint.y << ") | (" << nextPoint.x << ", " << nextPoint.y << "\n";
		TextureManager::Instance().draw("particle", nextPoint.x, nextPoint.y, 0, 255, true);

		simTime += timeStep;
	}
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

	getRigidBody()->velocity.y += getRigidBody()->acceleration.y;
	
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
