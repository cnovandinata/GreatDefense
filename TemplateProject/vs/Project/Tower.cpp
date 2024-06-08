#include "Tower.h"

Engine::Tower::Tower(Texture* texture, Shader* shader, Quad* quad, int id) :BaseCharacter(texture, shader, quad)
{
	sprite->SetNumXFrames(1)->SetNumYFrames(11)->AddAnimation("a", 8, 8)
		->AddAnimation("a-dia", 9, 9)->AddAnimation("b-anim", 0, 3)
		->AddAnimation("b-open",4,4)->AddAnimation("p", 5, 5)
		->AddAnimation("s", 6, 6)->AddAnimation("s-dia", 7,7)->PlayAnim("a")
		->SetScale(1)->SetAnimationDuration(90);
	sprite->SetPosition(1000, 250);
	this->id = id;
	Spawn();
}

Engine::Tower::~Tower()
{
	
}

int Engine::Tower::GetId() {
	return this->id;
}

int Engine::Tower::GetTimer() {
	return this->timer;
}


void Engine::Tower::ResetTimer() {
	this->timer = 0;
}

void Engine::Tower::ResetAnimTimer() {
	this->animtimer = 0;
}
void Engine::Tower::SetTarget(Enemy* target) {
	this->target = target;
}
Engine::Enemy* Engine::Tower::GetTarget() {
	return target;
}
void Engine::Tower::Update(float deltaTime)
{
	animtimer += deltaTime;
	timer += deltaTime;
	if (target == nullptr) {
		if (id == 0) {
			sprite->PlayAnim("a");
		}
		if (id == 1) {
			sprite->PlayAnim("b");
		}
		if (id == 2) {
			sprite->PlayAnim("p");
		}
		if (id == 3) {
			sprite->PlayAnim("s");
		}
	}
	if (target != nullptr) {
		FacingSprite(this->GetPosition(), target->GetPosition());
	}
	if (Engine::CharacterState::ALIVE == state) {
		sprite->Update(deltaTime);
	}
}

void Engine::Tower::FacingSprite(vec2 position, vec2 target)
{
	vec2 direction = normalize(target - position);
	
	float angle = degrees(atan2(direction.y, direction.x));
	if (angle < 0) {
		angle += 360;
	}

	float range = 22.5f;
	if(id == 0){
		if (angle >= (0.0f + range) && angle < (45.0f + range)) {
			sprite->PlayAnim("a-dia")->SetRotation(90);
		}
		else if (angle >= (45.0f + range) && angle < (90.0f + range)) {
			sprite->PlayAnim("a")->SetRotation(180);
		}
		else if (angle >= (90.0f + range) && angle < (135.0f + range)) {
			sprite->PlayAnim("a-dia")->SetRotation(180);
		}
		else if (angle >= (135.0f + range) && angle < (180.0f + range)) {
			sprite->PlayAnim("a")->SetRotation(270);
		}
		else if (angle >= (180.0f + range) && angle < (235.5f + range)) {
			sprite->PlayAnim("a-dia")->SetRotation(270);
		}
		else if (angle >= (235.5f + range) && angle < (270.0f + range)) {
			sprite->PlayAnim("a")->SetRotation(0); 
		}
		else if (angle >= (270.0f + range) && angle < (315.0f + range)) {
			sprite->PlayAnim("a-dia")->SetRotation(0);
		}
		else {
			sprite->PlayAnim("a")->SetRotation(90);
		}
	}
	if (id == 1) {
		if (animtimer <= 360) {
			sprite->PlayAnim("b-anim");
		}
		else {
			sprite->PlayAnim("b-open");
		}
	}
	if (id == 2) {
		sprite->PlayAnim("p");
	}
	if (id == 3) {
		if (angle >= (0.0f + range) && angle < (45.0f + range)) {
			sprite->PlayAnim("s-dia")->SetRotation(90);
		}
		else if (angle >= (45.0f + range) && angle < (90.0f + range)) {
			sprite->PlayAnim("s")->SetRotation(180);
		}
		else if (angle >= (90.0f + range) && angle < (135.0f + range)) {
			sprite->PlayAnim("s-dia")->SetRotation(180);
		}
		else if (angle >= (135.0f + range) && angle < (180.0f + range)) {
			sprite->PlayAnim("s")->SetRotation(270);
		}
		else if (angle >= (180.0f + range) && angle < (235.5f + range)) {
			sprite->PlayAnim("s-dia")->SetRotation(270);
		}
		else if (angle >= (235.5f + range) && angle < (270.0f + range)) {
			sprite->PlayAnim("s")->SetRotation(0);
		}
		else if (angle >= (270.0f + range) && angle < (315.0f + range)) {
			sprite->PlayAnim("s-dia")->SetRotation(0);
		}
		else {
			sprite->PlayAnim("s")->SetRotation(90);
		}
	}

}
