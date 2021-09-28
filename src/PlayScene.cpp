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
	float dt = Game::Instance().getDeltaTime();
	t += dt;
	updateDisplayList();

	//float x;
	//float y;

	//y = d + sin(t * a) * b;
	//x = c + cos(t * a) * b;

	//m_pExampleSprite->getTransform()->position = glm::vec2(x, y);

	//y = m_pExampleSprite2->getTransform()->position.y + (cos(t * a)) * a * b * dt;
	//x = m_pExampleSprite2->getTransform()->position.x + (-sin(t * a)) * a * b * dt;
	//m_pExampleSprite2->getTransform()->position = glm::vec2(x, y);
	//std::cout << m_pExampleSprite2->getTransform()->position.x << " " << m_pExampleSprite2->getTransform()->position.y << "\n\n";
	m_pExampleSprite->getTransform()->position.x = c + cos(t * a) * b;
	m_pExampleSprite->getTransform()->position.y = d + sin(t * a) * b;

	m_pExampleSprite2->getTransform()->position.x = m_pExampleSprite2->getTransform()->position.x + (-sin(t * a)) * a * b * dt;
	m_pExampleSprite2->getTransform()->position.y = m_pExampleSprite2->getTransform()->position.y + (cos(t * a)) * a * b * dt;
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

	a = 13;
	b = 68;
	c = 200;
	d = 200;

	// Example Sprite
	m_pExampleSprite = new ExampleSprite();
	addChild(m_pExampleSprite);
	m_pExampleSprite->getTransform()->position = glm::vec2(400.0f, 200.0f);

	m_pExampleSprite2 = new ExampleSprite();
	addChild(m_pExampleSprite2);
	m_pExampleSprite2->getTransform()->position = glm::vec2(c + 200, d);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance().changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance().changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	addChild(m_pInstructionsLabel);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::SliderFloat("a", &a, -100.0f, 100.f, "%.3f");
	ImGui::SliderFloat("b", &b, -100.0f, 100.f, "%.3f");
	ImGui::SliderFloat("c", &c, -100.0f, 100.f, "%.3f");
	ImGui::SliderFloat("d", &d, -100.0f, 100.f, "%.3f");
	
	ImGui::End();
}
