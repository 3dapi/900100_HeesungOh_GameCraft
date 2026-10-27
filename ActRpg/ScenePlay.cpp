#include "ScenePlay.h"
#include "GameInput.h"
#include "App.h"

ScenePlay::ScenePlay()
{
	m_message = "Scene Play";
}

int ScenePlay::Init()
{
	Destroy();
	m_background = std::make_unique<MapBackground>();
	m_player = std::make_unique<GamePlayer>();
	const VEC2 posPlayer(g_pApp->GetScreenWidth() * 0.5F, g_pApp->GetScreenHeight() * 0.5F);
	if(	m_background->Init() < 0 ||
		m_player->Init({posPlayer, 2.0F}) < 0)
	{
		Destroy();
		return -1;
	}
	return 0;
}

int ScenePlay::Destroy()
{
	if(m_player)
		m_player->Destroy();
	if(m_background)
		m_background->Destroy();
	m_player.reset();
	m_background.reset();
	return 0;
}

int ScenePlay::Render()
{
	if(!m_background || !m_player)
		return -1;
	if(m_background->Draw() < 0)
		return -1;
	return m_player->Draw();
}

int ScenePlay::Update()
{
	auto keyEvent = GetGameInput()->GetKeyState(VK_RIGHT);
	if(keyEvent == EInput::EINPUT_DOWN)
		g_pApp->ChangeScene(GAME_PHASE::SCENE_PLAYRESULT);
	if(m_background->Update() < 0)
		return -1;
	return m_player->Update();
}
