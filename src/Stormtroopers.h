#pragma once
#ifndef __STORMTROOPERS_H__
#define __STORMTROOPERS_H__

#include "DisplayObject.h"

class StormTroopers : public DisplayObject {
public:
	StormTroopers();
	~StormTroopers();

	void draw() override;
	void update() override;
	void clean() override;
};

#endif // !__STORMTROOPERS_H__
