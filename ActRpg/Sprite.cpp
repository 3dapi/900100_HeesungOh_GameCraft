#include <glc2d.h>
#include "Sprite.h"
#include <string>

Sprite::~Sprite()
{
	Sprite::Destroy();
}

int Sprite::Init(const std::vector<std::any>& args)
{
	if (args.size() != 1)
		return -1;
	const auto* fileName = std::any_cast<std::string>(&args[0]);
	if (!fileName || fileName->empty())
		return -1;
	Destroy();
	m_rect.texId = g2_TextureLoad(fileName->c_str());
	if (m_rect.texId < 0)
		return -1;
	m_rect.rc.right = g2_TextureWidth(m_rect.texId);
	m_rect.rc.bottom = g2_TextureHeight(m_rect.texId);
	if (m_rect.rc.right <= 0 || m_rect.rc.bottom <= 0)
	{
		Destroy();
		return -1;
	}
	return 0;
}

void Sprite::Destroy()
{
	if (m_rect.texId >= 0)
		g2_TextureRelease(m_rect.texId);
	m_rect = SpriteRect{};
}

int Sprite::Draw()
{
	if (m_rect.texId < 0)
		return 0;
	const RECT source{m_rect.rc.left, m_rect.rc.top, m_rect.rc.right, m_rect.rc.bottom};
	const VEC2 worldPosition = GetWorldPosition();
	const VEC2 position(worldPosition.x + m_rect.offset.x * m_scale.x,
		worldPosition.y + m_rect.offset.y * m_scale.y);
	return g2_Draw2D(m_rect.texId, &source, &position, &m_scale);
}
