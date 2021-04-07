#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	
	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete my_character;
	my_character = nullptr;

	delete my_character2;
	my_character2 = nullptr;

	delete m_pow_block;
	m_pow_block = NULL;
}

void GameScreenLevel1::Render()
{

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	
	my_character->Render();
	my_character2->Render();
	m_pow_block->Render();

	
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	UpdatePowBlock();

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

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), my_character->GetCollisionBox())) {
		if (m_pow_block->IsAvailable()) {
			if (my_character->IsJumping()) {
				DoScreenshake();
				m_pow_block->TakeHit();
				my_character->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), my_character2->GetCollisionBox())) {
		if (m_pow_block->IsAvailable()) {
			if (my_character2->IsJumping()) {
				DoScreenshake();
				m_pow_block->TakeHit();
				my_character2->CancelJump();
			}
		}
	}
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

	SetLevelMap();

	//set up player character
	my_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	my_character2 = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(264, 300), m_level_map);

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };


	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}

void GameScreenLevel1::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

}
