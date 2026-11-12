#include "Game.h"

Game game;

int main(int argc, char* argv[]) {
	game.Init();
	game.WorldSetup();
	while (game.run) {
		game.Input();
		game.Update();
		game.Render();
	}
	game.Destroy();
	return 0;
}

