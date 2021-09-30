#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Particle.h"
#include "Background.h"
#include "Ground.h"
#include "Button.h"
#include "Label.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void scrollScene();
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	// UI Items
	Button* m_pBackButton;

	Particle* m_pParticle;
	Background* m_pBackground;
	std::vector<Ground*> m_pGround;
};

#endif /* defined (__PLAY_SCENE__) */