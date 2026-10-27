#include "MapBackground.h"
#include "App.h"
#include <string>

int MapBackground::Init(const std::vector<std::any>& args)
{
	if (args.size() > 1)
		return -1;
	const auto* fileName = args.empty() ? nullptr : std::any_cast<std::string>(&args[0]);
	if (!args.empty() && !fileName)
		return -1;
	Destroy();
	if (!g_pApp || m_sprite.Init({fileName ? *fileName : std::string("resource/Background/Background.png")}) < 0)
		return -1;
	m_sprite.SetPosition(0.0F, 0.0F);
	const VEC2i size = m_sprite.GetSize();
	m_sprite.SetScale(
		static_cast<float>(g_pApp->GetScreenWidth()) / size.x,
		static_cast<float>(g_pApp->GetScreenHeight()) / size.y);
	return 0;
}

int MapBackground::Destroy()
{
	m_sprite.Destroy();
	return 0;
}

int MapBackground::Update()
{
	return m_sprite.Update(g_pApp ? g_pApp->GetDeltaSeconds() : 0.0F);
}

int MapBackground::Draw()
{
	return m_sprite.Draw();
}
