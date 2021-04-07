#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition) : Character(renderer, imagePath, startPosition, map)
{

	m_position = startPosition;
	m_collected = false;

	m_currentFrame = 0;
	m_framedelay = ANIMATION_DELAY;

	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::Render()
{
	int left = m_currentFrame * m_single_sprite_w;

	SDL_Rect portionOfSpritesheet = { left, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	m_framedelay -= deltaTime;
	if (m_framedelay <= 0.0f)
	{
		m_framedelay = ANIMATION_DELAY;
		m_currentFrame++;

		if (m_currentFrame  > 2)
		{
			m_currentFrame = 0;
		}
	}
}
