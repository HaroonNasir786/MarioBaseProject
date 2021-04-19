#include "GameMenu.h"
#include <iostream>
#include "constants.h"
using namespace std;

GameMenu::GameMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpMenu();
}

GameMenu::~GameMenu()
{
	delete m_blackBackground;
	m_blackBackground = NULL;

	delete m_mario_logo;
	m_mario_logo = NULL;

	// FONTS
	delete fontVeryLarge;
	fontVeryLarge = NULL;

	delete fontLarge;
	fontLarge = NULL;

	delete fontMedium;
	fontMedium = NULL;

	delete fontSmall;
	fontSmall = NULL;

	// SOUNDS
	delete g_Overworld;
	g_Overworld = NULL;

	delete g_Underworld;
	g_Underworld = NULL;

	delete gameStartSound;
	gameStartSound = NULL;

	delete coinSound;
	coinSound = NULL;

	delete dieSound;
	dieSound = NULL;

	delete flagpoleSound;
	flagpoleSound = NULL;

	delete gameOverSound;
	gameOverSound = NULL;

	delete kickSound;
	kickSound = NULL;

	delete thwompSound;
	thwompSound = NULL;

	delete pauseSound;
	pauseSound = NULL;

	delete startSound;
	startSound = NULL;

	delete victorySound;
	victorySound = NULL;


	SDL_DestroyTexture(startText);
	SDL_DestroyTexture(copyrightText);
	SDL_DestroyTexture(start1Text);
	SDL_DestroyTexture(start2Text);
	SDL_DestroyTexture(pauseText);
	SDL_DestroyTexture(marioText);
	SDL_DestroyTexture(marioScoreText);
	SDL_DestroyTexture(luigiText);
	SDL_DestroyTexture(luigiScoreText);
	SDL_DestroyTexture(peachText);
	SDL_DestroyTexture(gameOverText);
	SDL_DestroyTexture(nextLevelText);
	SDL_DestroyTexture(escapeText);
	SDL_DestroyTexture(exitText);
}

void GameMenu::Render()
{
	m_blackBackground->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	m_mario_logo->Render(Vector2D(((SCREEN_WIDTH / 2) - (m_mario_logo->GetWidth() / 2)), 50), SDL_FLIP_NONE);

	startTextRect.x = (SCREEN_WIDTH / 2) - (startTextRect.w / 2);
	startTextRect.y = ((SCREEN_HEIGHT / 2) - (startTextRect.h / 2)) + 60;
	SDL_RenderCopy(m_renderer, startText, NULL, &startTextRect);

	exitTextRect.x = (SCREEN_WIDTH / 2) - (exitTextRect.w / 2);
	exitTextRect.y = ((SCREEN_HEIGHT / 2) - (exitTextRect.h / 2)) + 100;
	SDL_RenderCopy(m_renderer, exitText, NULL, &exitTextRect);

	copyrightTextRect.x = (SCREEN_WIDTH / 2) - (copyrightTextRect.w / 2);
	copyrightTextRect.y = ((SCREEN_HEIGHT / 2) - (copyrightTextRect.h / 2)) + 160;
	SDL_RenderCopy(m_renderer, copyrightText, NULL, &copyrightTextRect);
}


void GameMenu::Update(float deltaTime, SDL_Event e)
{
}

bool GameMenu::SetUpMenu()
{
	LoadFont();
	LoadAudio();

	Mix_PlayChannel(-1, gameStartSound, 0);

	m_mario_logo = new Texture2D(m_renderer);
	if (!m_mario_logo->LoadFromFile("Images/Menu/MarioLogo.png"))
	{
		cout << "Failed to load mario logo!";
		return false;
	}

	m_blackBackground = new Texture2D(m_renderer);
	if (!m_blackBackground->LoadFromFile("Images/Menu/Red.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	return true;
}
