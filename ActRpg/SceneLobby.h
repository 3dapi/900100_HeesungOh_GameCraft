#pragma once
#include "GameScene.h"

class SceneLobby : public GameScene
{
public:
	SceneLobby();
	virtual ~SceneLobby() = default;

	int Update() override;
};

