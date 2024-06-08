#include "Sprite.h"
#include "BaseCharacter.h"
#include "Enemy.h"
#include "Input.h"

#ifndef TOWER_H
#define TOWER_H

namespace Engine {
	class Tower :public Engine::BaseCharacter
	{
	public:
		Tower(Texture* texture, Shader* shader, Quad* quad, int id);
		~Tower();
		int GetId();
		int GetTimer();
		void ResetTimer();
		void ResetAnimTimer();
		void Update(float deltaTime);
		void SetTarget(Enemy* target);
		Enemy* GetTarget();
	private:
		int id;
		bool open = false;
		int animtimer;
		int timer;
		void Engine::Tower::FacingSprite(vec2 position, vec2 target);
		Enemy* target;
	};
}
#endif
