#pragma once
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
class Texture2D;

class GameScreenLevel1: GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;


private:
	Texture2D* m_background_texture;
	Character* my_character;
	Character* my_character2;
	bool SetUpLevel();
};

