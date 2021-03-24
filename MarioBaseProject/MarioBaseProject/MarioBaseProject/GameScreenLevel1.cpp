#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete my_character;
	my_character = nullptr;
	delete my_character2;
	my_character2 = nullptr;
}

void GameScreenLevel1::Render()
{

	//draw the background
	m_background_texture->Render(Vector2D(0,0), SDL_FLIP_NONE);
	
	my_character->Render();
	my_character2->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (Collisions::Instance()->Circle(my_character, my_character2))
	{
		cout << "Circle hit!" << endl;
	}

	if (Collisions::Instance()->Box(my_character->GetCollisionBox(), my_character2->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}

	//update character
	my_character->Update(deltaTime, e);
	my_character2->Update(deltaTime, e);



}

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//set up player character
	my_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(65, 445));
	my_character2 = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(50, 445));

	return true;
}
