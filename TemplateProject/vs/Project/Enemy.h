#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include "Text.h"
#include "BaseCharacter.h"

namespace Engine {
	class Enemy:public Engine::BaseCharacter
	{
	public:
		Enemy(Texture* texture, Shader* shader, Quad* quad);
		~Enemy();
		void Update(float deltaTime);
		void SetTarget(vector<vec2> targets);
		void SetMaxSpeed(float maxSpeed);
		Text* getText();
		void setText(Text* text);
		void Move(float deltaTime);
	private:
		vec2 Engine::Enemy::Seek();
		string Engine::Enemy::FacingSprite(vec2 position, vec2 target);
		vector<vec2> targets;
		vec2 currentTarget;
		float maxSpeed;
		Text* currentHp;
	};
}
#endif
