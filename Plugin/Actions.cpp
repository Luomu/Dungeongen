// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////////////
//Generate the dungeon. Opts have been set previously.
long ExtObject::aGenerate(LPVAL params)
{
	dungeon = new JBDungeon(options);
	return 0;
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
			unsigned int tile = dungeon->getDungeonAt(x, y, 0) == JBDungeon::c_WALL;
			if(tile <= 1) {
				objtype = objtypes[tile];
				if(objtype == 0) continue;
				CRunObject* obj = pRuntime->CreateObject(objtype, layer->number, layout);
				obj->info.x = x * options.tileSize;
				obj->info.y = y * options.tileSize;
				obj->UpdateBoundingBox();
			}
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
	options.maxRoomCount = params[0].GetInt();
	options.minRoomCount = params[1].GetInt();
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
	options.minRoomX = params[0].GetInt();
	options.maxRoomX = params[1].GetInt();
	options.minRoomY = params[2].GetInt();
	options.maxRoomY = params[3].GetInt();
	return 0;
}

//starting point for mazes
long ExtObject::aSetStart(LPVAL params)
{
	options.start = JBMazePt(params[0].GetInt(), params[1].GetInt(), 0);
	return 0;
}

//goal for mazes
long ExtObject::aSetEnd(LPVAL params)
{
	options.end = JBMazePt(params[0].GetInt(), params[1].GetInt(), 0);
	return 0;
}

/*
const int JBDungeonWall::c_NONE = 0;
const int JBDungeonWall::c_WALL = 1;
const int JBDungeonWall::c_DOOR = 2;
const int JBDungeonWall::c_SECRETDOOR = 3;
const int JBDungeonWall::c_CONCEALEDDOOR = 4;
*/
long ExtObject::aSetObjectMapping(LPVAL params)
{
	CRunObjType* objtype = params[1].GetObjectParam(pRuntime);
	if(objtype == 0)
		return 0;
	objtypes[params[0].GetInt()] = objtype;
	return 0;
}