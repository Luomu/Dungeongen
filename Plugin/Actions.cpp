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
	CRunObjType* objtype = pRuntime->GetTypeFromName("block");
	CRunLayout* layout = pLayout;
	CRunLayer* layer = params[0].GetLayerParam(pRuntime, layout);
	if(layer == 0)
		return 0;
	if(objtype == 0)
		throw DException("Unknown objtype");

	//maze should be generated at this point!
	for(unsigned int y = 0; y < dungeon->getY(); ++y) {
		for(unsigned int x = 0; x < dungeon->getX(); ++x) {
			if(dungeon->getDungeonAt(x, y, 0) == JBDungeon::c_WALL) {
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