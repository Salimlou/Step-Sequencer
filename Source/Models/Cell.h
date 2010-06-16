/*
 *  Cell.h
 *  midi_sequencer2
 *
 *  Created by Matt Sonic on 4/9/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#ifndef CELL_H
#define CELL_H

#include "JuceHeader.h"

class Cell 
{
public:
	Cell (int row_, int col_);
	~Cell();
	void setChecked (bool checked_);
	bool isChecked();
	void setNorthCell (Cell* northCell_);
	void setWestCell (Cell* westCell_);
	void setEastCell (Cell* eastCell_);
	void setSouthCell (Cell* southCell_);
	Cell* getNorthCell();
	Cell* getWestCell();
	Cell* getEastCell();
	Cell* getSouthCell();
	int getRow();
	int getCol();
	
private:
	bool checked;
	Cell* northCell;
	Cell* westCell;
	Cell* eastCell;
	Cell* southCell;
	int row;
	int col;
};

#endif
