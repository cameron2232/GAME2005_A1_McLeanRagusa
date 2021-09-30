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
	float getDeltaX();
	float getDeltaY();
	float getDeltaTotalX();
	float getDeltaTotalY();
	glm::vec2 getInitialPos();

	//setters
	void setIsBeingThrown(bool beingThrown);
	void setInitialPos(glm::vec2 pos);
private:
	float m_gravity;
	bool m_isGrounded;
	bool m_isBeingThrown;

	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;

	double launchAngleDeg;
	int spinAngle;
	float initialVelocity;
	int pixelsPerMeter;
	glm::vec2 initialPos;

	float totalFlightTime;
	float deltaX;
	float deltaY;
};

#endif /* defined (__OBSTACLE__) */