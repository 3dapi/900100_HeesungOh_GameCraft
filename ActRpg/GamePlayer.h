#pragma once
#include "GameCharacter.h"

class GamePlayer : public GameCharacter
{
public:
	// args: {[VEC2 position], [float scale]}
	int Init(const std::vector<std::any>& args = {}) override;
	int Attack(GameCharacter* pMob, int damage) override;
};

