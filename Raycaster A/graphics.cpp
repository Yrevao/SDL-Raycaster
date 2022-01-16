#include "Data.h"

void Data::drawCast() {
	int lineWidth = 2;													// width of drawn vertical scan lines
	int rX = runDraw.getWidth();										// max x based on render
	int rY = runDraw.getHeight();										// max y
	float inc = (fov * lineWidth) / rX;									// angle increments based on fov
	float ang = (ply.ang - (fov / 2));									// starting angle of draw loop
	int wallMaxH = rY;													// height coef for walls
	int spriteMaxH = rY;												// height coef for walls

	spriteHits spriteData;												// sprites hit with raycast
	wallHit mapData;													// map elements hit


	// selection sort the sprites by distance so they don't overlap when drawn
	for (int i = 0; i < spriteMap.size(); i++) {
		int highest = i;
		float dist = sqrt(((spriteMap[highest].x - ply.x) * (spriteMap[highest].x - ply.x)) + ((spriteMap[highest].y - ply.y) * (spriteMap[highest].y - ply.y)));
		for (int j = i + 1; j < spriteMap.size(); j++)
			if (sqrt(((spriteMap[j].x - ply.x) * (spriteMap[j].x - ply.x)) + ((spriteMap[j].y - ply.y) * (spriteMap[j].y - ply.y))) > dist) highest = j;

		sprite buffer = spriteMap[highest];
		spriteMap[highest] = spriteMap[i];
		spriteMap[i] = buffer;
	}

	// raycast and draw to every x coordinate of the screen
	for (int i = 0; i < rX; i += lineWidth) {
		// walls
		mapData = castMap(ply.x, ply.y, ang);
		float h = wallMaxH / (cos(ang - ply.ang) * mapData.dist);

		wallAtlas.drawAt(((int)(mapData.txDist * (wallAtlas.txH / mapData.tw))) % wallAtlas.txH, mapData.tID, i, (rY / 2) - (h / 2), lineWidth, h);

		// sprites
		spriteData = castSprite(mapData.dist, ply.x, ply.y, ang);
		for (int j = 0; j < spriteData.sprites.size(); j++) {
			float sh = spriteMaxH / (cos(ang - ply.ang) * spriteData.dists[j]);	// height of sprite on screen

			float sy = (rY / 2) - (sh / 2);
			if(spriteData.sprites[j].floor) sy = (rY / 2) + (sh / 2);

			spriteAtlas.drawAt(
				(int)((float)spriteAtlas.txH * (spriteData.txDists[j] / spriteData.sprites[j].w)),
				spriteData.sprites[j].tID,
				i,
				sy,
				lineWidth,
				sh * spriteData.sprites[j].h);
		}

		ang += inc;
	}
}