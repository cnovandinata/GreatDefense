#include "BaseCharacter.h"

Engine::BaseCharacter::BaseCharacter(Texture* texture, Shader* shader, Quad* quad)
{
	this->sprite = new Sprite(texture, shader, quad);

	state = Engine::CharacterState::NOTSPAWN;
}

Engine::BaseCharacter::~BaseCharacter()
{
	delete sprite;
}

void Engine::BaseCharacter::Update(float deltaTime)
{
	sprite->Update(deltaTime);
}

int Engine::BaseCharacter::GetHP() {
	return this->HP;
}
void Engine::BaseCharacter::Draw()
{
	if (Engine::CharacterState::ALIVE == state) {
		sprite->Draw();
	}
}

void Engine::BaseCharacter::Spawn() {
	state = Engine::CharacterState::ALIVE;
}
void Engine::BaseCharacter::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

vec2 Engine::BaseCharacter::GetPosition()
{
	return sprite->GetPosition();
}

Engine::Sprite* Engine::BaseCharacter::GetSprite()
{
	return sprite;
}

Engine::CharacterState Engine::BaseCharacter::GetState() {
	return state;
}

void Engine::BaseCharacter::SetHP(int hp)
{
	this->HP = hp;
	if (this->HP <= 0) {
		state = Engine::CharacterState::DEAD;
	}
}






