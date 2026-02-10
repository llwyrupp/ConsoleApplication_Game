#include "EngineCommon/Engine_Defines.h"
#include "Game/Game.h"

using namespace System; 

int main(void) {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	game.Run();

	return 0;
}