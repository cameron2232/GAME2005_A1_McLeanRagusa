#include "Stormtroopers.h"
#include "TextureManager.h"

StormTroopers::StormTroopers()
{
	TextureManager::Instance().load("../Assets/textures/Stormtroopers.png", "stormtroopers");
	auto size = TextureManager::Instance().getTextureSize("stormtroopers");

	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(0.0f, 0.0f);
}

StormTroopers::~StormTroopers()
{
}

void StormTroopers::draw()
{
	TextureManager::Instance().draw("stormtroopers", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void StormTroopers::update()
{
}

void StormTroopers::clean()
{
}
