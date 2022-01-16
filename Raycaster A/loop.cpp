#include "Input.h"

void Input::mainLoop() {
	bool quitLoop = false;

	float dPos = 0;
	float dRot = 0;

	while (!quitLoop) {
		while (SDL_PollEvent(&ev) != 0) {
			quitLoop = ev.type == SDL_QUIT; // check for window closes

			if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym) {
				case SDLK_UP:
					dPos = 0.1f;
					break;
				case SDLK_DOWN:
					dPos = -0.1f;
					break;
				case SDLK_LEFT:
					dRot = -0.03f;
					break;
				case SDLK_RIGHT:
					dRot = 0.03f;
					break;
				}
			}
			if (ev.type == SDL_KEYUP) {
				switch (ev.key.keysym.sym) {
				case SDLK_UP:
					dPos = 0;
					break;
				case SDLK_DOWN:
					dPos = 0;
					break;
				case SDLK_LEFT:
					dRot = 0;
					break;
				case SDLK_RIGHT:
					dRot = 0;
					break;
				}
			}

		}
		runData.playerMove(dPos);
		runData.ply.ang += dRot;

		SDL_Delay(1000 / 144);

		// floor / ceiling
		runData.runDraw.setColor(50, 50, 50, 0);
		runData.runDraw.drawRect(0, runData.runDraw.getHeight() / 2, runData.runDraw.getWidth(), 1 + runData.runDraw.getHeight() / 2);
		runData.runDraw.setColor(0, 204, 255, 0);
		runData.runDraw.drawRect(0, 0, runData.runDraw.getWidth(), runData.runDraw.getHeight() / 2);
		
		runData.drawCast();

		SDL_RenderPresent(runData.runDraw.render);
	}

	quit();
}