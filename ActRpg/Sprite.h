#pragma once
#include "glcType.h"
#include "GameComponent.h"

class Sprite : public GameComponent
{
public:
	struct SpriteRect
	{
		int texId {-1};			// texture id
		VEC2i offset{};			// draw offset
		RECT  rc{};				// draw left, top, right, bottom
	};

	explicit Sprite(GameObject& parent) : GameComponent(parent) {}
	virtual ~Sprite();

	// args: {std::string fileName}
	int Init(const std::vector<std::any>& args = {}) override;
	void Destroy() override;
	int Draw() override;

	VEC2i GetSize() const
	{
		return {int(m_rect.rc.right - m_rect.rc.left), int(m_rect.rc.bottom - m_rect.rc.top)};
	}
	const SpriteRect& GetRect() const { return m_rect; }

protected:
	SpriteRect m_rect{};
};

