#pragma once
#include "GameScreen.h"
#include "Texture2D.h"

class GameMenu : GameScreen
{
public:
	GameMenu(SDL_Renderer* renderer);
	~GameMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpMenu();
	Texture2D* m_blackBackground;
	Texture2D* m_mario_logo;
};

