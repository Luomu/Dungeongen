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
	//begin parameter actions
	ADDPARAM(PARAM_VALUE, "Seed", "Seed to base randomization on.");
	ADDACT("Set seed", "Parameters", "Set seed %0", &ExtObject::aSetSeed, "SetSeed", 0);

	ADDPARAM(PARAM_VALUE, "Width", "Dungeon width (tiles).");
	ADDPARAM(PARAM_VALUE, "Height", "Dungeon height (tiles).");
	ADDACT("Set size", "Parameters", "Set size to %0 by %1", &ExtObject::aSetSize, "SetSize", 0);
	//end parameter actions

	/////////////////////////////
	// Expressions
	// ADDEXP(List name, Category, Display string, Function address, Flags)
	//ADDEXP("My expression", "My category", "MyExpression", &ExtObject::eMyExpression, RETURN_INTEGER);
	// This line includes your common ACEs as specified in Main.h
#include "..\Common\CommonAceTable.hpp"
}


