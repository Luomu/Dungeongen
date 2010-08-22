// Include StdAfx
#include "StdAfx.h"

// Include any used common ACE definitions.
#ifdef RUN_ONLY
#include "..\Common\CommonAceDef.hpp"
#endif

//////////////////////////////////////////////////////////////////////////////////
// ACE table
//////////////////////////////////////////////////////////////////////////////////

void DefineACES(MicroAceTime* at)
{
	// Define your ACE tables here.
	// Use ADDPARAM before each ADDACT/ADDCND/ADDEXP to add parameters.
	// See the documentation for full details.

	// Note in the display string, %o is your object icon and %0-%9 make up parameters.
	// Note the script name should be a name suitable for the routine as if it were a member function in a
	// scripting language, eg. "Clear Stored Items" -> "ClearStoredItems"

	/////////////////////////////
	// Conditions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	//ADDCND("My condition", "My category", "%o My condition", &ExtObject::cMyCondition, "MyCondition", 0);

	/////////////////////////////
	// Actions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	//ADDPARAM(PARAM_VALUE, "Example parameter", "Here is an example parameter.");
	//ADDACT("My action", "My category", "Example action (%0)", &ExtObject::aMyAction, "MyAction", 0);
	ADDACT("Generate", "Generation", "Generate", &ExtObject::aGenerate, "Generate", 0);
	ADDPARAMDEF(PARAM_VALUE, "Layer", "Layer name or number to build the dungeon on.", "1");
	ADDACT("Build to layer", "Generation", "Build to layer %0", &ExtObject::aBuildToLayout, "BuildToLayer", 0);

	ADDPARAM(PARAM_VALUE, "Tile type", "Tile type (0 = empty, 1 = wall, 2 = door)");
	ADDPARAM(PARAM_OBJECT, "Object", "Object to represent the tile");
	ADDACT("Set object mapping", "Generation", "Use %1 with tile type %0", &ExtObject::aSetObjectMapping, "SetObjectMapping", 0); 
	//begin parameter actions
	ADDPARAM(PARAM_VALUE, "Seed", "Seed to base randomization on.");
	ADDACT("Set seed", "Parameters", "Set seed to %0", &ExtObject::aSetSeed, "SetSeed", 0);

	ADDPARAM(PARAM_VALUE, "Width", "Dungeon width. Actual width is x * 2 + 1 to accomodate for walls.");
	ADDPARAM(PARAM_VALUE, "Height", "Dungeon height. Actual height is y * 2 + 1 to accomodate for walls.");
	ADDACT("Set size", "Parameters", "Set size to %0 by %1", &ExtObject::aSetSize, "SetSize", 0);

	ADDPARAM(PARAM_VALUE, "Randomness", "Randomness 0-100%");
	ADDACT("Set randomness", "Parameters", "Set randomness to %0%", &ExtObject::aSetRandomness, "SetRandomness", 0);

	ADDPARAM(PARAM_VALUE, "Sparseness", "Sparseness 0-100%");
	ADDACT("Set Sparseness", "Parameters", "Set sparseness to %0%", &ExtObject::aSetSparseness, "SetSparseness", 0);

	ADDPARAM(PARAM_VALUE, "Tile size", "Dungeon tile size in pixels.");
	ADDACT("Set Tile size", "Parameters", "Set Tile size to %0 pixels", &ExtObject::aSetTileSize, "SetTileSize", 0);

	ADDPARAM(PARAM_VALUE, "Minimum room count", "Minimum number of rooms.");
	ADDPARAM(PARAM_VALUE, "Maximum room count", "Largest possible room count.");
	ADDACT("Set room count", "Parameters", "Set room count (%0 minimum, %1 maximum)",
		&ExtObject::aSetRoomCount, "SetRoomCount", 0);

	ADDPARAM(PARAM_VALUE, "% to remove", "Percentage of dead ends to remove.");
	ADDACT("Set dead end removal amount", "Parameters",
		"Set dead end removal amount to %0%",
		&ExtObject::aSetDeadEndsToRemove, "SetDeadEndRemovalAmount", 0);

	ADDPARAM(PARAM_VALUE, "Minimum width", "Minimum room width in tiles.");
	ADDPARAM(PARAM_VALUE, "Maximum width", "Maximum room width in tiles.");
	ADDPARAM(PARAM_VALUE, "Minimum height", "Minimum room height in tiles.");
	ADDPARAM(PARAM_VALUE, "Maximum height", "Maximum room height in tiles.");
	ADDACT("Set room dimensions", "Parameters",
		"Set room dimensions to %0-%1 by %2-%3",
		&ExtObject::aSetRoomDimensions, "SetRoomDimensions", 0);

	ADDPARAM(PARAM_VALUE, "X", "Tile X (column)");
	ADDPARAM(PARAM_VALUE, "Y", "Tile Y (row)");
	ADDACT("Set start", "Mazes",
		"Set starting point at (%0, %1)",
		&ExtObject::aSetStart, "SetStart", 0);

	ADDPARAM(PARAM_VALUE, "X", "Tile X (column)");
	ADDPARAM(PARAM_VALUE, "Y", "Tile Y (row)");
	ADDACT("Set end", "Mazes",
		"Set end point at (%0, %1)",
		&ExtObject::aSetEnd, "SetEnd", 0);

	ADDPARAM(PARAM_VALUE, "Width", "Wall width in pixels (disabled when zero)");
	ADDACT("Set thin wall width", "Parameters",
		"Set thin wall width to %0 px",
		&ExtObject::aSetThinWallWidth, "SetThinWallWidth", 0);
	//end parameter actions

	/////////////////////////////
	// Expressions
	// ADDEXP(List name, Category, Display string, Function address, Flags)
	//ADDEXP("My expression", "My category", "MyExpression", &ExtObject::eMyExpression, RETURN_INTEGER);
	ADDEXP("Seed", "Parameters", "Seed", &ExtObject::eSeed, RETURN_INTEGER);
	ADDEXP("Width", "Parameters", "Width", &ExtObject::eWidth, RETURN_INTEGER);
	ADDEXP("Height", "Parameters", "Height", &ExtObject::eHeight, RETURN_INTEGER);
	ADDEXP("Randomness", "Parameters", "Randomness", &ExtObject::eRandomness, RETURN_INTEGER);
	ADDEXP("Sparseness", "Parameters", "Sparseness", &ExtObject::eSparseness, RETURN_INTEGER);
	ADDEXP("Tile size", "Parameters", "TileSize", &ExtObject::eTileSize, RETURN_INTEGER);
	ADDEXP("Maximum room count", "Parameters", "MaxRoomCount", &ExtObject::eMaxRoomCount, RETURN_INTEGER);
	ADDEXP("Minimum room count", "Parameters", "MinRoomCount", &ExtObject::eMinRoomCount, RETURN_INTEGER);
	ADDEXP("Dead end removal amount", "Parameters", "DeadEndRemovalAmount", &ExtObject::eDeadEnds, RETURN_INTEGER);
	ADDEXP("Thin wall width", "Parameters", "ThinWallWidth", &ExtObject::eThinWallWidth, RETURN_INTEGER);
	// This line includes your common ACEs as specified in Main.h
#include "..\Common\CommonAceTable.hpp"
}


