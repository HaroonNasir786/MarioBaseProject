#pragma once

using namespace std;
#include "Character.h"

class CharacterGoomba : public Character
{
public:
	CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing);
	~CharacterGoomba();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void TakeDamage();
	void Jump();

	bool GetInjured() { return m_injured; }

private:
	
	float m_single_sprite_w;
	float m_single_sprite_h;

	bool m_injured;
	float m_injured_time;

	float m_framedelay;
	int m_currentFrame;

	void AnimateGoomba(float deltaTime, SDL_Event e);

	void FlipRightWayUp();
};