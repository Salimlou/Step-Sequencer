/*
 *  SequencerComponent.cpp
 *  syzygrd_sequencer1
 *
 *  Created by Matt Sonic on 6/17/10.
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
lastPlayheadRow (-1)
{
	sequencer = pluginAudioProcessor->getSequencer();
	
	setSize (600, 400);
	setWantsKeyboardFocus (true);
	
	setAlwaysOnTop (true);
	
	startTimer (50);
}

SequencerComponent::~SequencerComponent()
{
}

// Component methods
void SequencerComponent::paint (Graphics& g)
{
	g.fillAll (Colours::black);	
}

void SequencerComponent::resized()
{
}

bool SequencerComponent::keyPressed (const KeyPress& key)
{
	return Component::keyPressed (key);
}

// Timer methods
void SequencerComponent::timerCallback()
{
	if (lastPlayheadRow != sequencer->getPlayheadRow()) {
		lastPlayheadRow = sequencer->getPlayheadRow();
		repaint();
	}
}
