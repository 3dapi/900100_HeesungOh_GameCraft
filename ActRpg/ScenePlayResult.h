#pragma once
#include "GameScene.h"

class ScenePlayResult : public GameScene
{
public:
	ScenePlayResult();
	virtual ~ScenePlayResult() = default;

	int Update() override;
};

