#pragma once

using namespace std;

#include "Character.h"

class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition);
	~CharacterCoin();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	bool GetCollected() { return m_collected; }

private:
	
	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_framedelay;
	int m_currentFrame;

	bool m_collected;
};