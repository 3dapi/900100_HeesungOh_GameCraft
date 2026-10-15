#include "GameScene.h"
#include <glc2d.h>

int GameScene::Init()
{
	m_font1 = g2_FontCreate("netmarble Medium", 64);
	return 0;
}

int GameScene::Update()
{
	return 0;
}

int GameScene::Render()
{
	g2_FontDrawText(m_font1, { 10, 10 }, 0xFFFF00FF, "Game Scene");
	return 0;
}