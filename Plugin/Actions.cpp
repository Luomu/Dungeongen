// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////////////
//Generate the dungeon. Opts have been set previously.
long ExtObject::aGenerate(LPVAL params)
{
	dungeon = new JBDungeon(options);
	dungeon->expand();
	return 0;
}

void ExtObject::drawDoor(const int x, const int y, const int doorType,
						 const int horiz, CRunLayer* layer)
{
	CRunObject* obj = 0;
	CRunObjType* objtype = 0;
	if(doorType == JBDungeonWall::c_WALL)
		objtype = objtypes[3];
	else if(doorType == JBDungeonWall::c_DOOR)
		objtype = objtypes[4];
	else
		return;
	if(objtype == 0) return;
	obj = pRuntime->CreateObject(objtype, layer->number, pLayout);

	obj->info.w = options.thinWallWidth;
	obj->info.h = options.tileSize;

	if(horiz) {
		obj->info.x = x * options.tileSize + options.tileSize;
		obj->info.y = y * options.tileSize + options.tileSize - options.thinWallWidth/2;
		obj->info.angle = 90;
	} else {
		obj->info.x = x * options.tileSize + options.tileSize - options.thinWallWidth/2;;
		obj->info.y = y * options.tileSize;
	}
	obj->UpdateBoundingBox();
}

//after the maze has been generated, create it on the layout using
//set construct objects
long ExtObject::aBuildToLayout(LPVAL params)
{
	CRunLayout* layout = pLayout;
	CRunLayer* layer = params[0].GetLayerParam(pRuntime, layout);
	CRunObjType* objtype = 0;
	if(layer == 0)
		return 0;

	//maze should be generated at this point!
	for(unsigned int y = 0; y < dungeon->getY(); ++y) {
		for(unsigned int x = 0; x < dungeon->getX(); ++x) {
			int tile = dungeon->getDungeonAt(x, y, 0);
			if(tile == JBDungeon::c_WALL)
				objtype = objtypes[0];
			else if(tile == JBDungeon::c_PASSAGE)
				objtype = objtypes[1];
			else if(tile == JBDungeon::c_ROOM)
				objtype = objtypes[2];
			else
				continue;
			if(objtype == 0) continue;
			CRunObject* obj = pRuntime->CreateObject(objtype, layer->number, layout);
			obj->info.x = x * options.tileSize;
			obj->info.y = y * options.tileSize;
			obj->info.w = options.tileSize;
			obj->info.h = options.tileSize;
			obj->UpdateBoundingBox();
		}
	}

	if(options.thinWallWidth == 0) return 0;

	//walls, doors
	int wall = 0;
	for(unsigned int y = 0; y < dungeon->getY() - 1; ++y) {
		for(unsigned int x = 0; x < dungeon->getX() - 1; ++x) {
			JBMazePt p1(x, y, 0);
			JBMazePt p2(x, y+1, 0);
			JBMazePt p3(x+1, y, 0);
			/*if(dungeon->getDungeonAt(p1) == JBDungeon::c_WALL ||
				dungeon->getDungeonAt(p2) == JBDungeon::c_WALL ||
				dungeon->getDungeonAt(p3) == JBDungeon::c_WALL)
			{
				continue;
			}*/
			int dir = -1; // 0-1-2-3 == N-E-S-W
			wall = dungeon->getWallBetween(p1, p2); //south wall
			if(wall != JBDungeonWall::c_NONE)
				drawDoor(x, y, wall, 1, layer);
			wall = dungeon->getWallBetween(p1, p3); // east wall
			if(wall != JBDungeonWall::c_NONE)
				drawDoor(x, y, wall, 0, layer);
		}
	}
	return 0;
}

long ExtObject::aSetSeed(LPVAL params)
{
	options.seed = params[0].GetInt();
	return 0;
}

//set width/height (no depth support yet)
long ExtObject::aSetSize(LPVAL params)
{
	options.size.x = params[0].GetInt();
	options.size.y = params[1].GetInt();
	return 0;
}

//randomness amount little - lots
long ExtObject::aSetRandomness(LPVAL params)
{
	options.randomness = params[0].GetInt();
	return 0;
}

long ExtObject::aSetSparseness(LPVAL params)
{
	options.sparseness = params[0].GetInt();
	return 0;
}

//tile size (pixels) for "build to layout" action
long ExtObject::aSetTileSize(LPVAL params)
{
	options.tileSize = params[0].GetInt();
	return 0;
}

long ExtObject::aSetRoomCount(LPVAL params)
{
	options.minRoomCount = params[0].GetInt() >= 0 ? params[0].GetInt() : 0;
	options.maxRoomCount = params[1].GetInt() >= options.minRoomCount ? params[1].GetInt() : options.minRoomCount;
	return 0;
}

//percentage of dead ends to clear
long ExtObject::aSetDeadEndsToRemove(LPVAL params)
{
	options.clearDeadends = params[0].GetInt();
	return 0;
}

long ExtObject::aSetRoomDimensions(LPVAL params)
{
	options.minRoomX = params[0].GetInt() > 0 ? params[0].GetInt() : 1;
	options.maxRoomX = params[1].GetInt() >= options.minRoomX ? params[1].GetInt() : options.minRoomX + 1;
	options.minRoomY = params[2].GetInt() > 0 ? params[2].GetInt() : 1;
	options.maxRoomY = params[3].GetInt() >= options.minRoomY ? params[3].GetInt() : options.minRoomY + 1;
	assert(options.minRoomX > 0);
	assert(options.maxRoomX >= options.minRoomX);
	assert(options.minRoomY > 0);
	assert(options.maxRoomY >= options.minRoomY);
	return 0;
}

//starting point for mazes
long ExtObject::aSetStart(LPVAL params)
{
	int x = params[0].GetInt();
	int y = params[1].GetInt();
	Clamp(x, 0, options.size.x - 1);
	Clamp(y, 0, options.size.y - 1);
	options.start = JBMazePt(x, y, 0);
	return 0;
}

//goal for mazes
long ExtObject::aSetEnd(LPVAL params)
{
	options.end = JBMazePt(params[0].GetInt(), params[1].GetInt(), 0);
	return 0;
}

//Tile types:
//static const int c_WALL;     /* point is in a wall */
//static const int c_PASSAGE;  /* point is in a passage */
//static const int c_ROOM;     /* point is in a room */
//Walls are separate types:
//const int JBDungeonWall::c_NONE = 0;
//const int JBDungeonWall::c_WALL = 1;
//const int JBDungeonWall::c_DOOR = 2;
//const int JBDungeonWall::c_SECRETDOOR = 3;
//const int JBDungeonWall::c_CONCEALEDDOOR = 4;
//However we have only these:
//0 = rock
//1 = tunnel
//2 = room
//3 = wall
//4 = door
long ExtObject::aSetObjectMapping(LPVAL params)
{
	CRunObjType* objtype = params[1].GetObjectParam(pRuntime);
	if(objtype == 0)
		return 0;
	objtypes[params[0].GetInt()] = objtype;
	return 0;
}

long ExtObject::aSetThinWallWidth(LPVAL params)
{
	options.thinWallWidth = params[0].GetInt();
	Clamp(options.thinWallWidth, 0, 128);
	return 0;
}