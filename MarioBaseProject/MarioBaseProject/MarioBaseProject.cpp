#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
using namespace std;
//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
//Function prototypes
bool InitSDL();
void CLoseSDL();
bool Update();
void Render();
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
bool closeGame = false;


int main(int argc, char* args[])
{
	cout << "Mario Bros. Stats Window" << endl;

	//check if sdl was setup correctly
	InitSDL();
	
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
		g_old_time = SDL_GetTicks();
		bool quit = false;
		while (!quit && !closeGame)
		{
			Render();
			quit = Update();
		}

		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		quit = false;
		while (!quit && !closeGame)
		{
			Render();
			quit = Update();
		}

		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL2);
		quit = false;
		while (!quit && !closeGame)
		{
			Render();
			quit = Update();
		}
	CLoseSDL();

	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}

	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}


		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}

			// Initialise SDL_ttf
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialise! SDL_ttf Error: %s\n", TTF_GetError());
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048) < 0)
		{
			cout << "Mixer could not initialise. Error: " << Mix_GetError();
			return false;
		}
	}

	return true;
}

void CLoseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();

	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;


}

bool Update()
{
	// Get the new time.
	Uint32 newTime = SDL_GetTicks();

	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		closeGame = true;
		return true;
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
			Mix_HaltMusic();
			Mix_HaltChannel(-1);
			return true;
			break;
		case SDLK_ESCAPE:
			closeGame = true;
			break;
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		return true;
		break;
	}

	game_screen_manager->Update((float)(newTime - g_old_time) / 1000.0f, e);

	// Set the current time to be the old time.
	g_old_time = newTime;

	return false;
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//update the screen
	SDL_RenderPresent(g_renderer);

	

}


	






