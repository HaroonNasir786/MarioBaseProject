#include "CharacterLuigi.h"
#include "constants.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{

}

CharacterLuigi::~CharacterLuigi()
{
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	//Call Update to handle gravity/collision/etc.
	Character::Update(deltaTime, e);


	switch (e.type) {
		//Key Down Events
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			if (m_can_jump)
				Jump();
			break;
		}
		break;

		//Key Up Events
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		}
		break;

	}
}
