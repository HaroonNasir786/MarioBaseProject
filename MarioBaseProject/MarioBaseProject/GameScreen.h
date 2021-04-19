#pragma once
#include <SDL.h>
#include <string>
#include "SDL_ttf.h"
#include "Commons.h"
#include "Collisions.h"
#include "Constants.h"
#include <SDL_mixer.h>
using namespace std;
class Texture2D;

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void CheckPaused(SDL_Event e);
	bool paused;
	int marioScore;
	int marioSavedPeach;

	int luigiScore;
	int luigiSavedPeach;

	// FONTS
	void LoadFont();
	void LoadPlayerScores();

	TTF_Font* fontVeryLarge;
	TTF_Font* fontLarge;
	TTF_Font* fontMedium;
	TTF_Font* fontSmall;

	SDL_Color colorFg;
	SDL_Color colorBg;
	SDL_Color colorRed;
	SDL_Color colorGreen;
	SDL_Color colorPink;
	SDL_Color colorYellow;

	// Start of level text
	SDL_Surface* startTextSurface;
	SDL_Texture* startText;
	SDL_Rect startTextRect;

	SDL_Surface* copyrightTextSurface;
	SDL_Texture* copyrightText;
	SDL_Rect copyrightTextRect;

	SDL_Surface* start1TextSurface;
	SDL_Texture* start1Text;
	SDL_Rect start1TextRect;

	SDL_Surface* start2TextSurface;
	SDL_Texture* start2Text;
	SDL_Rect start2TextRect;

	SDL_Surface* pauseTextSurface;
	SDL_Texture* pauseText;
	SDL_Rect pauseTextRect;

	// Mario text
	SDL_Surface* marioTextSurface;
	SDL_Texture* marioText;
	SDL_Rect marioTextRect;

	SDL_Surface* marioScoreTextSurface;
	SDL_Texture* marioScoreText;
	SDL_Rect marioScoreTextRect;
	string marioScoreString;


	// Luigi text
	SDL_Surface* luigiTextSurface;
	SDL_Texture* luigiText;
	SDL_Rect luigiTextRect;

	SDL_Surface* luigiScoreTextSurface;
	SDL_Texture* luigiScoreText;
	SDL_Rect luigiScoreTextRect;
	string luigiScoreString;

	// Peach text
	SDL_Surface* peachTextSurface;
	SDL_Texture* peachText;
	SDL_Rect peachTextRect;

	// End of level text
	SDL_Surface* gameOverTextSurface;
	SDL_Texture* gameOverText;
	SDL_Rect gameOverTextRect;

	SDL_Surface* nextLevelTextSurface;
	SDL_Texture* nextLevelText;
	SDL_Rect nextLevelTextRect;

	SDL_Surface* escapeTextSurface;
	SDL_Texture* escapeText;
	SDL_Rect escapeTextRect;

	SDL_Surface* exitTextSurface;
	SDL_Texture* exitText;
	SDL_Rect exitTextRect;

	//Audio 

	bool LoadAudio();

	Mix_Music* g_Overworld;
	Mix_Music* g_Underworld;
	
	bool startTimer;
	float pauseMusic;
	float startGameTimer;

	Mix_Chunk* gameStartSound;
	Mix_Chunk* coinSound;
	Mix_Chunk* dieSound;
	Mix_Chunk* flagpoleSound;
	Mix_Chunk* gameOverSound;
	Mix_Chunk* pauseSound;
	Mix_Chunk* startSound;
	Mix_Chunk* victorySound;
	Mix_Chunk* kickSound;
	Mix_Chunk* thwompSound;

protected:

	SDL_Renderer* m_renderer;

};

