#include "GameTime.h"
#include <chrono>

using namespace std;

int GameTime::Init()
{
	//begintime		= chrono::system_clock::now() 에서 캐스팅
	eplapsedTime	= {};
	deltaTime		= {};			// millisecond
	return 0;
}

int GameTime::Update()
{
	// 이거 업데이트
	eplapsedTime = {};
	deltaTime = {};			// millisecond
	return 0;
}