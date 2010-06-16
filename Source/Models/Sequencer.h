/*
 *  Sequencer.h
 *  midi_sequencer1
 *
 *  Created by Matt Sonic on 6/16/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#ifndef Sequencer_H
#define Sequencer_H

#include "PluginAudioProcessor.h"
#include "AudioProcessorCallback.h"

#include "JuceHeader.h"

class Cell;

class Sequencer : public AudioProcessorCallback
{
public:
	Sequencer (PluginAudioProcessor* pluginAudioProcessor_);
	~Sequencer();
	
	int getTotalRows();
	int getTotalCols();
	Cell* getCellAt (int row, int col);
	int getPlayheadRow();

	// AudioProcessorCallback methods
	virtual void prepareToPlay (double sampleRate, int samplesPerBlock);
    virtual void releaseResources();
    virtual void processBlock (AudioSampleBuffer& buffer, 
							   MidiBuffer& midiMessages);	
	
private:
	PluginAudioProcessor* pluginAudioProcessor;

	const int totalRows;
	const int totalCols;
	OwnedArray< OwnedArray<Cell> > columns;

	int playheadRow;
};

#endif
