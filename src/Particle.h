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

	//getters
	bool isBeingThrown();

	//setters
	void setIsBeingThrown(bool beingThrown);
private:
	float m_gravity;
	bool m_isGrounded;
	bool m_isBeingThrown;

	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;

	double launchAngleDeg;
	float initialVelocity;
	int pixelsPerMeter;
	glm::vec2 initialPos;

	float totalSimDuration = 14.0f;
	float speedAdjustmentRate = 10;
	float elevationRate = 10;
	float totalFlightTime;
};

#endif /* defined (__OBSTACLE__) */