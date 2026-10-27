#pragma once
#include <memory>
#include "GameScene.h"
#include "MapBackground.h"
#include "GamePlayer.h"

class ScenePlay: public GameScene
{
public:
	ScenePlay();
	virtual ~ScenePlay() = default;

	int Init() override;
	int Destroy() override;
	int Update() override;
	int Render() override;
protected:
	std::unique_ptr<MapBackground>	m_background	{};
	std::unique_ptr<GamePlayer>		m_player		{};
};

