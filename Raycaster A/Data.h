#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <SDL_thread.h>
#include <SDL.h>

#include "Draw.h"

class Data {
public:
	// Running data
	Draw runDraw;
	// textures
	txAtlas wallAtlas;
	txAtlas spriteAtlas;
	// constants / config
	const float pi = 3.141592f;		// pi for math
	float fov = 60 * (pi / 180);	// fov of raycasting

	// data structures
	struct line {
		float x1;
		float y1;
		float x2;
		float y2;
		line(float ix1, float iy1, float ix2, float iy2) {
			x1 = ix1;
			y1 = iy1;
			x2 = ix2;
			y2 = iy2;
		}
	};
	// map
	struct wall {
		line pos = line(0.0f, 0.0f, 0.0f, 0.0f);
		float tw;	// texture width
		int tID;	// texture ID on atlas
		wall(float ix1, float iy1, float ix2, float iy2, float itw, int itID) {
			pos.x1 = ix1;
			pos.y1 = iy1;
			pos.x2 = ix2;
			pos.y2 = iy2;
			tw = itw;
			tID = itID;
		}
	};
	std::vector<wall> map;
	struct wallHit {
		float dist = INFINITY;
		float txDist = 0;
		float tw = 0;
		int tID = 0;
	};
	wallHit castMap(float x, float y, float rot);	// cast 1 ray on the map
	// sprites
	struct sprite {
		float x;
		float y;
		float w;
		float h;
		bool floor;
		float hitBoxSize;
		int tID;
		sprite(float ix, float iy, float iw, float ih, bool ifloor, float ihitBoxSize, int itID) {
			x = ix;
			y = iy;
			w = iw;
			h = ih;
			floor = ifloor;
			hitBoxSize = ihitBoxSize;
			tID = itID;
		}
	};
	std::vector<sprite> spriteMap;
	struct spriteHits {					// used to return raycasting results for sprites
		std::vector<sprite> sprites;	// sprites collided with
		std::vector<float> dists;		// distance to sprites collided with
		std::vector<float> txDists;		// how far into the line the collision occurred
	};
	spriteHits castSprite(float wallDist, float x, float y, float rot);	// ray cast to multiple sprites widthin the current angle
	// viewport location
	struct player {
		float x = 1.5f;
		float y = 1.5f;
		float ang = 0;
	} ply;

	// functions
	Data();												// constructor
	void playerMove(float dPos);						// move player by dPos
	void drawCast();									// draw raycast map; segCount is how many segments and segment is which segment of the rays will be drawn
	void lineInt(line a, line b, float *t, float *u);	// check if two lines intersect, then return distance to line and intersection distance along line
	float rotClamp(float rot);							// keep angle between 0-2pi by finding coterminal angles widthin that range
	void quit();										// unload everything
};

