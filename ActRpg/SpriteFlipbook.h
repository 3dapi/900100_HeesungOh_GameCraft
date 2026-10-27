#pragma once
#include <vector>
#include "Sprite.h"

class SpriteFlipbook : public Sprite
{
public:
	explicit SpriteFlipbook(GameObject& parent) : Sprite(parent) {}

	// Split a regular sheet left-to-right, then top-to-bottom; zero count uses all cells.
	// args: {std::string fileName, int width, int height, float secondsPerFrame,
	//        [bool loop = true], [int frameCount = 0]}
	int Init(const std::vector<std::any>& args = {}) override;
	int		SetFrames(int frameWidth, int frameHeight, float secondsPerFrame, bool loop = true, int frameCount = 0);
	void	Destroy() override;
	void	Reset() override;
	int		Update(float deltaSeconds = 0.0F) override;
	bool	IsFinished() const { return m_finished; }
	size_t	GetFrameIndex() const { return m_frameIndex; }
	const std::vector<SpriteRect>&
			GetFrames() const { return m_frames; }

protected:
	std::vector<SpriteRect> m_frames;
	size_t					m_frameIndex		{};
	double					m_elapsedSeconds	{};
	double					m_secondsPerFrame	{0.1};
	bool					m_loop				{true};
	bool					m_finished			{};
};
