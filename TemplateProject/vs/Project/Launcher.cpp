#include "Setting.h"
#include "Game.h"

#include "GreatDefense.h"

int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->screenWidth = 1600;
	setting->screenHeight = 900;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 75;
	Engine::Game* game = new Engine::GreatDefense(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
