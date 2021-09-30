#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	if (m_pParticle->isBeingThrown())
		scrollScene();

	if (CollisionManager::circleAABBCheck(m_pParticle, m_pGround[0]) || CollisionManager::circleAABBCheck(m_pParticle, m_pGround[1]))
		m_pParticle->setIsBeingThrown(false);

	updateDisplayList();	
}

void PlayScene::clean()
{
	removeAllChildren();

}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		m_pParticle->setIsBeingThrown(true);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pBackground = new Background();
	addChild(m_pBackground);

	m_pGround.push_back(new Ground());
	m_pGround.push_back(new Ground(1920, 636));
	for (int i = 0; i < 2; i++)
		addChild(m_pGround[i]);

	m_pParticle = new Particle();

	//Note: Original position is 400, 464. Add these values when calculating placement
	m_pStormTroopers = new StormTroopers();
	m_pStormTroopers->getTransform()->position = m_pParticle->getInitialPos();
	m_pStormTroopers->getTransform()->position.x += 485 * PIXELS_PER_METER, m_pParticle->getInitialPos().y - (m_pStormTroopers->getHeight() / 2) + (m_pParticle->getHeight() / 2);
	addChild(m_pStormTroopers);

	addChild(m_pParticle);

	m_pWookiee = new Wookiee();
	m_pWookiee->getTransform()->position = m_pParticle->getInitialPos();
	m_pWookiee->getTransform()->position.y -= (m_pWookiee->getHeight() / 2) - (m_pParticle->getHeight() / 2);
	addChild(m_pWookiee);
	
	// Example Sprite
	/*m_pExampleSprite = new ExampleSprite();
	addChild(m_pExampleSprite);
	m_pExampleSprite->getTransform()->position = glm::vec2(400.0f, 200.0f);

	m_pExampleSprite2 = new ExampleSprite();
	addChild(m_pExampleSprite2);
	m_pExampleSprite2->getTransform()->position = glm::vec2(c + 200, d);*/

	//// Back Button
	//m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	//m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	//m_pBackButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pBackButton->setActive(false);
	//	TheGame::Instance().changeSceneState(START_SCENE);
	//});

	/*m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);*/

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::scrollScene()
{
	//get the particles change in X and Y
	float deltaX = m_pParticle->getDeltaX();
	float deltaY = m_pParticle->getDeltaY();

	//used to slowly move the background
	int backgroundOffsetX = m_pParticle->getDeltaTotalX() / 75;
	int backgroundOffsetY = m_pParticle->getDeltaTotalY() / 75;

	//updates the background position as the particle moves
	m_pBackground->getTransform()->position = glm::vec2(0 - backgroundOffsetX, (600 - m_pBackground->getHeight()) - backgroundOffsetY);

	//used to prevent the particle's focus from dropping below the ground
	if (m_pGround[0]->getTransform()->position.y - m_pParticle->getTransform()->position.y < 200) {
		deltaY = 0;
	}
	else
		m_pParticle->getTransform()->position.y -= deltaY;

	//keeps the particle in the center of the X axis
	m_pParticle->getTransform()->position.x -= deltaX;

	//updates the initial position as the particle moves (required so that scrolling scene does not mess up results)
	m_pParticle->setInitialPos(glm::vec2(m_pParticle->getInitialPos().x - deltaX, m_pParticle->getInitialPos().y - deltaY));

	//updates the ground scrolling along X
	for (int i = 0; i < m_pGround.size(); i++) {
		m_pGround[i]->getTransform()->position.x -= deltaX;
		m_pGround[i]->getTransform()->position.y -= deltaY;

		if (m_pGround[i]->getTransform()->position.x < -m_pGround[i]->getWidth() / 2) {
			for (int j = 0; j < m_pGround.size(); j++) {
				m_pGround[j]->getTransform()->position.x += m_pGround[j]->getWidth();
			}
		}
	}

	//updates Wookiees position
	m_pWookiee->getTransform()->position.x -= deltaX;
	m_pWookiee->getTransform()->position.y -= deltaY;

	//updates the Stormtroopers position
	m_pStormTroopers->getTransform()->position.x -= deltaX;
	m_pStormTroopers->getTransform()->position.y -= deltaY;
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);
	
	ImGui::End();
}
