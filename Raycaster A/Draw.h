#pragma once
#include <iostream>
#include <SDL.h>

class Draw { // draw prototypes
public:
	// Data
	SDL_Window* win;
	SDL_Surface* srf;
	SDL_Renderer* render;
	SDL_Texture* wallsBMP;
	SDL_Texture* spritesBMP;

	// Loading and init
	Draw();
	void quit(); // unload everything
	bool loadBitmaps();

	// gfxOut
	void setColor(int r, int g, int b, int a); // set color of primatives
	void drawRect(int x, int y, int w, int h); // draw a simple colored rectangle
	void drawLine(int x1, int y1, int x2, int y2); // draw a line
	void drawBitmap(SDL_Texture* bitmap, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh); // draw a texture with a source and destination rectangle

	// Screen
	void clear(int r, int g, int b, int a);
	int getWidth();
	int getHeight();
};

class txAtlas { // texture atlas
private:
	Draw* curDraw;
	SDL_Texture* atlasBitmap;
public:
	int txW;
	int txH;

	void init(Draw* init_curDraw, SDL_Texture* init_atlasBitmap, int init_txW, int init_txH) {
		curDraw = init_curDraw;
		atlasBitmap = init_atlasBitmap;
		txW = init_txW;
		txH = init_txH;
	}

	void drawAt(int sx, int sy, int x, int y, int w, int h) {
		curDraw->drawBitmap(atlasBitmap, sx * txW, sy * txH, txW, txH, x, y, w, h);
	}
};