#pragma once
using namespace std;
#include "Character.h"

class CharacterPeach : public Character
{
public:
	CharacterPeach(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing);
	~CharacterPeach();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	bool isRescued;

private:
	
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_framedelay;
	int m_currentFrame;

	void AnimatePeach(float deltaTime, SDL_Event e);
};
