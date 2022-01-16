#include "Draw.h"

void Draw::setColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(render, r, g, b, a);
}

void Draw::drawRect(int x, int y, int w, int h) {
	SDL_Rect dRect;
	dRect.x = x;
	dRect.y = y;
	dRect.w = w;
	dRect.h = h;

	
	SDL_RenderFillRect(render, &dRect);
}

void Draw::drawLine(int x1, int y1, int x2, int y2) {
	SDL_RenderDrawLine(render, x1, y1, x2, y2);
}

void Draw::drawBitmap(SDL_Texture* bitmap, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh) {
	SDL_Rect sRect;
	sRect.x = sx;
	sRect.y = sy;
	sRect.w = sw;
	sRect.h = sh;

	SDL_Rect dRect;
	dRect.x = dx;
	dRect.y = dy;
	dRect.w = dw;
	dRect.h = dh;

	SDL_RenderCopy(render, bitmap, &sRect, &dRect);
}