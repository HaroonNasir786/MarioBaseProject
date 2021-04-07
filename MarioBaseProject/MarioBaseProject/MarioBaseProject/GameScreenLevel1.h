#pragma once
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include "PowBlock.h"
class Texture2D;
class Character;

class GameScreenLevel1: GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePowBlock();


private:
	Texture2D* m_background_texture;
	Character* my_character;
	Character* my_character2;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenshake();
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	
};

