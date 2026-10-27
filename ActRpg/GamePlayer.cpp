#include "GameCharacter.h"
#include "GamePlayer.h"
#include "SpriteFlipbook.h"
#include <cstdio>
#include <memory>
#include <string>
#include <utility>

int GamePlayer::Init(const std::vector<std::any>& args)
{
	if (args.size() > 2)
		return -1;
	const auto* position = args.empty() ? nullptr : std::any_cast<VEC2>(&args[0]);
	const auto* scale = args.size() >= 2 ? std::any_cast<float>(&args[1]) : nullptr;

	if ((!args.empty() && !position) || (args.size() >= 2 && !scale))
		return -1;

	Destroy();
	struct AnimationResource
	{
		CharacterState state;
		const char* fileName;
		int width, height;
		float secondsPerFrame;
		bool loop;
	};
	const AnimationResource animations[] =
	{
		{CharacterState::IDLE		, "Idle/Idle-Sheet.png"				, 64, 80, 0.15F, true},
		{CharacterState::RUN		, "Run/Run-Sheet.png"				, 64, 80, 0.08F, true},
		{CharacterState::ATTACK01	, "Attack-01/Attack-01-Sheet.png"	, 64, 80, 0.08F, false},
		{CharacterState::JUMP_RISE	, "Jump-Start/Jump-Start-Sheet.png"	, 64, 64, 0.10F, false},
		{CharacterState::JUMP_LAND	, "Jump-End/Jump-End-Sheet.png"		, 64, 64, 0.10F, false},
		{CharacterState::DEAD		, "Dead/Dead-Sheet.png"			, 64, 64, 0.10F, false}
	};
	// No WALK sheet is supplied. Register one with AddSprite when available.
	for(const auto& animation : animations)
	{
		const std::string path = std::string("resource/Character/Hero2D/") + animation.fileName;
		auto sprite = std::make_unique<SpriteFlipbook>(*this);
		if(sprite->Init({path, animation.width, animation.height,
			animation.secondsPerFrame, animation.loop}) < 0)
		{
			std::fprintf(stderr, "Cannot load animation: %s\n", path.c_str());
			Destroy();
			return -1;
		}
		if(AddSprite(animation.state, std::move(sprite)) < 0)
		{
			Destroy();
			return -1;
		}
	}
	if (position)
		SetPosition(*position);
	if (scale)
		SetScale(*scale);
	return SetState(CharacterState::IDLE);
}

int GamePlayer::Attack(GameCharacter* pMob, int damage)
{
	// 내일을 처리하고

	//
	pMob->Damage(damage);
	return 0;
}
