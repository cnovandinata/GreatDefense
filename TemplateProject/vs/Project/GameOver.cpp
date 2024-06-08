#include "GameOver.h"

Engine::GameOver::GameOver()
{
	text = NULL;
}

void Engine::GameOver::Init()
{
	// Create a Texture
	Texture* texture = new Texture("buttons.png");


	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(6)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		200);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = (new Text("8-bit Arcade In.ttf", 150, game->GetDefaultTextShader()))
		->SetText("GAME OVER")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 400, game->GetSettings()->screenHeight - 200.0f)->SetColor(235, 229, 52);

}


void Engine::GameOver::Update()
{
	// Set background
	game->SetBackgroundColor(52, 155, 235);

	if (game->GetInputManager()->IsKeyReleased("press")) {
		game->SetState(Engine::State::EXIT);
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}

}

void Engine::GameOver::Draw()
{
	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	text->Draw();
}
