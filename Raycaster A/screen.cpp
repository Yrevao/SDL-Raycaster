#include "Draw.h"

void Draw::clear(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(render, r, g, b, a);
	SDL_RenderClear(render);
}

int Draw::getWidth() {
	int width;
	SDL_GetRendererOutputSize(render, &width, NULL);

	return width;
}

int Draw::getHeight() {
	int height;
	SDL_GetRendererOutputSize(render, NULL, &height);
	
	return height;
}
