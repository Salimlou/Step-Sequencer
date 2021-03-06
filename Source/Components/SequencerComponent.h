/*
 *  SequencerComponent.h
 *  syzygrd_sequencer1
 *
 *  Created by Matt Sonic on 6/17/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#ifndef SequencerComponent_H
#define SequencerComponent_H

#include "JuceHeader.h"

class PluginAudioProcessor;
class Cell;
class Sequencer;
class CellComponent;

class SequencerComponent : 
public Component,
public Timer
{
public:
	SequencerComponent(PluginAudioProcessor* pluginAudioProcessor_);
	~SequencerComponent();
	
	CellComponent* getCellAt (int row, int col);
	
	// Component methods
	virtual void paint (Graphics& g);
	virtual void resized();
	virtual bool keyPressed (const KeyPress& key);
	
	// Timer methods
	virtual void timerCallback();
	
private:
	PluginAudioProcessor* pluginAudioProcessor;
	Sequencer* sequencer;
	
	OwnedArray< Array<CellComponent*> > rows;
	
	int lastPlayheadCol;
};

#endif

