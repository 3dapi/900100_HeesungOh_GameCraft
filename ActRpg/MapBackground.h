#pragma once
#include "GameObject.h"
#include "Sprite.h"

class MapBackground : public GameObject
{
public:
	MapBackground() : m_sprite(*this) {}
	// args: {[std::string fileName]}; empty uses the default background.
	int Init(const std::vector<std::any>& args = {}) override;
	int Destroy() override;
	int Update() override;
	int Draw() override;

protected:
	Sprite m_sprite;
};
