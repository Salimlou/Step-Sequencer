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
#include "Sequencer.h"

#include "SequencerComponent.h"

SequencerComponent::SequencerComponent (PluginAudioProcessor* pluginAudioProcessor_) :
Component ("SequencerComponent"),
pluginAudioProcessor (pluginAudioProcessor_),
sequencer (0),
tableListBox (0),
selectedCell (0),
selectedRowIndex (-1),
lastPlayheadRow (-1)
{
	sequencer = pluginAudioProcessor->getSequencer();
	
	addAndMakeVisible(tableListBox = new MyTableListBox (T("My Table List Box"), this));
	tableListBox->setHeaderHeight (15);
	tableListBox->setRowHeight (15);
	tableListBox->getHeader()->setStretchToFitActive (true);
	
	for (int i = 0; i <= sequencer->getTotalCols(); i++) {
		addTableColumn (i < 1 ? String::empty : String(i - 1), i + 1);
	}
	
	setSize (600, 400);
	setWantsKeyboardFocus (true);
	
	setAlwaysOnTop (true);
	
	startTimer (20);
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
	if (key.getKeyCode() == KeyPress::spaceKey) {
		return false;
	}
	
	Cell* newSelectedCell = 0;
	if (key.getKeyCode() == KeyPress::leftKey) {
		newSelectedCell = selectedCell->getWestCell();
	} else if (key.getKeyCode() == KeyPress::rightKey) {
		newSelectedCell = selectedCell->getEastCell();
	} else if (key.getKeyCode() == KeyPress::downKey) {
		newSelectedCell = selectedCell->getSouthCell();
	} else if (key.getKeyCode() == KeyPress::upKey) {
		newSelectedCell = selectedCell->getNorthCell();
	} else if (key.getKeyCode() == KeyPress::pageDownKey) {
		newSelectedCell = selectedCell->getSouthCell()->getSouthCell()->getSouthCell()->getSouthCell();
	} else if (key.getKeyCode() == KeyPress::pageUpKey) {
		newSelectedCell = selectedCell->getNorthCell()->getNorthCell()->getNorthCell()->getNorthCell();
	} else if (key.getKeyCode() == KeyPress::deleteKey) {
		selectedCell->setNoteNumber (-1);
		newSelectedCell = selectedCell->getSouthCell();
	} else {
		int newNoteNumber = 0;	
		switch (key.getKeyCode()) {
			case 'q':
				newNoteNumber = 60; break;
			case '2':
				newNoteNumber = 61; break;
			case 'w':
				newNoteNumber = 62; break;
			case '3':
				newNoteNumber = 63; break;
			case 'e':
				newNoteNumber = 64; break;
			case 'r':
				newNoteNumber = 65; break;
			case '5':
				newNoteNumber = 66; break;
			case 't':
				newNoteNumber = 67; break;
			case '6':
				newNoteNumber = 68; break;
			case 'y':
				newNoteNumber = 69; break;
			case '7':
				newNoteNumber = 70; break;
			case 'u':
				newNoteNumber = 71; break;
			case 'i':
				newNoteNumber = 72; break;
			case '9':
				newNoteNumber = 73; break;
			case 'o':
				newNoteNumber = 74; break;
			case '0':
				newNoteNumber = 75; break;
			case 'p':
				newNoteNumber = 76; break;
		}
		if (newNoteNumber > 0) {
			selectedCell->setNoteNumber(newNoteNumber);
			newSelectedCell = selectedCell->getSouthCell();
		}
	}
	
	if (newSelectedCell != 0) {
		selectedCell = newSelectedCell;
		tableListBox->selectRow(selectedCell->getRow(), false, true);
		repaint();	
	}
	
	return true;	
}

// TableListBoxModel methods
int SequencerComponent::getNumRows()
{
	return sequencer->getTotalRows();
}

void SequencerComponent::paintRowBackground (Graphics& g,
											 int rowNumber,
											 int width, int height,
											 bool rowIsSelected)
{
}

void SequencerComponent::paintCell (Graphics& g,
									int rowNumber,
									int columnId,
									int width, int height,
									bool rowIsSelected)
{
	int rowNum = rowNumber;
	int colNum = columnId - 2;
	
	if (colNum == -1) {
		g.fillAll (Colours::lightgrey);
		g.drawText(String(rowNum), 0, 0, width, height, Justification::centred, false);
	} else if (rowNum >= sequencer->getTotalRows()) {
		g.fillAll (Colours::black);
	} else {
		Cell* cell = sequencer->getCellAt (rowNum, colNum);

		bool isSelectedRow = false;
		if ((selectedCell != 0) 
			&& (cell->getRow() == selectedCell->getRow())) {
			isSelectedRow = true;
		}
		
		bool isPlayheadRow = false;
		if (cell->getRow() == sequencer->getPlayheadRow()) {
			isPlayheadRow = true;
		}
		
		if (cell == selectedCell) {
			g.fillAll (Colours::blue);
		} else if (((rowNum) % 4 == 0) 
				   && ((colNum % 4) == 0)) {
			if (isPlayheadRow) {
				g.fillAll (Colour::fromRGB(50, 140, 50));
			} else if (isSelectedRow) {
				g.fillAll (Colour::fromRGB(50, 50, 140));
			} else {
				g.fillAll (Colour::fromRGB(50, 50, 50));
			}
		} else if ((rowNum) % 4 == 0) {
			if (isPlayheadRow) {
				g.fillAll (Colour::fromRGB(30, 120, 30));
			} else if (isSelectedRow) {
				g.fillAll (Colour::fromRGB(30, 30, 120));
			} else {
				g.fillAll (Colour::fromRGB(30, 30, 30));
			}
		} else if ((colNum) % 4 == 0) {
			if (isPlayheadRow) {
				g.fillAll (Colour::fromRGB(30, 120, 30));
			} else if (isSelectedRow) {
				g.fillAll (Colour::fromRGB(30, 30, 120));
			} else {
				g.fillAll (Colour::fromRGB(30, 30, 30));
			}
		} else {
			if (isPlayheadRow) {
				g.fillAll (Colour::fromRGB(30, 100, 30));
			} else if (isSelectedRow) {
				g.fillAll (Colour::fromRGB(30, 30, 100));
			} else {
				g.fillAll (Colours::black);
			}
		}
		
		String noteString;
		switch (cell->getNoteNumber()) {
			case 60:
				noteString << "C-3"; break;
			case 61:
				noteString << "C#-3"; break;
			case 62:
				noteString << "D-3"; break;
			case 63:
				noteString << "D#-3"; break;
			case 64:
				noteString << "E-3"; break;
			case 65:
				noteString << "F-3"; break;
			case 66:
				noteString << "F#-3"; break;
			case 67:
				noteString << "G-3"; break;
			case 68:
				noteString << "G#-3"; break;
			case 69:
				noteString << "A-3"; break;
			case 70:
				noteString << "A#-3"; break;
			case 71:
				noteString << "B-3"; break;
			case 72:
				noteString << "C-4"; break;
			case 73:
				noteString << "C#-4"; break;
			case 74:
				noteString << "D-4"; break;
			case 75:
				noteString << "D#-4"; break;
			case 76:
				noteString << "E-4"; break;
		}
		if (!noteString.isEmpty()) {
			g.setColour (Colours::white);
			g.drawText(noteString, 0, 0, width, height, Justification::centred, false);
		} 
	}
	g.setColour (Colours::darkgrey);
	g.drawRect (0, 0, width+1, height+1, 1.0);	
}

void SequencerComponent::cellClicked (int rowNumber, int columnId, const MouseEvent& e)
{
	int rowNum = rowNumber;
	int colNum = columnId - 2;
	
	if (rowNum < 0 || colNum < 0) return;
	
	Cell* cell = sequencer->getCellAt (rowNum, colNum);
	
	selectedCell = cell;
	
	repaint();	
}

void SequencerComponent::selectedRowsChanged (int lastRowSelected)
{
}

// Timer methods
void SequencerComponent::timerCallback()
{
	if (lastPlayheadRow != sequencer->getPlayheadRow()) {
		lastPlayheadRow = sequencer->getPlayheadRow();
		repaint();
	}
}



