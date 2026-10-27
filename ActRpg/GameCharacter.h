#pragma once
#include <memory>
#include <vector>
#include "GameObject.h"
#include "Sprite.h"

enum class CharacterState
{
	IDLE, WALK, RUN, ATTACK01, JUMP_RISE, JUMP_LAND, DEAD
};

struct CharacterSprite
{
	CharacterState			state	{};
	std::unique_ptr<Sprite>	sprite	{};
};

class GameCharacter: public GameObject
{
public:
	virtual ~GameCharacter();
	int Destroy() override;
	int Update() override;
	int Draw() override;

	int AddSprite(CharacterState state, std::unique_ptr<Sprite> sprite);
	int SetState(CharacterState state, bool restart = false);
	CharacterState GetState() const { return m_state; }

	virtual int Damage(int damage);
	virtual int Attack(GameCharacter* pMob, int damage)
	{
		return pMob ? pMob->Damage(damage) : -1;
	}
protected:
	Sprite*							m_pSpriteCurrent	{nullptr};
	std::vector<CharacterSprite>	m_pSpriteList				;
	CharacterState					m_state				{CharacterState::IDLE};
};
