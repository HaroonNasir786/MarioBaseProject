#include "GameScreen.h"
#include <SDL_image.h>
#include <iostream>
#include "Texture2D.h"
using namespace std;

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;

}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render()
{
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}

void GameScreen::CheckPaused(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_p:
			Mix_PlayChannel(-1, pauseSound, 0);
			paused = !paused;
			break;
		}
		break;
	}
}

void GameScreen::LoadFont()
{
	fontVeryLarge = TTF_OpenFont("Fonts/MarioFont.ttf", 72);
	fontLarge = TTF_OpenFont("Fonts/MarioFont.ttf", 36);
	fontMedium = TTF_OpenFont("Fonts/MarioFont.ttf", 24);
	fontSmall = TTF_OpenFont("Fonts/MarioFont.ttf", 18);

	fontVeryLarge = TTF_OpenFont("Fonts/MarioFont.ttf", 72);
	fontLarge = TTF_OpenFont("Fonts/MarioFont.ttf", 36);
	fontMedium = TTF_OpenFont("Fonts/MarioFont.ttf", 24);
	fontSmall = TTF_OpenFont("Fonts/MarioFont.ttf", 18);

	colorFg = { 255, 255, 255, 255 };
	colorBg = { 0, 0, 0, 255 };
	colorRed = { 240, 102, 102, 255 };
	colorGreen = { 102, 240, 102, 255 };
	colorPink = { 255, 153, 255, 255 };
	colorYellow = { 255, 156, 51, 255 };

	// START
	startTextSurface = TTF_RenderText_Solid(fontMedium, "'ENTER' TO START", colorYellow);
	startText = SDL_CreateTextureFromSurface(m_renderer, startTextSurface);
	SDL_QueryTexture(startText, NULL, NULL, &startTextRect.w, &startTextRect.h);

	SDL_FreeSurface(startTextSurface);
	startTextSurface = nullptr;

	// COPYRIGHT
	copyrightTextSurface = TTF_RenderText_Solid(fontMedium, "©1983. ©1988. ©1999 NINTENDO", colorFg);
	copyrightText = SDL_CreateTextureFromSurface(m_renderer, copyrightTextSurface);
	SDL_QueryTexture(copyrightText, NULL, NULL, &copyrightTextRect.w, &copyrightTextRect.h);

	SDL_FreeSurface(copyrightTextSurface);
	copyrightTextSurface = nullptr;

	// LEVEL 1 - START
	start1TextSurface = TTF_RenderText_Solid(fontLarge, "LEVEL 1 START", colorFg);
	start1Text = SDL_CreateTextureFromSurface(m_renderer, start1TextSurface);
	SDL_QueryTexture(start1Text, NULL, NULL, &start1TextRect.w, &start1TextRect.h);

	SDL_FreeSurface(start1TextSurface);
	start1TextSurface = nullptr;

	// LEVEL 2 - START
	start2TextSurface = TTF_RenderText_Solid(fontLarge, "LEVEL 2 START", colorFg);
	start2Text = SDL_CreateTextureFromSurface(m_renderer, start2TextSurface);
	SDL_QueryTexture(start2Text, NULL, NULL, &start2TextRect.w, &start2TextRect.h);

	SDL_FreeSurface(start2TextSurface);
	start2TextSurface = nullptr;


	// PAUSE
	pauseTextSurface = TTF_RenderText_Solid(fontVeryLarge, "paused", colorFg);
	pauseText = SDL_CreateTextureFromSurface(m_renderer, pauseTextSurface);
	SDL_QueryTexture(pauseText, NULL, NULL, &pauseTextRect.w, &pauseTextRect.h);

	SDL_FreeSurface(pauseTextSurface);
	pauseTextSurface = nullptr;

	// MARIO
	marioTextSurface = TTF_RenderText_Solid(fontMedium, "mario score:", colorRed);
	marioText = SDL_CreateTextureFromSurface(m_renderer, marioTextSurface);
	SDL_QueryTexture(marioText, NULL, NULL, &marioTextRect.w, &marioTextRect.h);

	SDL_FreeSurface(marioTextSurface);
	marioTextSurface = nullptr;

	// MARIO SCORE
	marioScoreString = to_string(marioScore);
	marioScoreTextSurface = TTF_RenderText_Solid(fontSmall, marioScoreString.c_str(), colorFg);
	marioScoreText = SDL_CreateTextureFromSurface(m_renderer, marioScoreTextSurface);
	SDL_QueryTexture(marioScoreText, NULL, NULL, &marioScoreTextRect.w, &marioScoreTextRect.h);

	SDL_FreeSurface(marioScoreTextSurface);
	marioScoreTextSurface = nullptr;

	// LUIGI
	luigiTextSurface = TTF_RenderText_Solid(fontMedium, "luigi score:", colorGreen);
	luigiText = SDL_CreateTextureFromSurface(m_renderer, luigiTextSurface);
	SDL_QueryTexture(luigiText, NULL, NULL, &luigiTextRect.w, &luigiTextRect.h);

	SDL_FreeSurface(luigiTextSurface);
	luigiTextSurface = nullptr;

	// LUIGI SCORE
	luigiScoreString = to_string(luigiScore);
	luigiScoreTextSurface = TTF_RenderText_Solid(fontSmall, luigiScoreString.c_str(), colorFg);
	luigiScoreText = SDL_CreateTextureFromSurface(m_renderer, luigiScoreTextSurface);
	SDL_QueryTexture(luigiScoreText, NULL, NULL, &luigiScoreTextRect.w, &luigiScoreTextRect.h);

	SDL_FreeSurface(luigiScoreTextSurface);
	luigiScoreTextSurface = nullptr;

	//PEACH
		peachTextSurface = TTF_RenderText_Solid(fontLarge, "princess peach has been rescued", colorFg);
	peachText = SDL_CreateTextureFromSurface(m_renderer, peachTextSurface);
	SDL_QueryTexture(peachText, NULL, NULL, &peachTextRect.w, &peachTextRect.h);

	SDL_FreeSurface(peachTextSurface);
	peachTextSurface = nullptr;

	// GAME OVER
	gameOverTextSurface = TTF_RenderText_Solid(fontLarge, "game over", colorFg);
	gameOverText = SDL_CreateTextureFromSurface(m_renderer, gameOverTextSurface);
	SDL_QueryTexture(gameOverText, NULL, NULL, &gameOverTextRect.w, &gameOverTextRect.h);

	SDL_FreeSurface(gameOverTextSurface);
	gameOverTextSurface = nullptr;

	// NEXT LEVEL
	nextLevelTextSurface = TTF_RenderText_Solid(fontSmall, "'ENTER' - LEVEL 2 || 'ESC' - EXIT", colorYellow);
	nextLevelText = SDL_CreateTextureFromSurface(m_renderer, nextLevelTextSurface);
	SDL_QueryTexture(nextLevelText, NULL, NULL, &nextLevelTextRect.w, &nextLevelTextRect.h);

	SDL_FreeSurface(nextLevelTextSurface);
	nextLevelTextSurface = nullptr;

	// ESCAPE
	escapeTextSurface = TTF_RenderText_Solid(fontSmall, "'ENTER' - VIEW SCORES || 'ESC' - EXIT", colorYellow);
	escapeText = SDL_CreateTextureFromSurface(m_renderer, escapeTextSurface);
	SDL_QueryTexture(escapeText, NULL, NULL, &escapeTextRect.w, &escapeTextRect.h);

	SDL_FreeSurface(escapeTextSurface);
	escapeTextSurface = nullptr;

	// EXIT
	exitTextSurface = TTF_RenderText_Solid(fontMedium, "PRESS 'ESC' TO EXIT", colorYellow);
	exitText = SDL_CreateTextureFromSurface(m_renderer, exitTextSurface);
	SDL_QueryTexture(exitText, NULL, NULL, &exitTextRect.w, &exitTextRect.h);

	SDL_FreeSurface(exitTextSurface);
	exitTextSurface = nullptr;
}

void GameScreen::LoadPlayerScores()
{
	// MARIO SCORE
	marioScoreString = to_string(marioScore);
	marioScoreTextSurface = TTF_RenderText_Solid(fontSmall, marioScoreString.c_str(), colorFg);
	marioScoreText = SDL_CreateTextureFromSurface(m_renderer, marioScoreTextSurface);
	SDL_QueryTexture(marioScoreText, NULL, NULL, &marioScoreTextRect.w, &marioScoreTextRect.h);

	SDL_FreeSurface(marioScoreTextSurface);
	marioScoreTextSurface = nullptr;

	// LUIGI SCORE
	luigiScoreString = to_string(luigiScore);
	luigiScoreTextSurface = TTF_RenderText_Solid(fontSmall, luigiScoreString.c_str(), colorFg);
	luigiScoreText = SDL_CreateTextureFromSurface(m_renderer, luigiScoreTextSurface);
	SDL_QueryTexture(luigiScoreText, NULL, NULL, &luigiScoreTextRect.w, &luigiScoreTextRect.h);

	SDL_FreeSurface(luigiScoreTextSurface);
	luigiScoreTextSurface = nullptr;
}

bool GameScreen::LoadAudio()
{
	g_Overworld = Mix_LoadMUS("Music/WorldMusic/Mario.mp3");
	if (g_Overworld == NULL)
	{
		cout << "Failed to load overworld theme! Error: " << Mix_GetError() << endl;
		return false;
	}

	g_Underworld = Mix_LoadMUS("Music/WorldMusic/MarioUnderworld.mp3");
	if (g_Underworld == NULL)
	{
		cout << "Failed to load underworld theme! Error: " << Mix_GetError() << endl;
		return false;
	}

	gameStartSound = Mix_LoadWAV("Music/Character/TitleTheme.wav");
	if (gameStartSound == NULL)
	{
		cout << "Failed to load game start sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	coinSound = Mix_LoadWAV("Music/Character/Coin.wav");
	if (coinSound == NULL)
	{
		cout << "Failed to load coin sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	dieSound = Mix_LoadWAV("Music/Character/Die.wav");
	if (dieSound == NULL)
	{
		cout << "Failed to load die sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	flagpoleSound = Mix_LoadWAV("Music/Character/Flagpole.wav");
	if (flagpoleSound == NULL)
	{
		cout << "Failed to load flagpole sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	gameOverSound = Mix_LoadWAV("Music/Character/GameOver.wav");
	if (gameOverSound == NULL)
	{
		cout << "Failed to load game over sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	pauseSound = Mix_LoadWAV("Music/Character/Pause.wav");
	if (pauseSound == NULL)
	{
		cout << "Failed to load pause sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	startSound = Mix_LoadWAV("Music/Character/LevelStart.wav");
	if (startSound == NULL)
	{
		cout << "Failed to load start sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	kickSound = Mix_LoadWAV("Music/Character/Kick.wav");
	if (kickSound == NULL)
	{
		cout << "Failed to load kick sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	thwompSound = Mix_LoadWAV("Music/Character/thwomp.wav");
	if (thwompSound == NULL)
	{
		cout << "Failed to load kick sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	return false;
}
