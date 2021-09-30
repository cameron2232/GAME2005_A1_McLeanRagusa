#pragma once
#ifndef __PARTICLE__
#define __PARTICLE__
#include "DisplayObject.h"

class Particle : public DisplayObject
{
public:
	// constructors
	Particle();
	
	// destructor
	~Particle();
	
	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
private:
	float m_gravity;
	bool m_isGrounded;
	float m_force;
	glm::vec2 m_currentDirection;
	double m_currentAngle;
	glm::vec2 m_targetPosition;
	float m_drag;
	double launchAngleDeg = 15.88963;
	float PixelsPerSec = 50;
	glm::vec2 startPos = glm::vec2(75.0f, 500.0f);
	int numPoints = 1500;
	float totalSimDuration = 14.0f;
	float speedAdjustmentRate = 10;
	float elevationRate = 10;
};

#endif /* defined (__OBSTACLE__) */