#include "SDL.h"
#include"GameLoop.h"


GameLoop* game = nullptr;
int main(int argc, char* argv[]) {

	const int frameRate = 60;
	const int frameDelay = 1000 / frameRate;

	SDL_Event e;
	game = new GameLoop();

	game->init("Ping Pong", 0, 0, 0);
	while (game->running()) {

		Uint32 frameStart = SDL_GetTicks();
		game->handleEvents(e);
		game->render();

		int frametime = SDL_GetTicks() - frameStart;

		if (frameDelay > frametime) {
			SDL_Delay(frameDelay - frametime);
		}
	}
	game->clean();
	return 0;
}