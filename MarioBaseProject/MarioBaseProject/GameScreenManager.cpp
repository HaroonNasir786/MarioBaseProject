#include "GameScreen.h"
#include "GameMenu.h"
#include "GameScreenLevel1.h"
#include "GameScreenManager.h"
#include <iostream>
#include "GameScreenLevel2.h"
using namespace std;
GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//clear up the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}
	GameMenu* tempScreenMenu;
	GameScreenLevel1* tempScreenLevel1;
	GameScreenLevel2* tempScreenLevel2;


	switch (new_screen)
	{
	case SCREEN_MENU:
		tempScreenMenu = new GameMenu(m_renderer);
		m_current_screen = (GameScreen*)tempScreenMenu;
		tempScreenMenu = NULL;
		break;
	case SCREEN_LEVEL1:
		tempScreenLevel1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreenLevel1;
		tempScreenLevel1 = NULL;
		break;
	case SCREEN_LEVEL2:
		tempScreenLevel2 = new GameScreenLevel2(m_renderer);
		m_current_screen = (GameScreen*)tempScreenLevel2;
		tempScreenLevel2 = NULL;
		break;
	default:
		cout << "Was not able to load any of the game screens!" << endl;
		break;
	}

}
