#pragma once
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "CharacterKoopa.h"
#include <vector>
#include "CharacterCoin.h"
#include "CharacterGoomba.h"
#include "CharacterPeach.h"
#include <vector>
#include <Windows.h>
class Texture2D;
class Character;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	Texture2D* m_background_texture;
	Texture2D* m_underWorld_texture;
	Texture2D* m_transparency;
	Texture2D* m_blackBackground;
	Character* my_character;
	Character* my_character2;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	vector<CharacterKoopa*> m_enemies;
	vector<CharacterCoin*> m_coins;
	vector<CharacterGoomba*> m_EnemyGoomba;
	CharacterPeach* characterPeach;

	bool SetUpLevel();
	void SetLevelMap();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoin(float deltaTime, SDL_Event e);
	void UpdateGoombas(float deltaTime, SDL_Event e);
	void UpdatePeach(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateGoomba(Vector2D position, FACING direction);
	void CreatePeach(Vector2D position, FACING direction);
	void CreateCoin(Vector2D position);
	void WallCollisions(Character* character);
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float enemyTimer;
	bool playersDead;
};

