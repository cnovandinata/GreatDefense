#ifndef GREATDEFENSE_H
#define GREATDEFENSE_H

#include "Game.h"
#include "Setting.h"
#include "MainMenuScreen.h"
#include "InGameScreen.h"
#include "GameOver.h"
#include "Clear.h"

namespace Engine {
	class GreatDefense :public Engine::Game
	{
	public:
		GreatDefense(Setting* setting);
		~GreatDefense();
		virtual void Init();
		virtual void Update();
		virtual void Render();	
	};
}

#endif

