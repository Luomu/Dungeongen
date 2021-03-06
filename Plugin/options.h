#ifndef OPTIONS_H
#define OPTIONS_H

//at the moment a wrapper to jbdungeonopts
class Options : public JBDungeonOptions {
public:
	Options() : JBDungeonOptions(),
		tileSize(32),
		thinWallWidth(8)
	{
		secretDoors = 0;
		concealedDoors = 0;
		minRoomX = 2;
		maxRoomX = 3;
		minRoomY = 2;
		maxRoomY = 3;
	}

	int tileSize;
	int thinWallWidth;
};

#endif