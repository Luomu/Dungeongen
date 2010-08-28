// Main.h
// Definitions and classes for the object workings

// Only include once
#ifndef MAIN_H
#define MAIN_H

#define MINIMUM_VERSION	1

// IDE FLAGS
// Can be a combination of:
//OF_NOSIZE	- Extension cannot be resized at edittime
//OF_NODRAW - Extension does not display anything
//OF_ALLOWANGLES - Can be rotated at edittime
//OF_PRIVATEVARIABLES - Uses private variables
//OF_MOVEMENTPLUGIN - Is a movement plugin
//OF_MOVEMENTS - Allow movement plugins to be added
//OF_EFFECTS - Allow display effects
//OF_NOCOMMONDEBUG - Don't show 'Common' field (X/Y/W/H/Angle/Opacity) in debugger
//OF_NODEBUG - Don't show at all in debugger
//OF_UNDEFINEDEXPRESSIONS - Allow ReturnUndefinedExpression to be called
#define IDE_FLAGS 	OF_NOCOMMONDEBUG | OF_NODRAW

#include "..\Common\ExpReturn.hpp"
#include "jbdungeon.h"
#include "options.h"
#include "exceptions.h"

#define OBJECTRECT CRect(editObject->objectX, editObject->objectY, editObject->objectX + editObject->objectWidth, editObject->objectY + editObject->objectHeight)

//////////// RUNTIME OBJECT ////////////
// Add any member functions or data you want to this class.
// Your extension inherits CRunObject.  See the definition
// for the default member values you have access to.
class ExtObject : public CRunObject
{
public:
	// Constructor (called when Construct creates the object)
	ExtObject(initialObject* editObject, VRuntime* pVRuntime);
	// Destructor (called when Construct destroys the object)
	~ExtObject();

	IRenderer* const renderer;

	//////////////////////////
	// OnFrame: called once per frame just before Draw() (after the events list)
	// OnFrame2: called once per frame just after Draw() (before the events list)
	BOOL		OnFrame();
	BOOL		OnFrame2();
	// Draw: called when Construct wants you to render your object.
	void		Draw();
	// WindowProc is called if your extension creates a window and calls RegisterWindow().
	LRESULT		WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	BOOL		PreTranslateMessage(MSG* msg);
	// Return default expression editor value and undefined expressions when enabled.
	long		ReturnDefaultValue(LPVAL params, ExpReturn& ret);
	long		ReturnUndefinedExpression(CString& expName, LPVAL params, ExpReturn& ret);
	// Called just after the constructor when your object has been prepared.
	void		OnCreate();
	// Called when a frame changes and your object is global
	void		OnFrameChange(int oldFrame, int newFrame);
	// Called when your object should save/load itself at runtime
	void		Serialize(bin& ar);
	// Data functions
	long		GetData(int id, void* param);
	long		CallFunction(int id, void* param);
	// Debugging
	void		DebuggerUpdateDisplay(ExpStore*& pPrivateVars);
	void		OnDebuggerValueChanged(const char* name, const char* value);

	////////////////////////////////////////////////////
	// ACTIONS, CONDITIONS AND EXPRESSIONS DEFINITIONS
#include "..\Common\CommonAceDecl.hpp"

	//long cMyCondition(LPVAL params);

	long aGenerate(LPVAL params);
	long aBuildToLayout(LPVAL params);
	long aSetObjectMapping(LPVAL params);
  long aBuildToLayoutExpanded(LPVAL params);
	//param setters
	long aSetSeed(LPVAL params);
	long aSetSize(LPVAL params);
	long aSetRandomness(LPVAL params);
	long aSetSparseness(LPVAL params);
	long aSetTileSize(LPVAL params);
	long aSetRoomCount(LPVAL params);
	long aSetDeadEndsToRemove(LPVAL params);
	long aSetRoomDimensions(LPVAL params);
	long aSetStart(LPVAL params);
	long aSetEnd(LPVAL params);
	long aSetThinWallWidth(LPVAL params);

	//param getters
	long eSeed(LPVAL params, ExpReturn& ret) { return ret = options.seed; }
	long eWidth(LPVAL params, ExpReturn& ret) { if(dungeon) return ret = dungeon->getX(); else return ret = options.size.x * 4 + 3; }
	long eHeight(LPVAL params, ExpReturn& ret) { if(dungeon) return ret = dungeon->getY(); else return ret = options.size.y * 4 + 3; }
	long eRandomness(LPVAL params, ExpReturn& ret) { return ret = options.randomness; }
	long eSparseness(LPVAL params, ExpReturn& ret) { return ret = options.sparseness; }
	long eTileSize(LPVAL params, ExpReturn& ret) { return ret = options.tileSize; }
	long eMaxRoomCount(LPVAL params, ExpReturn& ret) { return ret = options.maxRoomCount; }
	long eMinRoomCount(LPVAL params, ExpReturn& ret) { return ret = options.minRoomCount; }
	long eDeadEnds(LPVAL params, ExpReturn& ret) { return ret = options.clearDeadends; }
	long eThinWallWidth(LPVAL params, ExpReturn& ret) { return ret = options.thinWallWidth; }

	//non-param expressions
	long eGetTileAt(LPVAL params, ExpReturn& ret);
	long eGetWallBetweenPoints(LPVAL params, ExpReturn& ret);
	long eRoomCount(LPVAL params, ExpReturn& ret) { if(dungeon) return ret = dungeon->getRoomCount(); else return ret = 0; }
	long eRoomTopLeftX(LPVAL params, ExpReturn& ret);
	long eRoomTopLeftY(LPVAL params, ExpReturn& ret);
	long eRoomWidth(LPVAL params, ExpReturn& ret);
	long eRoomHeight(LPVAL params, ExpReturn& ret);

	////////////////////////////////////////////////////
	// Data members

	// Use when private variables (OF_PRIVATEVARIABLES) are enabled.
private:
	enum TileTypes {
		tile_ROCK = 0,
		tile_PASSAGE,
		tile_ROOM,
		tile_WALL,
		tile_DOOR,
		tile_DOOR_HORIZONTAL
	};
	JBDungeon* dungeon;
	Options options;
	std::map<int, CRunObjType*> objtypes;

	void placeTile(CRunObjType* obj, int tileX, int tileY, CRunLayer* layer, int angle = -1);
	void placeWall(CRunObjType* obj, int tileX, int tileY, CRunLayer* layer, int angle = -1);
};

//////////// EDITTIME INFO ////////////
class EditExt
{
public:

	///////////////////////////
	// Class data
	EditExt(class VEditTime* pVEditTime, class editInfo* pEInfo);
	~EditExt();

	void Draw();
	int  GetMenuIcons(int ACEMenu);
	void Initialize();
	void OnPut();
	void OnRemoved();
	int  OnShowACEMenu(TABLE ACEType);
	BOOL OnSizeObject();
	void Serialize(bin& ar);
	void OnPropertiesUpdate();
	void GetAnimationHandle(int& handle);

	class VEditTime* pEditTime;	// Pointer to Virtual Edittime
	class editInfo*  pInfo;		// Pointer to object edittime info

	///////////////////////////
	// Your edittime extension data goes here
	//int iTexture;		// DX texture

	//int myValue;
};

// Internal stuff include
#include "..\Common\Internal.hpp"
#include "..\Common\Properties.h"

// Only include once
#endif