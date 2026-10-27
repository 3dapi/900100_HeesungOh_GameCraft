#include <glc2d.h>
#include <cmath>
#include "SpriteFlipbook.h"

int SpriteFlipbook::Init(const std::vector<std::any>& args)
{
	if (args.size() < 4 || args.size() > 6)
		return -1;
	const auto* frameWidth = std::any_cast<int>(&args[1]);
	const auto* frameHeight = std::any_cast<int>(&args[2]);
	const auto* secondsPerFrame = std::any_cast<float>(&args[3]);
	const auto* loop = args.size() >= 5 ? std::any_cast<bool>(&args[4]) : nullptr;
	const auto* frameCount = args.size() >= 6 ? std::any_cast<int>(&args[5]) : nullptr;
	if (!frameWidth || !frameHeight || !secondsPerFrame ||
		(args.size() >= 5 && !loop) || (args.size() >= 6 && !frameCount))
		return -1;
	if (Sprite::Init({args[0]}) < 0)
		return -1;
	if (SetFrames(*frameWidth, *frameHeight, *secondsPerFrame,
		loop ? *loop : true, frameCount ? *frameCount : 0) < 0)
	{
		Destroy();
		return -1;
	}
	return 0;
}

int SpriteFlipbook::SetFrames(int frameWidth, int frameHeight,
	float secondsPerFrame, bool loop, int frameCount)
{
	if (m_rect.texId < 0 || frameWidth <= 0 || frameHeight <= 0 ||
		!std::isfinite(secondsPerFrame) || secondsPerFrame <= 0 || frameCount < 0)
		return -1;
	const int width = g2_TextureWidth(m_rect.texId);
	const int height = g2_TextureHeight(m_rect.texId);
	if (width <= 0 || height <= 0 || width % frameWidth || height % frameHeight)
		return -1;
	const int columns = width / frameWidth;
	const int rows = height / frameHeight;
	if (frameCount == 0)
		frameCount = columns * rows;
	if (frameCount <= 0 || frameCount > columns * rows)
		return -1;
	m_frames.clear();
	for (int i = 0; i < frameCount; ++i)
	{
		SpriteRect frame{};
		frame.texId = m_rect.texId;
		frame.rc.left = (i % columns) * frameWidth;
		frame.rc.top = (i / columns) * frameHeight;
		frame.rc.right = frame.rc.left + frameWidth;
		frame.rc.bottom = frame.rc.top + frameHeight;
		m_frames.push_back(frame);
	}
	m_secondsPerFrame = secondsPerFrame;
	m_loop = loop;
	Reset();
	return 0;
}

void SpriteFlipbook::Destroy()
{
	m_frames.clear();
	m_frameIndex = 0;
	m_elapsedSeconds = 0;
	m_finished = false;
	Sprite::Destroy();
}

void SpriteFlipbook::Reset()
{
	m_frameIndex = 0;
	m_elapsedSeconds = 0;
	m_finished = false;
	if (!m_frames.empty())
		m_rect = m_frames.front();
}

int SpriteFlipbook::Update(float deltaSeconds)
{
	if (m_frames.empty() || m_finished || !std::isfinite(deltaSeconds) || deltaSeconds <= 0)
		return 0;
	m_elapsedSeconds += deltaSeconds;
	const double duration = m_secondsPerFrame * m_frames.size();
	if (m_loop)
		m_elapsedSeconds = std::fmod(m_elapsedSeconds, duration);
	else if (m_elapsedSeconds >= duration)
	{
		m_elapsedSeconds = duration;
		m_finished = true;
	}
	m_frameIndex = m_finished ? m_frames.size() - 1 :
		static_cast<size_t>(m_elapsedSeconds / m_secondsPerFrame);
	m_rect = m_frames[m_frameIndex];
	return 0;
}
