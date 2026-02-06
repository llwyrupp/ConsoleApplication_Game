#include "ClientCommon/Client_Includes.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/FieldLevel/FieldLevel.h"

USING(System)
int main(void) {
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	game.Run();

	return 0;
}