#pragma once
#include "GameScene.h"

class SceneBegin : public GameScene
{
public:
	SceneBegin();
	virtual ~SceneBegin() = default;

	int Update() override;
};

