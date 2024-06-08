#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include "Sprite.h"

namespace Engine {
	
	enum class CharacterState {
		ALIVE,
		DEAD,
		NOTSPAWN
	};

	class BaseCharacter {
	public:
		BaseCharacter(Texture* texture, Shader* shader, Quad* quad);
		~BaseCharacter();
		void Update(float deltaTime);
		void Draw();
		void SetPosition(float x, float y);
		void Spawn();
		vec2 GetPosition();
		Sprite* GetSprite();
		CharacterState GetState();
		void SetHP(int hp);
		int GetHP();
	protected:
		Sprite* sprite;
		CharacterState state;
		vec2 velocity;
		int HP;
	};
}
#endif
