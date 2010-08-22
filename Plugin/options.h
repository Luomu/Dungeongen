#ifndef OPTIONS_H
#define OPTIONS_H

//at the moment a wrapper to jbdungeonopts
class Options : public JBDungeonOptions {
public:
	Options() : JBDungeonOptions(),
		tileSize(32)
	{
		secretDoors = 3;
		concealedDoors = 3;
		minRoomX = 2;
		maxRoomX = 3;
		minRoomY = 2;
		maxRoomY = 3;
	}

	int tileSize;
};

#endif