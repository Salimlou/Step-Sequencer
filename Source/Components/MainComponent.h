/*
 *  MainComponent.h
 *  audio_playhead1
 *
 *  Created by Matt Sonic on 5/4/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#ifndef MainComponent_H
#define MainComponent_H

#include "JuceHeader.h"

class PluginAudioProcessor;

class MainComponent : 
public Component,
public Timer
{
public:
	MainComponent (PluginAudioProcessor* pluginAudioProcessor_);
	~MainComponent();
	
	// Component methods
	virtual void paint (Graphics& g);
	virtual void resized();

	// Timer methods
	virtual void timerCallback();

private:
	PluginAudioProcessor* pluginAudioProcessor;
	Label* positionLabel;	
	AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;
};

#endif
