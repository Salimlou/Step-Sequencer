/*
 *  PluginAudioProcessorEditor.h
 *  plugin_template1
 *
 *  Created by Matt Sonic on 5/2/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#ifndef PLUGIN_AUDIO_PROCESSOR_EDITOR_H
#define PLUGIN_AUDIO_PROCESSOR_EDITOR_H

#include "JuceHeader.h"
#include "JucePluginCharacteristics.h"
#include "PluginAudioProcessor.h"

class MainComponent;

class PluginAudioProcessorEditor : public AudioProcessorEditor
{
public:
    PluginAudioProcessorEditor (PluginAudioProcessor* ownerFilter);
    ~PluginAudioProcessorEditor();

	// Component methods
    virtual void paint (Graphics& g);
	virtual void resized();

private:
	ResizableCornerComponent* resizer;
	ComponentBoundsConstrainer resizeLimits;
	MainComponent* mainComponent;
};

#endif 
