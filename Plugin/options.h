#ifndef OPTIONS_H
#define OPTIONS_H

//at the moment a wrapper to jbdungeonopts
class Options : public JBDungeonOptions {
public:
	Options() : JBDungeonOptions(),
		tileSize(32)
	{ }

	int tileSize;
};

#endif