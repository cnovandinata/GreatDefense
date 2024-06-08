#include "GreatDefense.h"

Engine::GreatDefense::GreatDefense(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "The Great Defense";
}

Engine::GreatDefense::~GreatDefense()
{
}

void Engine::GreatDefense::Init()
{
	GetInputManager()->AddInputMapping("esc", SDLK_ESCAPE);
	GetInputManager()->AddInputMapping("first", SDLK_1);
	GetInputManager()->AddInputMapping("second", SDLK_2);
	GetInputManager()->AddInputMapping("third", SDLK_3);
	GetInputManager()->AddInputMapping("down", SDLK_DOWN)
		->AddInputMapping("up", SDLK_UP)
		->AddInputMapping("left",SDLK_LEFT)
		->AddInputMapping("right",SDLK_RIGHT)
		->AddInputMapping("press", SDLK_RETURN)
		->AddInputMapping("space",SDLK_SPACE);
	Engine::ScreenManager::GetInstance(this)->AddScreen("ingame", new InGameScreen())
		->AddScreen("mainmenu", new MainMenuScreen())->SetCurrentScreen("mainmenu")->AddScreen("gameover",new GameOver())->AddScreen("clear",new Clear());

}

void Engine::GreatDefense::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::GreatDefense::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}





