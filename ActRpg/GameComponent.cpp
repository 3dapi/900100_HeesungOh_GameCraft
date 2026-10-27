#include "GameComponent.h"
#include "GameObject.h"

GameComponent::GameComponent(GameObject& parent) : m_parent(&parent)
{
}

int GameComponent::Init(const std::vector<std::any>& args)
{
	return 0;
}

VEC2 GameComponent::GetWorldPosition() const
{
	const VEC2 parentPosition = m_parent->GetPosition();
	return VEC2(parentPosition.x + m_position.x, parentPosition.y + m_position.y);
}
