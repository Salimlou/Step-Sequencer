/*
 *  SequencerComponent.cpp
 *  midi_sequencer1
 *
 *  Created by Matt Sonic on 6/15/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "Cell.h"
#include "PluginAudioProcessor.h"
#include "MyTableListBox.h"

#include "SequencerComponent.h"

SequencerComponent::SequencerComponent(PluginAudioProcessor* pluginAudioProcessor_) :
Component ("SequencerComponent"),
pluginAudioProcessor (pluginAudioProcessor_),
tableListBox (0),
totalRows (64),
totalCols (16),
selectedCell (0),
selectedRowIndex (-1)
{
	addAndMakeVisible(tableListBox = new MyTableListBox (T("My Table List Box"), this));
	tableListBox->setHeaderHeight (0);
	tableListBox->setRowHeight (15);
	tableListBox->getHeader()->setStretchToFitActive (true);
	
	int i = 0;
	for (i = 0; i < totalCols; i++) {
		OwnedArray<Cell>* col;
		columns.add(col = new OwnedArray<Cell>);
		addTableColumn (String(i), i + 1);
		
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
	addTableColumn (String(i), i + 1);
	
	setSize (600, 400);
	setWantsKeyboardFocus (true);
}

SequencerComponent::~SequencerComponent()
{
	deleteAndZero (tableListBox);
}

void SequencerComponent::addTableColumn (const String& title, int ID)
{
	tableListBox->getHeader()->addColumn (title,
										  ID,
										  20,
										  30,
										  100,
										  TableHeaderComponent::defaultFlags);	
}

// Component methods
void SequencerComponent::paint (Graphics& g)
{
	g.setGradientFill(ColourGradient (Colours::lightgrey, 0, 0,
									  Colours::white, 0, getHeight(), 
									  false));
	g.fillAll();	
}

void SequencerComponent::resized()
{
	tableListBox->setBoundsInset (BorderSize(10));	
}

bool SequencerComponent::keyPressed (const KeyPress& key)
{
	if (key.getKeyCode() == KeyPress::leftKey) {
		Cell* newSelectedCell = selectedCell->getWestCell();
		if (newSelectedCell != 0) {
			selectedCell = newSelectedCell;
		}
		repaint();
	} else if (key.getKeyCode() == KeyPress::rightKey) {
		Cell* newSelectedCell = selectedCell->getEastCell();
		if (newSelectedCell != 0) {
			selectedCell = newSelectedCell;
		}
		repaint();
	} else if (key.getKeyCode() == KeyPress::downKey) {
		Cell* newSelectedCell = selectedCell->getSouthCell();
		if (newSelectedCell != 0) {
			selectedCell = newSelectedCell;
			tableListBox->selectRow(selectedCell->getRow() + 1, false, true);
		}
		repaint();
	} else if (key.getKeyCode() == KeyPress::upKey) {
		Cell* newSelectedCell = selectedCell->getNorthCell();
		if (newSelectedCell != 0) {
			selectedCell = newSelectedCell;
			tableListBox->selectRow(selectedCell->getRow() + 1, false, true);
		}
		repaint();
	} else if (key.getKeyCode() == KeyPress::pageDownKey) {
		Cell* newSelectedCell = selectedCell->getSouthCell()->getSouthCell()->getSouthCell()->getSouthCell();
		if (newSelectedCell != 0) {
			selectedCell = newSelectedCell;
			tableListBox->selectRow(selectedCell->getRow() + 1, false, true);
		}
		repaint();
	} else if (key.getKeyCode() == KeyPress::pageUpKey) {
		Cell* newSelectedCell = selectedCell->getNorthCell()->getNorthCell()->getNorthCell()->getNorthCell();
		if (newSelectedCell != 0) {
			selectedCell = newSelectedCell;
			tableListBox->selectRow(selectedCell->getRow() + 1, false, true);
		}
		repaint();		
	} else if (key.getKeyCode() == KeyPress::spaceKey) {
		selectedCell->setChecked (true);
		tableListBox->selectRow(selectedCell->getRow() + 1, false, true);
 
		repaint();
	} 
	
	return true;	
}

// TableListBoxModel methods
int SequencerComponent::getNumRows()
{
	return totalRows + 1;	
}

void SequencerComponent::paintRowBackground (Graphics& g,
											 int rowNumber,
											 int width, int height,
											 bool rowIsSelected)
{
	if (rowIsSelected) {
		g.fillAll (Colours::darkblue);
	} else {
		if ((rowNumber - 1) % 4 == 0) {
			g.fillAll (Colour::fromRGB (50, 50, 50));
		} else {
			g.fillAll (Colours::black);
		}
	}	
}

void SequencerComponent::paintCell (Graphics& g,
									int rowNumber,
									int columnId,
									int width, int height,
									bool rowIsSelected)
{
	int rowNum = rowNumber - 1;
	int colNum = columnId - 2;
	
	if (rowNum == -1 & colNum == -1) {
		g.fillAll (Colours::lightgrey);
	} else if (rowNum == -1) {
		g.fillAll (Colours::lightgrey);
		g.drawText(String(colNum), 0, 0, width, height, Justification::centred, false);
	} else if (colNum == -1) {
		g.fillAll (Colours::lightgrey);
		g.drawText(String(rowNum), 0, 0, width, height, Justification::centred, false);
	} else {
		OwnedArray<Cell>* col = columns[colNum];
		Cell* cell = col->getUnchecked (rowNum);
		if (cell == selectedCell) {
			g.fillAll( Colours::blue );
		}
		if (cell->isChecked()) {
			g.setColour (Colours::white);
			g.drawText(T("C-3"), 0, 0, width, height, Justification::centred, false);
		} 
	}
	g.setColour (Colours::darkgrey);
	g.drawRect (0, 0, width+1, height+1, 1.0);	
}

void SequencerComponent::cellClicked (int rowNumber, int columnId, const MouseEvent& e)
{
	int rowNum = rowNumber - 1;
	int colNum = columnId - 2;
	
	if (rowNum < 0 || colNum < 0) return;
	
	OwnedArray<Cell>* col = columns[colNum];
	Cell* cell = col->getUnchecked (rowNum);
	
	selectedCell = cell;
	
	repaint();	
}

void SequencerComponent::selectedRowsChanged (int lastRowSelected)
{
/*
	if (!selectedCell) {
		selectedRowIndex = lastRowSelected;
		return;
	}
	
	if (lastRowSelected == 0) {
		SparseSet<int> ss;
		ss.addRange (Range<int>(1, 1));
		tableListBox->setSelectedRows(ss, true);
		return;
	}
	
	Cell* newSelectedCell = selectedCell;
	if (lastRowSelected > selectedRowIndex) {
		for (int i = 0; i < (lastRowSelected - selectedRowIndex); i++) {
			if (newSelectedCell->getSouthCell() == 0) break;
			newSelectedCell = newSelectedCell->getSouthCell();
		}
	} else {
		for (int i = 0; i < (selectedRowIndex - lastRowSelected); i++) {
			if (newSelectedCell->getNorthCell() == 0) break;
			newSelectedCell = newSelectedCell->getNorthCell();
		}
	}
	if (newSelectedCell != 0) {
		selectedCell = newSelectedCell;
	}
	selectedRowIndex = lastRowSelected;
	tableListBox->scrollToEnsureRowIsOnscreen (lastRowSelected);
	repaint();	
 */
}

void SequencerComponent::deleteKeyPressed (int lastRowSelected)
{
	selectedCell->setChecked (false);
	
/*
	int nextRow = tableListBox->getSelectedRow(0) + 1;
	nextRow = jmin(nextRow, tableListBox->getNumRows() - 1);
	SparseSet<int> ss;
	ss.addRange (Range<int>(nextRow, 1));
	tableListBox->setSelectedRows(ss, true);
*/
 
	repaint();	
}



