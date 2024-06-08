#include "Enemy.h"

Engine::Enemy::Enemy(Texture* texture, Shader* shader, Quad* quad) :BaseCharacter(texture, shader, quad)
{
	sprite->SetNumXFrames(96)->SetNumYFrames(1)->AddAnimation("bot-up", 4, 6)
		->AddAnimation("bot-upright", 16, 18)->AddAnimation("bot-right", 28, 30)
		->AddAnimation("bot-downright", 40, 42)->AddAnimation("bot-down", 52, 54)
		->AddAnimation("bot-downleft", 64, 66)->AddAnimation("bot-left", 76, 78)
		->AddAnimation("bot-upleft", 88, 90)->PlayAnim("bot-down")
		->SetScale(3)->SetAnimationDuration(90);
	sprite->SetPosition(1000, 250);
	maxSpeed = 0.0f;
	currentTarget = vec2(0,0);
}

Engine::Enemy::~Enemy()
{
}

void Engine::Enemy::Update(float deltaTime)
{
	if (Engine::CharacterState::ALIVE == state) {
		Move(deltaTime);
	}
	currentHp->SetText(to_string(GetHP()))->SetPosition(GetPosition().x, GetPosition().y + 50)->SetColor(255, 255, 255);

}

Engine::Text* Engine::Enemy::getText() {
	return this->currentHp;
}

void Engine::Enemy::setText(Text* text) {
	this->currentHp = text;
}

void Engine::Enemy::SetTarget(vector<vec2> targets)
{
	this->targets = targets;
}

void Engine::Enemy::SetMaxSpeed(float maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

void Engine::Enemy::Move(float deltaTime)
{
	currentTarget = targets.back();
	if (fabs(this->GetPosition().x - currentTarget.x) <= 5 && fabs(this->GetPosition().y - currentTarget.y) <= 5) {
		if (targets.size() > 1) {
			targets.pop_back();
		}
	}
	vec2 steering = Seek();
	// Update Bot Position based on steeyring behavior
	velocity += steering;
	vec2 position = GetPosition();
	vec2 oldPosition = vec2(position);
	position += velocity * deltaTime;
	SetPosition(position.x, position.y);
	// Update Sprite Animation
	string anim = FacingSprite(oldPosition, position);
	sprite->PlayAnim("bot-"+anim);
	sprite->Update(deltaTime);
}

vec2 Engine::Enemy::Seek() {
	vec2 targetPosition = currentTarget;
	vec2 position = GetPosition();
	vec2 desiredVelocity = normalize(targetPosition - position) * maxSpeed;
	vec2 steering = desiredVelocity - velocity;
	return steering;
}

string Engine::Enemy::FacingSprite(vec2 position, vec2 target)
{
	if (target == position) {
		return "";
	}

	vec2 direction = normalize(target - position);

	float angle = degrees(atan2(direction.y, direction.x));
	if (angle < 0) {
		angle += 360;
	}

	float range = 22.5f;

	if (angle >= (0.0f + range) && angle < (45.0f + range)) {
		return "upright";
	}
	else if (angle >= (45.0f + range) && angle < (90.0f + range)) {
		return "up";
	}
	else if (angle >= (90.0f + range) && angle < (135.0f + range)) {
		return "upleft";
	}
	else if (angle >= (135.0f + range) && angle < (180.0f + range)) {
		return "left";
	}
	else if (angle >= (180.0f + range) && angle < (235.5f + range)) {
		return "downleft";
	}
	else if (angle >= (235.5f + range) && angle < (270.0f + range)) {
		return "down";
	}
	else if (angle >= (270.0f + range) && angle < (315.0f + range)) {
		return "downright";
	}
	else {
		return "right";
	}
}