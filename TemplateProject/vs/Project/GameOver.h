#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include <vector>
#include "ScreenManager.h"

namespace Engine {
	class GameOver :
		public Engine::Screen
	{
	public:
		GameOver();
		void Init();
		void Update();
		void Draw();
	private:
		vector<Button*> buttons;
		Text* text;
		int currentButtonIndex = 0;
	};
}

#endif