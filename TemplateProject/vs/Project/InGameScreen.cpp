#include "InGameScreen.h"

Engine::InGameScreen::InGameScreen() 
{
}

void Engine::InGameScreen::Init()
{
	texture = new Texture("s8dchars.png");
	basetexture = new Texture("Base.png");
	choices = new Texture("icons.png");
	lanes = new Texture("lanes.png");
	lanechoices = new Texture("lanechoices.png");
	towerstex = new Texture("turrets.png");
	explosiontex = new Texture("explode.png");
	poisontex = new Texture("psn.png");
	currency = 12;
	gamestate = GameState::NORMAL;
	towerloc = vec2((game->GetSettings()->screenWidth / 2) - 64, game->GetSettings()->screenHeight / 2 - 64);
	rot = 180;
	CreateBaseSprite();
	hptext = (new Text("8-bit Arcade In.ttf", 20, game->GetDefaultTextShader()))
		->SetText("HP 10")->SetPosition(60, game->GetSettings()->screenHeight - 60)->SetColor(235, 229, 52);
	currencytext = (new Text("8-bit Arcade In.ttf", 20, game->GetDefaultTextShader()))
		->SetText("Currency 10")->SetPosition(60, game->GetSettings()->screenHeight - 80)->SetColor(235, 229, 52);
	wavetext = (new Text("8-bit Arcade In.ttf", 20, game->GetDefaultTextShader()))
		->SetText("Wave 1")->SetPosition(60, game->GetSettings()->screenHeight - 100)->SetColor(235, 229, 52);
	CreateChoices();
	filter = new Sprite(towerstex, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	filter->SetNumXFrames(1)->SetNumYFrames(11)->AddAnimation("normal", 10, 10)->PlayAnim("normal");

	spawn = vec2((game->GetSettings()->screenWidth / 2), game->GetSettings()->screenHeight / 2 - 64);
	lanespawn = vec2((game->GetSettings()->screenWidth / 2) - 64, game->GetSettings()->screenHeight / 2 - 192);
	Button* LaneButton = new Button(chooseLaneSprite, "lane");
	LaneButton->SetPosition((game->GetSettings()->screenWidth / 4), game->GetSettings()->screenHeight / 8);
	buttons.push_back(LaneButton);
	Button* TowerButton = new Button(chooseTowerSprite, "tower");
	TowerButton->SetPosition((game->GetSettings()->screenWidth / 2), game->GetSettings()->screenHeight / 8);
	buttons.push_back(TowerButton);
	Button* RTowerButton = new Button(chooseRTowerSprite, "rtower");
	RTowerButton->SetPosition((game->GetSettings()->screenWidth*3 / 4), game->GetSettings()->screenHeight / 8);
	buttons.push_back(RTowerButton);
	Button* Lane1Button = new Button(Lane1, "lane1");
	Lane1Button->SetPosition((game->GetSettings()->screenWidth / 4), game->GetSettings()->screenHeight / 8);
	lanebuttons.push_back(Lane1Button);
	Button* Lane2Button = new Button(Lane2, "lane2");
	Lane2Button->SetPosition((game->GetSettings()->screenWidth / 2), game->GetSettings()->screenHeight / 8);
	lanebuttons.push_back(Lane2Button);
	Button* Lane3Button = new Button(Lane3, "lane3");
	Lane3Button->SetPosition((game->GetSettings()->screenWidth * 3 / 4), game->GetSettings()->screenHeight / 8);
	lanebuttons.push_back(Lane3Button);
	targets.push_back(vec2(baseSprite->GetPosition().x + 64, baseSprite->GetPosition().y + 64));
	currentButtonIndex = 4;

}

void Engine::InGameScreen::Update()
{
	// Back to main menu
	if (Engine::GameState::NORMAL == gamestate) {
		if (game->GetInputManager()->IsKeyReleased("esc")) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
		}
	
		if (game->GetInputManager()->IsKeyReleased("first")) {
			// Set previous button to normal state
			if (currentButtonIndex != 4) {
				buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
			}
			// Next Button
			if (currentButtonIndex != 0) {
				currentButtonIndex = 0;
				// Set current button to hover state
				buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
			}
			else {
				currentButtonIndex = 4;
			}

		}
		if (game->GetInputManager()->IsKeyReleased("second")) {
			// Set previous button to normal state
			if (currentButtonIndex != 4) {
				buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
			}
			// Next Button
			if (currentButtonIndex != 1) {
				currentButtonIndex = 1;
				// Set current button to hover state
				buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
			}
			else {
				currentButtonIndex = 4;
			}
		}
		if (game->GetInputManager()->IsKeyReleased("third")) {
			// Set previous button to normal state
			if (currentButtonIndex != 4) {
				buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
			}
			// Next Button
			if (currentButtonIndex != 2) {
				currentButtonIndex = 2;
				// Set current button to hover state
				buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
			}
			else {
				currentButtonIndex = 4;
			}
		}

		if (game->GetInputManager()->IsKeyReleased("press")) {
			// Set previous button to normal state
			if (currentButtonIndex == 0) {
				if (currency >= 2) {
					if (!activelanes.empty() && activelanes.front() != nullptr) {
						for (Sprite* l : activelanes) {
							if (lanespawn.x == l->GetPosition().x && lanespawn.y == l->GetPosition().y) {
								laneoverlap = true;
								break;
							}
						}
					}
					if (lanespawn.x == baseSprite->GetPosition().x && lanespawn.y == baseSprite->GetPosition().y)
						laneoverlap = true;
					if (!laneoverlap) {
						gamestate = GameState::LANE;
						lanechoice1 = rand() % 3;
						lanechoice2 = rand() % 3;
						while (lanechoice1 == lanechoice2) {
							lanechoice2 = rand() % 3;
						}
						currency -= 2;
					}
				}
			}
			if (currentButtonIndex == 1) {
				if(currency>=3){
					towerchoice = rand() % 2;
					CreateTower(towerchoice);
					gamestate = GameState::TOWER;
					currency -= 3;
				}
			}
			if (currentButtonIndex == 2) {
				if (currency >= 5) {
					towerchoice = rand() % 2;
					CreateTower(towerchoice + 2);
					gamestate = GameState::TOWER;
					currency -= 5;
				}
			}
			if (currentButtonIndex == 4) {

			}
		}
		if (game->GetInputManager()->IsKeyReleased("space")) {
			StartWave();
			spawnTimer = 3000;
			poisons.clear();
			for (Tower* t : towers) {
				if (t->GetId() == 2) {
					Sprite* psn = new Sprite(poisontex, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
					psn->SetNumXFrames(1)->SetNumYFrames(3)->AddAnimation("spread", 0, 1)
						->AddAnimation("normal", 1, 1)->SetPosition(t->GetPosition().x - 128, t->GetPosition().y - 128)->SetAnimationDuration(100);
					poisons.push_back(psn);
				}
			}
			gamestate = GameState::WAVE;
		}
		for (Button* b : buttons) {
			b->Update(game->GetGameTime());
		}
		
	}
	if (Engine::GameState::LANE == gamestate) {
		if (game->GetInputManager()->IsKeyReleased("esc")) {
			gamestate = GameState::NORMAL;
		}
		if (game->GetInputManager()->IsKeyReleased("first")) {

			if (lanechoice1 == 0 || lanechoice2 == 0) {
				// Set previous button to normal state
				if (currentLaneButtonIndex != 4) {
					lanebuttons[currentLaneButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
				}
				// Next Button
				if (currentLaneButtonIndex != 0) {
					currentLaneButtonIndex = 0;
					// Set current button to hover state
					lanebuttons[currentLaneButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
				}
				else {
					currentButtonIndex = 4;
				}
				CreateLane(0);
			}
		}
		if (game->GetInputManager()->IsKeyReleased("second")) {

			if (lanechoice1 == 1 || lanechoice2 == 1) {
				// Set previous button to normal state
				if (currentLaneButtonIndex != 4) {
					lanebuttons[currentLaneButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
				}
				// Next Button
				if (currentLaneButtonIndex != 1) {
					currentLaneButtonIndex = 1;
					// Set current button to hover state
					lanebuttons[currentLaneButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
				}
				else {
					currentButtonIndex = 4;
				}
				CreateLane(1);
			}
		}
		if (game->GetInputManager()->IsKeyReleased("third")) {

			if (lanechoice1 == 2 || lanechoice2 == 2) {
				// Set previous button to normal state
				if (currentLaneButtonIndex != 4) {
					lanebuttons[currentLaneButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
				}
				// Next Button
				if (currentLaneButtonIndex != 2) {
					currentLaneButtonIndex = 2;
					// Set current button to hover state
					lanebuttons[currentLaneButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
				}
				else {
					currentButtonIndex = 4;
				}
				CreateLane(2);
			}
		}
		if (game->GetInputManager()->IsKeyReleased("press")) {
			if (currentLaneButtonIndex != 4) {
				activelanes.push_back(ChosenLane);
				if (currentLaneButtonIndex == 0) {
					if (rot % 360 == 0) {
						lanespawn.y += 128;
						spawn.y += 128;
					}
					if (rot % 360 == 90) {
						lanespawn.x -= 128;
						spawn.x -= 128;
					}
					if (rot % 360 == 180) {
						lanespawn.y -= 128;
						spawn.y -= 128;
					}
					if (rot % 360 == 270) {

						lanespawn.x += 128;
						spawn.x += 128;
					}
				}
				if (currentLaneButtonIndex == 1) {
					if (rot % 360 == 0) {
						lanespawn.x += 128;
						spawn.y += 64;
						spawn.x += 64;
					}
					if (rot % 360 == 90) {
						lanespawn.y += 128;
						spawn.y += 64;
						spawn.x -= 64;

					}
					if (rot % 360 == 180) {
						lanespawn.x -= 128;
						spawn.y -= 64;
						spawn.x -= 64;
					}
					if (rot % 360 == 270) {
						lanespawn.y -= 128;
						spawn.y -= 64;
						spawn.x += 64;
					}

					rot -= 90;
					rot = rot % 360;
				}
				if (currentLaneButtonIndex == 2) {
					if (rot % 360 == 0) {
						lanespawn.x -= 128;
						spawn.y += 64;
						spawn.x -= 64;
					}
					if (rot % 360 == 90) {
						lanespawn.y -= 128;
						spawn.y -= 64;
						spawn.x -= 64;

					}
					if (rot % 360 == 180) {
						lanespawn.x += 128;
						spawn.y -= 64;
						spawn.x += 64;
					}
					if (rot % 360 == 270) {
						lanespawn.y += 128;
						spawn.y += 64;
						spawn.x += 64;
					}
					rot = rot % 360;
					rot += 90;
				}
				targets.push_back(vec2(ChosenLane->GetPosition().x + 64, ChosenLane->GetPosition().y + 64));
				gamestate = Engine::GameState::NORMAL;
				currentLaneButtonIndex = 4;
			}
		}

		for (Button* b : lanebuttons) {
			b->Update(game->GetGameTime());
		}
	}
	if (Engine::GameState::TOWER == gamestate) {
		overlap = false;
		if (game->GetInputManager()->IsKeyReleased("esc")) {
			gamestate = Engine::GameState::NORMAL;
		}
		if (game->GetInputManager()->IsKeyReleased("up")) {
			towerloc.y += 128;
			currentTower->SetPosition(towerloc.x, towerloc.y);
		}

		if (game->GetInputManager()->IsKeyReleased("down")) {
			towerloc.y -= 128;
			currentTower->SetPosition(towerloc.x, towerloc.y);
		}

		if (game->GetInputManager()->IsKeyReleased("right")) {
			towerloc.x += 128;
			currentTower->SetPosition(towerloc.x, towerloc.y);
		}

		if (game->GetInputManager()->IsKeyReleased("left")) {
			towerloc.x -= 128;
			currentTower->SetPosition(towerloc.x, towerloc.y);
		}
		if (!activelanes.empty() && activelanes.front() != nullptr) {
			for (Sprite* l : activelanes) {
				if (towerloc.x == l->GetPosition().x && towerloc.y == l->GetPosition().y) {
					overlap = true;
					break;
				}
			}
		}
		if (!towers.empty() && towers.front() != nullptr) {
			for (Tower* t : towers) {
				if (towerloc.x == t->GetPosition().x && towerloc.y == t->GetPosition().y) {
					overlap = true;
					break;
				}
			}
		}
		if (towerloc.x == baseSprite->GetPosition().x && towerloc.y == baseSprite->GetPosition().y) {
			overlap = true;
		}
		if (overlap) {
			filter->SetPosition(towerloc.x, towerloc.y);
			filter->Update(game->GetGameTime()
			);
		}
		else {
			if (game->GetInputManager()->IsKeyReleased("press")) {
				towers.push_back(currentTower);
				gamestate = Engine::GameState::NORMAL;

			}
		}
		currentTower->Update(game->GetGameTime());
	}
	if (gamestate == Engine::GameState::WAVE) {
		
		spawnTimer += game->GetGameTime();
		
		if (spawnTimer >= 1750 - 100 * wave) {
			for (Enemy* e : enemies) {
				if (e->GetState() == Engine::CharacterState::NOTSPAWN) {
					e->Spawn();

					spawnTimer = 0;
					break;
				}
			}
		}
		if (!poisons.empty() && poisons.front() != nullptr) {
			psnanimtimer += game->GetGameTime();
			for (Sprite* psn : poisons) {
				psn->Update(game->GetGameTime());
				if (psnanimtimer >= 200) {
					psn->PlayAnim("normal");
				}
			}
		}
		if (!poisons.empty() && poisons.front() != nullptr) {
			psntimer += game->GetGameTime();
			for (Sprite* psn : poisons) {
				if(psntimer >=100){
					for (Enemy* e : enemies) {
						if (e->GetPosition().x >= psn->GetPosition().x && e->GetPosition().x <= psn->GetPosition().x + 384 &&
							e->GetPosition().y >= psn->GetPosition().y && e->GetPosition().y <= psn->GetPosition().y + 384) {
							e->SetHP(e->GetHP() - 1);
						}
					}
					psntimer = 0;
				}
				
			}
		}
		for (Enemy* e : enemies) {
			e->Update(game->GetGameTime());
			if (fabs(e->GetPosition().x - baseSprite->GetPosition().x - 64) <= 5 && fabs(e->GetPosition().y - baseSprite->GetPosition().y - 64) <= 5) {
				e->SetHP(0);
				e->SetPosition(0, 0);
				hp -= 1;
			}
		}
		if (!towers.empty() && towers.front() != nullptr) {
			for (Tower* t : towers) {
				if (t->GetId() == 0 || t->GetId() == 1) {
					for (Enemy* e : enemies) {
						if (e->GetState() == Engine::CharacterState::ALIVE) {
							if (e->GetPosition().x >= t->GetPosition().x - 256 && e->GetPosition().x <= t->GetPosition().x + 384 &&
								e->GetPosition().y >= t->GetPosition().y - 256 && e->GetPosition().y <= t->GetPosition().y + 384) {
								t->SetTarget(e);
								break;
							}
						}
						else {
							t->SetTarget(nullptr);
						}
					}
				}
				if (t->GetId() == 3) {
					for (Enemy* e : enemies) {
						if (e->GetState() == Engine::CharacterState::ALIVE) {
							t->SetTarget(e);
							break;
						}
						else {
							t->SetTarget(nullptr);
						}
					}
				}
			}
		}
		if (!towers.empty() && towers.front() != nullptr) {
			for (Tower* t : towers) {

				t->Update(game->GetGameTime());
				if (t->GetTarget() != nullptr) {
					if (t->GetId() == 0) {
						if (t->GetTimer() >= 300) {
							t->ResetTimer();
							t->GetTarget()->SetHP(t->GetTarget()->GetHP() - 20);
						}
					}
					if (t->GetId() == 1) {
						if (t->GetTimer() >= 250) {
							explosions.clear();
						}
						if (t->GetTimer() >= 750) {
							t->ResetTimer();
							Sprite* explsn = new Sprite(explosiontex, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
							explsn->SetPosition(t->GetTarget()->GetPosition().x, t->GetTarget()->GetPosition().y);
							explosions.push_back(explsn);
							for (Enemy* e : enemies) {
								if (e->GetState() == Engine::CharacterState::ALIVE) {
									if (e->GetPosition().x >= explsn->GetPosition().x - 48 && e->GetPosition().x <= explsn->GetPosition().x + 48 &&
										e->GetPosition().y >= explsn->GetPosition().y - 48 && e->GetPosition().y <= explsn->GetPosition().y + 48) {
										e->SetHP(e->GetHP() - 20);
									}
								}
							}
						}
					}
					if (t->GetId() == 3) {
						if (t->GetTimer() >= 600) {
							t->ResetTimer();
							t->GetTarget()->SetHP(t->GetTarget()->GetHP() - 50);
						}
					}
				}
				
			}
		}

		for (Enemy* e : enemies) {
			clear = true;
			if (e->GetState() == Engine::CharacterState::NOTSPAWN || e->GetState() == Engine::CharacterState::ALIVE) {
				clear = false;
			}
		}
		if (hp == 0) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("gameover");
		}
		if (clear) {
			if(wave<=8){
				wave += 1;
				currency += 6;
				for (Tower* t : towers) {
					t->ResetTimer();
					t->ResetAnimTimer();
				}
				gamestate = Engine::GameState::NORMAL;
			}
			else {

				ScreenManager::GetInstance(game)->SetCurrentScreen("clear");
			}
		}
	}
	
	// Set background
	game->SetBackgroundColor(52, 155, 235);
	hptext->SetText("HP " + to_string(hp));
	wavetext->SetText("Wave " + to_string(wave + 1));
	currencytext->SetText("Currency " + to_string(currency));
	baseSprite->Update(game->GetGameTime());
	if (ChosenLane != nullptr) {
		ChosenLane->Update(game->GetGameTime());
	}
	if (!activelanes.empty() && activelanes.front() != nullptr) {
		for (Sprite* l : activelanes) {
			l->Update(game->GetGameTime());
		}
	}
	

}

void Engine::InGameScreen::Draw()
{
	baseSprite->Draw();

	if (!activelanes.empty() && activelanes.front()!= nullptr) {
		for (Sprite* l : activelanes) {
			l->Draw();
		}
	}
	if (!towers.empty() && towers.front() != nullptr) {
		for (Tower* t : towers) {
			t->Draw();
		}
	}
	if (gamestate == GameState::NORMAL) {
		for (Button* b : buttons) {
			b->Draw();
		}
	}
	if (Engine::GameState::LANE == gamestate) {
		lanebuttons[lanechoice1]->Draw();
		lanebuttons[lanechoice2]->Draw();
		if (lanebuttons[0]->GetButtonState() == Engine::ButtonState::HOVER ||
			lanebuttons[1]->GetButtonState() == Engine::ButtonState::HOVER || 
			lanebuttons[2]->GetButtonState() == Engine::ButtonState::HOVER) {
			ChosenLane->Draw();
		}
	}
	if (Engine::GameState::TOWER == gamestate) {
		currentTower->Draw();
		if (overlap)
			filter->Draw();
	}
	if (Engine::GameState::WAVE == gamestate) {
		for (Enemy* e : enemies) {
			e->Draw();
			if(e->getText()!=nullptr && e->GetState() == Engine::CharacterState::ALIVE)
				e->getText()->Draw();
		}
		if (!poisons.empty() && poisons.front() != nullptr) {
			for (Sprite* psn : poisons) {
				psn->Draw();
			}
		}
		if (!explosions.empty() && explosions.front() != nullptr) {
			for (Sprite* explsn : explosions) {
				explsn->Draw();
			}
		}
	}
	hptext->Draw();
	wavetext->Draw();
	currencytext->Draw();
}



void Engine::InGameScreen::CreateBaseSprite()
{
	baseSprite = new BaseCharacter(basetexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	baseSprite->Spawn();
	baseSprite->SetPosition((game->GetSettings()->screenWidth / 2) - 64, game->GetSettings()->screenHeight / 2 - 64);
}

void Engine::InGameScreen::CreateChoices()
{
	chooseLaneSprite = new Sprite(choices, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	chooseLaneSprite->SetNumXFrames(1)->SetNumYFrames(9)->AddAnimation("normal", 2, 2)->AddAnimation("hover",7,8)->SetAnimationDuration(400);;
	chooseTowerSprite = new Sprite(choices, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	chooseTowerSprite->SetNumXFrames(1)->SetNumYFrames(9)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 5, 6)->SetAnimationDuration(400);;
	chooseRTowerSprite = new Sprite(choices, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	chooseRTowerSprite->SetNumXFrames(1)->SetNumYFrames(9)->AddAnimation("normal", 1, 1)->AddAnimation("hover", 3, 4)->SetAnimationDuration(400);;
	Lane1 = new Sprite(lanechoices, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	Lane1->SetNumXFrames(1)->SetNumYFrames(9)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 1, 2)->SetAnimationDuration(400);;
	Lane2 = new Sprite(lanechoices, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	Lane2->SetNumXFrames(1)->SetNumYFrames(9)->AddAnimation("normal", 3, 3)->AddAnimation("hover", 4, 5)->SetAnimationDuration(400);;
	Lane3 = new Sprite(lanechoices, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	Lane3->SetNumXFrames(1)->SetNumYFrames(9)->AddAnimation("normal", 6, 6)->AddAnimation("hover", 7, 8)->SetAnimationDuration(400);;

}

void Engine::InGameScreen::CreateLane(int laneid) {
	ChosenLane = new Sprite(lanes, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	ChosenLane->SetNumXFrames(1)->SetNumYFrames(3)->AddAnimation("normal", laneid, laneid)->PlayAnim("normal")->SetRotation((rot) % 360);
	ChosenLane->SetPosition(lanespawn.x,lanespawn.y);
}

void Engine::InGameScreen::CreateTower(int towerid) {
	currentTower = new Tower(towerstex, game->GetDefaultSpriteShader(), game->GetDefaultQuad(), towerid);
	currentTower->SetPosition(towerloc.x, towerloc.y);
}


void Engine::InGameScreen::StartWave() {
	enemies.clear();
	for (int i = 0; i < 5 + wave * 2; i++) {
		Enemy* e = new Enemy(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		e->SetPosition(spawn.x, spawn.y);
		e->SetTarget(targets);
		e->SetMaxSpeed(0.05f + 0.005f * wave);
		e->SetHP(200 + wave * 30);
		Text* ehp = new Text("8-bit Arcade In.ttf", 25, game->GetDefaultTextShader());
		ehp->SetText(to_string(e->GetHP()))->SetPosition(e->GetPosition().x + 20, e->GetPosition().y + 50)->SetColor(255, 255, 255);
		e->setText(ehp);
		enemies.push_back(e);
	}
}




