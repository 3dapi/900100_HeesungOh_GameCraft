#include "GameCharacter.h"
#include "App.h"
#include <utility>

GameCharacter::~GameCharacter()
{
	Destroy();
}

int GameCharacter::Destroy()
{
	m_pSpriteCurrent = nullptr;
	m_pSpriteList.clear();
	m_state = CharacterState::IDLE;
	return 0;
}

int GameCharacter::AddSprite(CharacterState state, std::unique_ptr<Sprite> sprite)
{
	if(!sprite || sprite->GetParent() != this)
		return -1;
	for(const auto& entry : m_pSpriteList)
		if(entry.state == state)
			return -1;
	m_pSpriteList.push_back(CharacterSprite{state, std::move(sprite)});
	return 0;
}

int GameCharacter::SetState(CharacterState state, bool restart)
{
	for(const auto& entry : m_pSpriteList)
	{
		if(entry.state != state)
			continue;
		if(m_pSpriteCurrent != entry.sprite.get() || restart)
		{
			m_state = state;
			m_pSpriteCurrent = entry.sprite.get();
			m_pSpriteCurrent->Reset();
		}
		return 0;
	}
	return -1; // Keep the current state when an animation is unavailable.
}

int GameCharacter::Update()
{
	return m_pSpriteCurrent ? m_pSpriteCurrent->Update(g_pApp ? g_pApp->GetDeltaSeconds() : 0.0F) : 0;
}

int GameCharacter::Draw()
{
	if(!m_pSpriteCurrent)
		return 0;
	m_pSpriteCurrent->SetScale(m_scale, m_scale);

	const VEC2i size = m_pSpriteCurrent->GetSize();
	const VEC2 newPos(-size.x * m_scale * 0.5F, -size.y * m_scale * 0.5F);

	m_pSpriteCurrent->SetPosition(newPos);
	return m_pSpriteCurrent->Draw();
}

int GameCharacter::Damage(int damage)
{
	return 0;
}
