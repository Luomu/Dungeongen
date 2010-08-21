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
	throw NotImplementedException();
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