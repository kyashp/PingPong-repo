#pragma once
#include "SDL.h"


class GameLoop {
private:
	//System Initialisation
	bool isRunning = false;
	const int WINDOW_WIDTH = 1000;
	const int WINDOW_HEIGHT = 800;
	SDL_Window* win = nullptr;
	SDL_Renderer* ren = nullptr;

	//Paddle Information
	const int PADDLE_HEIGHT = 100;
	const int PADDLE_WIDTH = 20;
	int p1X = 0;
	int p2X = WINDOW_WIDTH - PADDLE_WIDTH;
	int p1Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
	int p2Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
	const int PADDLE_SPEED = 15;
	int p1Yvel = PADDLE_SPEED;
	int p2Yvel = PADDLE_SPEED;


	//Ball information
	const int BALL_SIZE = 10;
	int bX = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
	int bY = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;
	const int BALL_SPEED = 5;
	int bXvel = BALL_SPEED;
	int bYvel = BALL_SPEED;


public:
	GameLoop();
	void init(const char* title, int r, int g, int b);
	bool running() {
		return isRunning;
	}
	void handleEvents(SDL_Event& e);
	void updateBallMove();
	void ballRender();
	void paddleRender();
	void render();
	void clean();
	
};