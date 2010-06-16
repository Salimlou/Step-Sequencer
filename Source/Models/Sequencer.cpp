/*
 *  Sequencer.cpp
 *  midi_sequencer1
 *
 *  Created by Matt Sonic on 6/16/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "Cell.h"

#include "Sequencer.h"

Sequencer::Sequencer (PluginAudioProcessor* pluginAudioProcessor_) :
pluginAudioProcessor (pluginAudioProcessor_),
totalRows (64),
totalCols (16)
{
	int i = 0;
	for (i = 0; i < totalCols; i++) {
		OwnedArray<Cell>* col;
		columns.add(col = new OwnedArray<Cell>);
		
		for (int j = 0; j < totalRows; j++) {
			Cell* cell;
			col->add (cell = new Cell (j, i));
			if (i != 0) {
				Cell* westCell = columns.getUnchecked(i - 1)->getUnchecked(j);
				cell->setWestCell (westCell);
				westCell->setEastCell (cell);
			}
			if (j != 0) {
				Cell* northCell = col->getUnchecked (j - 1);
				cell->setNorthCell (northCell);
				northCell->setSouthCell (cell);
			}
		}
	}
}

Sequencer::~Sequencer()
{
}

int Sequencer::getTotalRows()
{
	return totalRows;
}

int Sequencer::getTotalCols()
{
	return totalCols;
}

Cell* Sequencer::getCellAt (int row, int col)
{
	OwnedArray<Cell>* column = columns[col];
	Cell* cell = column->getUnchecked (row);
	return cell;
}




