#include "Character.h"
#include "Texture2D.h"
#include "constants.h"


Character::Character(SDL_Renderer* renderer, std::string LoadFromFile, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;
    m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(LoadFromFile));
	{
		std::cout << "Failed to load background texture!" << std::endl;
		
	}

	m_facing_direction = FACING_RIGHT;

	m_moving_left = false;
	m_moving_right = false;

	m_collision_radius = 15.0f;
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}

}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (!m_jumping){
		AddGravity(deltaTime);
	}
	else {
		//Collided with ground so can jump again
		m_can_jump = true;
	}
	//deal with jumping first
	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::AddGravity(float deltaTime)
{
	if (m_position.y + 64 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}

	else
	{
		m_can_jump = true;
	}
}

void Character::Jump()
{
	if (!m_jumping) {
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = true;
	}
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

void Character::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENTSPEED; 
	m_facing_direction = FACING_LEFT; 
}

void Character::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}
