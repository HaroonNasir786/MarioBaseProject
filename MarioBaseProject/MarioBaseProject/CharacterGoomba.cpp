#include "CharacterGoomba.h"

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing) : Character(renderer, imagePath, startPosition, map)
{
	m_facing_direction = startFacing;
	m_position = startPosition;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterGoomba::~CharacterGoomba()
{
}

void CharacterGoomba::Render()
{
	int left = m_currentFrame * m_single_sprite_w;

	SDL_Rect portionOfSpritesheet = { left, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else if (m_injured)
	{
		m_texture->Render(portionOfSpritesheet, destRect, SDL_FLIP_VERTICAL);
	}
	else
	{
		m_texture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
		AnimateGoomba(deltaTime, e);
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		m_moving_right = false;
		m_moving_left = false;

		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
		{
			FlipRightWayUp();
		}
	}
}

void CharacterGoomba::TakeDamage()
{

}

void CharacterGoomba::Jump()
{
}

void CharacterGoomba::AnimateGoomba(float deltaTime, SDL_Event e)
{
	m_framedelay -= deltaTime;
	if (m_framedelay <= 0.0f)
	{
		m_framedelay = ANIMATION_DELAY;
		m_currentFrame++;

		if (m_currentFrame > 1)
		{
			m_currentFrame = 0;
		}
	}
}

void CharacterGoomba::FlipRightWayUp()
{
}
