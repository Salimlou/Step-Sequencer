/*
 *  MainComponent.h
 *  plugin_template1
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
public Timer,
public SliderListener
{
public:
	MainComponent (PluginAudioProcessor* pluginAudioProcessor_);
	~MainComponent();
	
	// Component methods
	virtual void paint (Graphics& g);
	virtual void resized();

	// Timer methods
	virtual void timerCallback();
	
	// SliderListener methods
	virtual void sliderValueChanged (Slider* slider);
	
private:
	PluginAudioProcessor* pluginAudioProcessor;
	Slider* gainSlider;
};

#endif
