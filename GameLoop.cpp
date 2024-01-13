#include "GameLoop.h"
#include<iostream>


GameLoop::GameLoop()
{
}

void GameLoop::init(const char* title, int r, int g, int b)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL cannot be initialised. SDL ERROR: %s", SDL_GetError());
	}
	else {
		win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (win == nullptr) {
			printf("Window cannot be initialised. SDL ERROR: %s", SDL_GetError());
		}
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if (ren == nullptr) {
			printf("Renderer cannot be initialised. SDL ERROR: %s", SDL_GetError());
		}
		isRunning = true;
	}
	SDL_SetRenderDrawColor(ren, r, g, b, 255);
}

void GameLoop::handleEvents(SDL_Event& e)
{
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			SDL_Quit();
			exit(0);
		}
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			if (p2Y > 0) {
				p2Y -= p2Yvel;
			}
			break;
		case SDLK_DOWN:
			if (p2Y < WINDOW_HEIGHT - PADDLE_HEIGHT) {
				p2Y += p2Yvel;
			}
			break;
		case SDLK_w:
			if (p1Y > 0) {
				p1Y -= p1Yvel;
			}
			break;
		case SDLK_s:
			if (p1Y < WINDOW_HEIGHT - PADDLE_HEIGHT) {
				p1Y += p1Yvel;
			}
			break;
		default:
			break;
		}
	}
}

void GameLoop::updateBallMove()
{
	bX += bXvel;
	bY += bYvel;

	if (bY<BALL_SIZE || bY>WINDOW_HEIGHT - BALL_SIZE) {
		bYvel = -bYvel;
	}
	
	if ((bX <= PADDLE_WIDTH &&  bY>=p1Y-BALL_SIZE && bY<= p1Y + PADDLE_HEIGHT - BALL_SIZE)|| (bX >= WINDOW_WIDTH-PADDLE_WIDTH && bY>=p2Y -BALL_SIZE && bY <= p2Y + PADDLE_HEIGHT - BALL_SIZE)) {
		bXvel = -bXvel;
	}
	else if(bX>WINDOW_WIDTH||bX<0) {
		bX = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
		bY = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;
	}
}

void GameLoop::ballRender()
{
	updateBallMove();
	SDL_Rect ball{ bX,bY,BALL_SIZE,BALL_SIZE };
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderFillRect(ren, &ball);
}

void GameLoop::paddleRender()
{
	SDL_Rect paddle1{ p1X,p1Y,PADDLE_WIDTH,PADDLE_HEIGHT };
	SDL_SetRenderDrawColor(ren, 100, 0, 0, 255);
	SDL_RenderFillRect(ren, &paddle1);

	SDL_Rect paddle2{ p2X,p2Y,PADDLE_WIDTH,PADDLE_HEIGHT };
	SDL_SetRenderDrawColor(ren, 0, 0, 100, 255);
	SDL_RenderFillRect(ren, &paddle2);

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}

void GameLoop::render()
{
	SDL_RenderClear(ren);
	ballRender();
	paddleRender();
	SDL_RenderPresent(ren);
}

void GameLoop::clean()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}


