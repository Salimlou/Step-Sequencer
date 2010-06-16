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
AudioProcessorCallback (pluginAudioProcessor),
pluginAudioProcessor (pluginAudioProcessor_),
totalRows (64),
totalCols (16),
playheadRow (0),
lastPlayheadRow (-1),
speed (4)
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

int Sequencer::getPlayheadRow()
{
	return playheadRow;
}

// AudioProcessorCallback methods
void Sequencer::prepareToPlay (double sampleRate_, int samplesPerBlock)
{
	sampleRate = sampleRate_;
}

void Sequencer::releaseResources()
{
}

void Sequencer::processBlock (AudioSampleBuffer& buffer,
							  MidiBuffer& midiMessages)
{
	AudioPlayHead::CurrentPositionInfo pos (pluginAudioProcessor->lastPosInfo);	

	if (! pos.isPlaying) {
		return;
	}
	
	double ppq = pos.ppqPosition;

	/*
	int numerator = pos.timeSigNumerator;
	int denominator = pos.timeSigDenominator;
	
	const int ppqPerBar = (numerator * 4 / denominator); // e.g. 4 if 4/4
	const double beats = (fmod (ppq, ppqPerBar) / ppqPerBar) * numerator;
	
	const int bar = ((int) ppq) / ppqPerBar + 1;
	const int beat = ((int) beats) + 1;
	const int ticks = ((int) (fmod (beats, 1.0) * 960.0));	
	*/
	 
	double playheadRowPrecise = fmod (ppq * speed, totalRows);
	playheadRow = (int)playheadRowPrecise;
	
	if (playheadRow != lastPlayheadRow) {

		lastPlayheadRow = playheadRow;
		
		double beatsPerSec = pos.bpm * speed / 60.0;
		double secPerBeat = 1.0 / beatsPerSec;	

		double playheadOffset = playheadRowPrecise - playheadRow;
		int playheadOffsetSamples = playheadOffset * secPerBeat * sampleRate;
		playheadOffsetSamples = jmax (buffer.getNumSamples() - playheadOffsetSamples - 1, 0);
		
		for (int i = 0; i < totalCols; i++) {
			Cell* cell = getCellAt (playheadRow, i);
			int noteNumber = cell->getNoteNumber();
			if (noteNumber != -1) {
				MidiMessage m = MidiMessage::noteOn(1, noteNumber, 0.9f);
				//midiMessages.addEvent (m, 0);
				midiMessages.addEvent (m, playheadOffsetSamples);
			}
		}
	}
}





