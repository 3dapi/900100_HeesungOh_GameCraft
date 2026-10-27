#pragma once
#include <vector>
#include <any>
#include "glcType.h"

class GameObject;

class GameObject
{
public:
	virtual ~GameObject() = default;

	virtual int Init(const std::vector<std::any>& args = {});
	virtual int Destroy();
	virtual int Update();
	virtual int Draw();

	virtual VEC2 GetPosition() const			{ return m_position; }
	virtual void SetPosition(const VEC2& pos)	{ m_position = pos; }

	virtual void SetScale(float scale)			{ m_scale = scale; }
	virtual float GetScale() const				{ return m_scale; }

protected:
	VEC2						m_position	{0.0F, 0.0F};
	float						m_scale		{1.0F};
	GameObject*					m_parent	{};
	std::vector<GameObject*>	m_pChildren;
};

