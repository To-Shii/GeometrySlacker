#include "Game.h"
#include "GameManager.h"
#include "GeometryDash.h"

void InitConfig()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Logger::Reset();
}

int main()
{
    InitConfig();
    M_GAME.Launch(new GeometryDash());

	return EXIT_SUCCESS;
}