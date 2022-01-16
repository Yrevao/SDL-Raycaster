#include "Data.h"

// displace player along it's movement vector by dPos
void Data::playerMove(float dPos) {
	ply.x = ply.x + (cos(ply.ang) * dPos);
	ply.y = ply.y + (sin(ply.ang) * dPos);
}

// make sure angles stay widthin a range of 0 - 2pi radians
float Data::rotClamp(float rot) {
	float crot = fmod(rot, 2.0f * pi);
	if (crot < 0) crot = crot + (2.0f * pi);

	return crot;
}

// preform line-line intersection; t is how far along line a that line b intersected, and u is how far along line b that line a intersected
void Data::lineInt(line a, line b, float *t, float *u) {
	float tTop = (a.x1 - b.x1) * (b.y1 - b.y2) - (a.y1 - b.y1) * (b.x1 - b.x2);
	float tBot = (a.x1 - a.x2) * (b.y1 - b.y2) - (a.y1 - a.y2) * (b.x1 - b.x2);

	float uTop = (a.x1 - a.x2) * (a.y1 - b.y1) - (a.y1 - a.y2) * (a.x1 - b.x1);
	float uBot = (a.x1 - a.x2) * (b.y1 - b.y2) - (a.y1 - a.y2) * (b.x1 - b.x2);

	*t = tTop / tBot;
	*u = -1.0f * uTop / uBot;
}

// find closest wall that a ray intersects with; return parameters of raycast to that wall
Data::wallHit Data::castMap(float x, float y, float rot) {
	wallHit hitData;

	float t = 0;
	float u = 0;
	line unitRay(x, y, x + cos(rot), y + sin(rot));

	for (wall w : map) {
		lineInt(unitRay, w.pos, &t, &u);
		if (t < 0 || u < 0 || u > 1) continue;
		if (t < hitData.dist) {
			hitData.dist = t;
			hitData.tID = w.tID;
			hitData.tw = w.tw;
			hitData.txDist = sqrtf(((w.pos.x2 - w.pos.x1) * (w.pos.x2 - w.pos.x1)) + ((w.pos.y2 - w.pos.y1) * (w.pos.y2 - w.pos.y1))) * u;
		}
	}

	return hitData;
}

// raycast to all sprites sorted by closest to player; return raycast parameters for all sprites that are in player's fov and are not fully occluded by a wall
Data::spriteHits Data::castSprite(float wallDist, float x, float y, float rot) {
	spriteHits hitData;

	float t = 0;
	float u = 0;
	line unitRay(x, y, x + cos(rot), y + sin(rot));

	for (sprite s : spriteMap) {
		float x1 = cos(rotClamp(ply.ang - (pi / 2.0f))) * (s.w / 2.0f) + s.x;
		float y1 = sin(rotClamp(ply.ang - (pi / 2.0f))) * (s.w / 2.0f) + s.y;
		float x2 = cos(rotClamp(ply.ang + (pi / 2.0f))) * (s.w / 2.0f) + s.x;
		float y2 = sin(rotClamp(ply.ang + (pi / 2.0f))) * (s.w / 2.0f) + s.y;
		line spritePlane(x1, y1, x2, y2);


		lineInt(unitRay, spritePlane, &t, &u);
		if (t < 0 || u < 0 || u > 1) continue;
		if (t < wallDist) {
			hitData.dists.push_back(t);
			hitData.txDists.push_back(sqrtf(((spritePlane.x2 - spritePlane.x1) * (spritePlane.x2 - spritePlane.x1)) + ((spritePlane.y2 - spritePlane.y1) * (spritePlane.y2 - spritePlane.y1))) * u);
			hitData.sprites.push_back(s);
		}
	}

	return hitData;
}