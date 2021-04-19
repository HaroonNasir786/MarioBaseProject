#include "CharacterPeach.h"

CharacterPeach::CharacterPeach(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing) : Character(renderer, imagePath, startPosition, map)
{
	m_facing_direction = startFacing;
	m_position = startPosition;
	isRescued = false;

	m_single_sprite_w = m_texture->GetWidth();
    m_single_sprite_h = m_texture->GetHeight();
}

CharacterPeach::~CharacterPeach()
{
}

void CharacterPeach::Render()
{
	int left = m_currentFrame * m_single_sprite_w;

	SDL_Rect portionOfSpritesheet = { left, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterPeach::Update(float deltaTime, SDL_Event e)
{

}

void CharacterPeach::AnimatePeach(float deltaTime, SDL_Event e)
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
