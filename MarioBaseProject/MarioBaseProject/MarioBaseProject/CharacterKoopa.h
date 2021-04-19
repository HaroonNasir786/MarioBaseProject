#pragma once
#include "Character.h"
using namespace std;

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();
	void Update(float deltaTime, SDL_Event e);
	void Render();

	void TakeDamage();
	void Jump();

	bool GetAlive() { return isAlive; }
	void SetAlive(bool alive) { isAlive = alive; }

	bool GetInjured() { return m_injured; }

private:

	float m_single_sprite_w;
	float m_single_sprite_h;

	bool m_injured;
	float m_injured_time;

	float m_movement_speed;

	bool isAlive;

	void FlipRightWayUp();
};

