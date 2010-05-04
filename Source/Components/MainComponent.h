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

class MainComponent : public Component
{
public:
	MainComponent (PluginAudioProcessor* pluginAudioProcessor_);
	~MainComponent();
	
	// Component methods
	virtual void paint (Graphics& g);
	virtual void resized();

private:
	PluginAudioProcessor* pluginAudioProcessor;
};

#endif
