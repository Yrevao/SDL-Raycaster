#include "Data.h"

Data::Data() {
	// initialize
	wallAtlas.init(&runDraw, runDraw.wallsBMP, 1, 8);
	spriteAtlas.init(&runDraw, runDraw.spritesBMP, 1, 8);

	// line based map
	float tw = 1;
	float bw = 1;
	float aID = 0;
	float bID = 1;
	map.push_back(wall(1, 1, 12, 1, tw, aID));
	map.push_back(wall(1, 10, 12, 10, tw, aID));
	map.push_back(wall(1, 1, 1, 10, tw, aID));
	map.push_back(wall(12, 1, 12, 3, tw, aID));
	map.push_back(wall(12, 8, 12, 10, tw, aID));
	map.push_back(wall(12, 3, 17, 3, tw, aID));
	map.push_back(wall(12, 8, 17, 8, tw, aID));
	map.push_back(wall(17, 3, 17, 8, tw, aID));

	map.push_back(wall(12, 5, 13, 5, bw, bID));
	map.push_back(wall(12, 5, 12, 6, bw, bID));
	map.push_back(wall(13, 5, 13, 6, bw, bID));
	map.push_back(wall(12, 6, 13, 6, bw, bID));

	// sprites
	spriteMap.push_back(sprite(4, 4, 0.1f, 0.1f, true, 1, 0));
	spriteMap.push_back(sprite(6, 4, 1, 1, false, 1, 1));
}
void Data::quit() {
	runDraw.quit();
}