
#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	playersDead = false;
	paused = false;
	startTimer = false;
	pauseMusic = MUSIC_TIMER;
	enemyTimer = ENEMY_TIMER;
	startGameTimer = START_TIMER;

	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_overworld_texture;
	m_overworld_texture = NULL;

	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_transparency;
	m_transparency = NULL;

	delete  m_blackBackground;
	m_blackBackground = NULL;

	delete my_character;
	my_character = nullptr;

	delete my_character2;
	my_character2 = nullptr;

	delete characterPeach;
	characterPeach = NULL;

	delete m_pow_block;
	m_pow_block = NULL;

	m_level_map = NULL;

	m_enemies.clear();
	m_coins.clear();
	m_EnemyGoomba.clear();

	// SOUNDS
	delete g_Overworld;
	g_Overworld = NULL;

	delete g_Underworld;
	g_Underworld = NULL;

	delete gameStartSound;
	gameStartSound = NULL;

	delete coinSound;
	coinSound = NULL;

	delete dieSound;
	dieSound = NULL;

	delete flagpoleSound;
	flagpoleSound = NULL;

	delete gameOverSound;
	gameOverSound = NULL;

	delete pauseSound;
	pauseSound = NULL;

	delete startSound;
	startSound = NULL;

	delete victorySound;
	victorySound = NULL;

	delete kickSound;
	kickSound = NULL;

	delete thwompSound;
	thwompSound = NULL;

	// FONTS
	delete fontVeryLarge;
	fontVeryLarge = NULL;

	delete fontLarge;
	fontLarge = NULL;

	delete fontMedium;
	fontMedium = NULL;

	delete fontSmall;
	fontSmall = NULL;

	SDL_DestroyTexture(startText);
	SDL_DestroyTexture(copyrightText);
	SDL_DestroyTexture(start1Text);
	SDL_DestroyTexture(start2Text);
	SDL_DestroyTexture(pauseText);
	SDL_DestroyTexture(marioText);
	SDL_DestroyTexture(marioScoreText);
	SDL_DestroyTexture(luigiText);
	SDL_DestroyTexture(luigiScoreText);
	SDL_DestroyTexture(peachText);
	SDL_DestroyTexture(gameOverText);
	SDL_DestroyTexture(nextLevelText);
	SDL_DestroyTexture(escapeText);
	SDL_DestroyTexture(exitText);
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_overworld_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	
	my_character->Render();
	my_character2->Render();
	m_pow_block->Render();
	characterPeach->Render();

	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	for (int i = 0; i < m_EnemyGoomba.size(); i++)
	{
		m_EnemyGoomba[i]->Render();
	}

	// Render Mario Score
	marioTextRect.x = 75;
	marioTextRect.y = 5;
	SDL_RenderCopy(m_renderer, marioText, NULL, &marioTextRect);
	marioScoreTextRect.x = 187;
	marioScoreTextRect.y = 6;
	SDL_RenderCopy(m_renderer, marioScoreText, NULL, &marioScoreTextRect);

	// Render Luigi Score
	luigiTextRect.x = 321;
	luigiTextRect.y = 5;
	SDL_RenderCopy(m_renderer, luigiText, NULL, &luigiTextRect);
	luigiScoreTextRect.x = 425;
	luigiScoreTextRect.y = 6;
	SDL_RenderCopy(m_renderer, luigiScoreText, NULL, &luigiScoreTextRect);

	if (paused)
	{
		m_transparency->Render(Vector2D(0,0), SDL_FLIP_NONE);

		pauseTextRect.x = (SCREEN_WIDTH / 2) - (pauseTextRect.w / 2);
		pauseTextRect.y = (SCREEN_HEIGHT / 2) - (pauseTextRect.h / 2);
		SDL_RenderCopy(m_renderer, pauseText, NULL, &pauseTextRect);
	}
	else
	{
		if (startGameTimer >= 0.0f)
		{
			m_transparency->Render(Vector2D(0,0), SDL_FLIP_NONE);

			start1TextRect.x = (SCREEN_WIDTH / 2) - (start1TextRect.w / 2);
			start1TextRect.y = (SCREEN_HEIGHT / 2) - (start1TextRect.h / 2);
			SDL_RenderCopy(m_renderer, start1Text, NULL, &start1TextRect);
		}

		if (characterPeach->isRescued)
		{
			m_blackBackground->Render(Vector2D(0,0), SDL_FLIP_NONE);

			peachTextRect.x = (SCREEN_WIDTH / 2) - (peachTextRect.w / 2);
			peachTextRect.y = (SCREEN_HEIGHT / 2) - (peachTextRect.h / 2);
			SDL_RenderCopy(m_renderer, peachText, NULL, &peachTextRect);

			nextLevelTextRect.x = (SCREEN_WIDTH / 2) - (nextLevelTextRect.w / 2);
			nextLevelTextRect.y = ((SCREEN_HEIGHT / 2) - (nextLevelTextRect.h / 2)) + 40;
			SDL_RenderCopy(m_renderer, nextLevelText, NULL, &nextLevelTextRect);
		}

		if (my_character->GetAlive() == false && my_character2->GetAlive() == false && !characterPeach->isRescued)
		{
			m_blackBackground->Render(Vector2D(0,0), SDL_FLIP_NONE);

			gameOverTextRect.x = (SCREEN_WIDTH / 2) - (gameOverTextRect.w / 2);
			gameOverTextRect.y = (SCREEN_HEIGHT / 2) - (gameOverTextRect.h / 2);
			SDL_RenderCopy(m_renderer, gameOverText, NULL, &gameOverTextRect);

			nextLevelTextRect.x = (SCREEN_WIDTH / 2) - (nextLevelTextRect.w / 2);
			nextLevelTextRect.y = ((SCREEN_HEIGHT / 2) - (nextLevelTextRect.h / 2)) + 40;
			SDL_RenderCopy(m_renderer, nextLevelText, NULL, &nextLevelTextRect);
		}
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	startGameTimer -= 1.0f;

	if (startGameTimer <= 0.0f)
	{
		CheckPaused(e);
	}

	if (startGameTimer == 1000.0f)
	{
		Mix_PlayMusic(g_Overworld, -1);
	}

	if (!paused && !characterPeach->isRescued && startGameTimer <= 0.0f)
	{
		if (pauseMusic == MUSIC_TIMER)
		{
			Mix_ResumeMusic();
		}

	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	UpdatePowBlock();

	// Update and spawn the enemy characters.
	enemyTimer -= 0.25f;
	switch ((int)enemyTimer)
	{
	case 15000:
		CreateKoopa(Vector2D(64, 32), FACING_RIGHT, KOOPA_SPEED);
		break;
	case 10000:
		CreateGoomba(Vector2D(414, 32), FACING_LEFT);
		break;
	case 5000:
		CreateGoomba(Vector2D(64, 32), FACING_RIGHT);
		break;
	case 0:
		enemyTimer = ENEMY_TIMER;
		CreateKoopa(Vector2D(414, 32), FACING_LEFT, KOOPA_SPEED);
		break;
	default:
		break;
	}

	if (Collisions::Instance()->Circle(my_character, my_character2))
	{
		cout << "Circle hit!" << endl;
	}

	if (Collisions::Instance()->Box(my_character->GetCollisionBox(), my_character2->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}

	//update character
	my_character->Update(deltaTime, e);
	my_character2->Update(deltaTime, e);
	WallWrapping(my_character);
	WallWrapping(my_character2);

	UpdateEnemies(deltaTime, e);
	UpdateCoin(deltaTime, e);
	UpdateGoombas(deltaTime, e);
	UpdatePeach(deltaTime, e);

	if (my_character->GetAlive() == false && my_character2->GetAlive() == false && playersDead == false)
	{
		Mix_HaltMusic();
		Mix_HaltChannel(-1);
		Mix_PlayChannel(-1, gameOverSound, 0);
		playersDead = true;
	}
	}
	else
	{
		Mix_PauseMusic();
	}
}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), my_character->GetCollisionBox())) {
		if (m_pow_block->IsAvailable()) 
		{
			if (my_character->IsJumping()) 
			{
				Mix_PlayChannel(-1, thwompSound, 0);
				DoScreenshake();
				m_pow_block->TakeHit();
				my_character->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), my_character2->GetCollisionBox())) {
		if (m_pow_block->IsAvailable()) 
		{
			if (my_character2->IsJumping()) 
			{
				Mix_PlayChannel(-1, thwompSound, 0);
				DoScreenshake();
				m_pow_block->TakeHit();
				my_character2->CancelJump();
			}
		}
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();
	LoadFont();
	LoadAudio();

	Mix_PlayChannel(-1, startSound, 0);

	m_blackBackground = new Texture2D(m_renderer);
	if (!m_blackBackground->LoadFromFile("Images/Level1/Red.png"))
	{
		cout << "Failed to load black background texture!";
		return false;
	}

	m_overworld_texture = new Texture2D(m_renderer);
	if (!m_overworld_texture->LoadFromFile("Images/Level1/OverWorld.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Level1/Level1_New.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	m_transparency = new Texture2D(m_renderer);
	if (!m_transparency->LoadFromFile("Images/Transparency.png"))
	{
		cout << "Failed to load transparency image!";
		return false;
	}

	//set up player character
	my_character = new CharacterMario(m_renderer, "Images/Characters/Mario.png", Vector2D(64, 330), m_level_map);
	my_character2 = new CharacterLuigi(m_renderer, "Images/Characters/Luigi.png", Vector2D(414, 342), m_level_map);

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;

	// Create and set coin positions.
	{
		// Bottom-left platform
		CreateCoin(Vector2D(25, 266));
		CreateCoin(Vector2D(89, 266));
		CreateCoin(Vector2D(153, 266));

		// Bottom-right platform
		CreateCoin(Vector2D(345, 266));
		CreateCoin(Vector2D(409, 266));
		CreateCoin(Vector2D(471, 266));

		// Middle-left platform
		CreateCoin(Vector2D(25, 170));

		// Middle platform
		CreateCoin(Vector2D(153, 138));
		CreateCoin(Vector2D(217, 138));
		CreateCoin(Vector2D(281, 138));
		CreateCoin(Vector2D(345, 138));

		// Middle-right platform
		CreateCoin(Vector2D(471, 170));
		CreateGoomba(Vector2D(414, 34), FACING_LEFT);
		CreatePeach(Vector2D(32, 20), FACING_RIGHT);
	}

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };


	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}

void GameScreenLevel1::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->TakeDamage();
	}

	for (int i = 0; i < m_EnemyGoomba.size(); i++)
	{
		m_EnemyGoomba[i]->TakeDamage();
	}

}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}
			//now do the update

			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], my_character))
				{
					if (m_enemies[i]->GetInjured())
					{
						Mix_PlayChannel(-1, kickSound, 0);
						m_enemies[i]->SetAlive(false);

						marioScore += 20;
						LoadPlayerScores();

					}
					else
					{
						Mix_PauseMusic();
						startTimer = true;
						Mix_PlayChannel(-1, dieSound, 0);

						my_character->SetAlive(false);
						my_character->SetPosition(Vector2D(500, 1000));

					}

				}

				else if (Collisions::Instance()->Circle(m_enemies[i], my_character2))
				{
					if (m_enemies[i]->GetInjured())
					{
						Mix_PlayChannel(-1, kickSound, 0);
						m_enemies[i]->SetAlive(false);

						luigiScore += 20;
						LoadPlayerScores();

					}
					else
					{
						Mix_PauseMusic();
						startTimer = true;
						Mix_PlayChannel(-1, dieSound, 0);

						my_character2->SetAlive(false);
						my_character2->SetPosition(Vector2D(500, 1000));


					}
				}

				//if the enemy is no longer alive then schedule it for deletion
				if (!m_enemies[i]->GetAlive())
				{
					enemyIndexToDelete = i;
				}
			}

			//remove dead enemies -1 each update

			if (enemyIndexToDelete != -1)
			{
				m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
			}
		}

	}
}

void GameScreenLevel1::UpdateCoin(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			m_coins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(m_coins[i], my_character))
			{
				if (m_coins[i]->GetCollected())
				{
					my_character->SetAlive(false);
				}
				else
				{
					m_coins[i]->SetAlive(false);
					m_coins[i]->SetPosition(Vector2D(500, 1000));
				}

				Mix_PlayChannel(-1, coinSound, 0);
				marioScore += 10;
				LoadPlayerScores();


			}
				
			if (Collisions::Instance()->Circle(m_coins[i], my_character2))
			{
				if (m_coins[i]->GetCollected())
				{
					my_character2->SetAlive(false);
				}
				else
				{
					m_coins[i]->SetAlive(false);
					m_coins[i]->SetPosition(Vector2D(500, 1000));
				}

				Mix_PlayChannel(-1, coinSound, 0);
				luigiScore += 10;
				LoadPlayerScores();

			}

			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}

		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateGoombas(float deltaTime, SDL_Event e)
{
	if (!m_EnemyGoomba.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_EnemyGoomba.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_EnemyGoomba[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_EnemyGoomba[i]->GetPosition().x < (float)(-m_EnemyGoomba[i]->GetCollisionBox().width * 0.5f) || m_EnemyGoomba[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_EnemyGoomba[i]->GetCollisionBox().width * 0.55f))
					m_EnemyGoomba[i]->SetAlive(false);
			}
			//now do the update

			m_EnemyGoomba[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_EnemyGoomba[i]->GetPosition().y > 300.0f || m_EnemyGoomba[i]->GetPosition().y <= 64.0f) && (m_EnemyGoomba[i]->
				GetPosition().x < 64.0f || m_EnemyGoomba[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_EnemyGoomba[i], my_character))
				{
					if (m_EnemyGoomba[i]->GetInjured())
					{
						Mix_PlayChannel(-1, kickSound, 0);
						m_EnemyGoomba[i]->SetAlive(false);

						marioScore += 20;
						LoadPlayerScores();

					}
					else
					{
						Mix_PauseMusic();
						startTimer = true;
						Mix_PlayChannel(-1, dieSound, 0);

						my_character->SetAlive(false);
						my_character->SetPosition(Vector2D(500, 1000));

					}

				}

				else if (Collisions::Instance()->Circle(m_EnemyGoomba[i], my_character2))
				{
					if (m_EnemyGoomba[i]->GetInjured())
					{
						Mix_PlayChannel(-1, kickSound, 0);
						m_EnemyGoomba[i]->SetAlive(false);

						luigiScore += 20;
						LoadPlayerScores();

					}
					else
					{
						Mix_PauseMusic();
						startTimer = true;
						Mix_PlayChannel(-1, dieSound, 0);

						my_character2->SetAlive(false);
						my_character2->SetPosition(Vector2D(500, 1000));

					}
				}

				//if the enemy is no longer alive then schedule it for deletion
				if (!m_EnemyGoomba[i]->GetAlive())
				{
					enemyIndexToDelete = i;
				}
			}

			//remove dead enemies -1 each update

			if (enemyIndexToDelete != -1)
			{
				m_EnemyGoomba.erase(m_EnemyGoomba.begin() + enemyIndexToDelete);
			}
		}

	}
}

void GameScreenLevel1::UpdatePeach(float deltaTime, SDL_Event e)
{
	characterPeach->Update(deltaTime, e);

	if (!characterPeach->isRescued)
	{
		if (Collisions::Instance()->Circle(characterPeach, my_character))
		{
			Mix_HaltMusic();
			Mix_PlayChannel(-1, flagpoleSound, 0);

			characterPeach->isRescued = true;

			marioSavedPeach += 1;
			marioScore += 50;
			LoadPlayerScores();

		}
		else if (Collisions::Instance()->Circle(characterPeach, my_character2))
		{
			Mix_HaltMusic();
			Mix_PlayChannel(-1, flagpoleSound, 0);

			characterPeach->isRescued = true;

			luigiSavedPeach += 1;
			luigiScore += 50;
			LoadPlayerScores();

		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* characterKoopa = new CharacterKoopa(m_renderer, "Images/Characters/Koopa.png", m_level_map, position, direction, speed);
	m_enemies.push_back(characterKoopa);
}

void GameScreenLevel1::CreateGoomba(Vector2D position, FACING direction)
{
	CharacterGoomba* characterGoomba = new CharacterGoomba(m_renderer, "Images/Characters/GoombaNPC.png", m_level_map, position, direction);
	m_EnemyGoomba.push_back(characterGoomba);
}

void GameScreenLevel1::CreatePeach(Vector2D position, FACING direction)
{
	characterPeach = new CharacterPeach(m_renderer, "Images/Characters/Peach.png", m_level_map, position, direction);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	CharacterCoin* characterCoin = new CharacterCoin(m_renderer, "Images/Characters/Coin.png", m_level_map, position);
	m_coins.push_back(characterCoin);
}

void GameScreenLevel1::WallWrapping(Character* character)
{
	// Right wall collision - wrap left
	if (character->GetPosition().x >= SCREEN_WIDTH - character->GetCollisionBox().width / 3)
	{
		character->SetPosition(Vector2D(0, character->GetPosition().y));
	}

	// Left wall collision - wrap right
	if (character->GetPosition().x < 0)
	{
		character->SetPosition(Vector2D(SCREEN_WIDTH - character->GetCollisionBox().width / 3, character->GetPosition().y));
	}
}


