// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Built-in expressions
//////////////////////////////////////////////////////////////////////////////////

// Return the Default Value.  This is the value to be returned if your object name
// is used without an expression name, eg. in "Counter + 1".
// Parameters can be passed, eg. MyObject(3,7).  You can check ExpReturn::Type() or GetNumParams() to check for overloads.
long ExtObject::ReturnDefaultValue(LPVAL theParams, ExpReturn& ret)
{
	return ret = 0;
}

// Called for undefined expression names, if your extension allows it.
// Eg: MyObject.UndefinedExpression(3,4,5) calls this routine with
// "UndefinedExpression" as the expression name.  OF_UNDEFINEDEXPRESSIONS must be specified in Main.h.
long ExtObject::ReturnUndefinedExpression(CString& expName, LPVAL theParams, ExpReturn& ret)
{
	return ret = 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Expressions
//////////////////////////////////////////////////////////////////////////////////
long ExtObject::eGetTileAt(LPVAL params, ExpReturn &ret)
{
	int x = params[0].GetInt();
	int y = params[1].GetInt();
	int retval = 0;
	if(x >= 0 && x <= dungeon->getX() && y >= 0 && y <= dungeon->getY())
		retval = dungeon->getDungeonAt(x, y, 0);
	return ret = retval;
}

long ExtObject::eGetWallBetweenPoints(LPVAL params, ExpReturn &ret)
{
	if(dungeon == 0) return ret = 0;
	JBMazePt p1(params[0].GetInt(), params[1].GetInt(), 0);
	JBMazePt p2(params[2].GetInt(), params[3].GetInt(), 0);
	int retval = dungeon->getWallBetween(p1, p2);
	if(retval == JBDungeonWall::c_WALL)
		retval = 3;
	else if(retval == JBDungeonWall::c_DOOR)
		retval = 4;
	else
		retval = 0;
	return ret = retval;
}