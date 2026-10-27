#pragma once
#include <any>
#include <vector>
#include "glcType.h"

class GameObject;

// A component requires an owner. The owner must outlive its components.
class GameComponent
{
public:
	explicit GameComponent(GameObject& parent);
	virtual ~GameComponent() = default;

	virtual int  Init(const std::vector<std::any>& args = {});
	virtual void Destroy() {}
	virtual int  Update(float deltaSeconds = 0.0F) { return 0; }
	virtual int  Draw() = 0;
	virtual void Reset() {}

	GameObject* GetParent() const		{ return m_parent; }
	VEC2 GetPosition() const			{ return m_position; }
	VEC2 GetWorldPosition() const;
	void SetPosition(const VEC2& pos)	{ m_position = pos; }
	void SetPosition(float x, float y)	{ SetPosition(VEC2(x, y)); }
	VEC2 GetScale() const				{ return m_scale; }
	void SetScale(float x, float y)		{ m_scale = VEC2(x, y); }

protected:
	GameObject* const	m_parent	{			}; // Non-owning; assigned once at construction.
	VEC2				m_position	{0.0F, 0.0F}; // Relative to the owner, in screen units.
	VEC2				m_scale		{1.0F, 1.0F};
};
