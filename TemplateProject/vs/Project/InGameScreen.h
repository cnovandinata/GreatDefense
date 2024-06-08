#ifndef INGAMESCREEN_H
#define INGAMESCREEN_H

#include "Screen.h"
#include "ScreenManager.h"
#include "Sprite.h"
#include "Text.h"
#include "Enemy.h"
#include "Button.h"
#include "Tower.h"

namespace Engine {
	enum class GameState {
		NORMAL,
		LANE,
		TOWER,
		WAVE
	};
	class InGameScreen :

		public Engine::Screen
	{

	public:
		InGameScreen();
		void Init();
		void Update();
		void Draw();
	private:
		Texture* texture;
		Texture* basetexture, * choices, * lanes, * lanechoices, * towerstex, * explosiontex, * poisontex;
		vector<Sprite*> poisons;
		bool laneoverlap = false;
		Enemy* botSprite;
		vec2 spawn, lanespawn;
		vec2 towerloc;
		vector<Tower*> towers;
		Tower* currentTower;
		int lanechoice1, lanechoice2, lanechosen, towerchosen, rtowerchosen, rot;
		BaseCharacter* baseSprite;
		vector<Button*> buttons;
		vector<Button*> lanebuttons;
		vector<Sprite*> activelanes;
		Sprite* playerSprite, * chooseLaneSprite, * chooseTowerSprite, * chooseRTowerSprite, * Lane1, * Lane2, * Lane3, * ChosenLane, *filter;
		vec2 botVelocity, playerVelocity, currentTarget;
		vector<vec2> targets;
		GameState gamestate;
		vector<Text*>enemyhp;
		Text* hptext;
		Text* currencytext;
		Text* wavetext;
		int towerchoice = 0;
		bool overlap = false;
		bool clear = false;
		int wave = 0;
		float spawnTimer = 0;
		vector<Enemy*> enemies;
		vector<Sprite*>explosions;
		int currency = 0;
		int psnanimtimer = 0;
		int psntimer = 0;
		int hp = 10;
		int currentButtonIndex = 4;
		int currentLaneButtonIndex = 4;
		void StartWave();
		void CreateBaseSprite();
		void CreateLane(int id);
		void CreateChoices();
		void CreateTower(int id);
	};
}

#endif