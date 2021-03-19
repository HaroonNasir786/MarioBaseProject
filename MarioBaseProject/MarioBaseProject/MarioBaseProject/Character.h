#pragma once
#include "Commons.h"
#include <SDL.h>
#include <iostream>
#include <string>
class Texture2D;


class Character
{

public:
	Character(SDL_Renderer* renderer, std::string LoadFromFile, Vector2D start_position);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	void AddGravity(float deltaTime);
	void Jump();

 protected:
	 SDL_Renderer* m_renderer;
	 Vector2D m_position;
	 Texture2D* m_texture;
	 FACING m_facing_direction;
	 bool m_moving_left;
	 bool m_moving_right;
	 bool m_jumping;
	 bool m_can_jump = true;
	 float m_jump_force;
	 virtual void MoveLeft(float deltaTime);
	 virtual void MoveRight(float deltaTime);


};

