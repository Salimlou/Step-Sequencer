/*
 *  PluginAudioProcessorEditor.h
 *  audio_playhead4
 *
 *  Created by Matt Sonic on 5/2/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#ifndef PLUGIN_AUDIO_PROCESSOR_EDITOR_H
#define PLUGIN_AUDIO_PROCESSOR_EDITOR_H

#include "JuceHeader.h"
#include "JucePluginCharacteristics.h"

class PluginAudioProcessor;
class MainComponent;

class PluginAudioProcessorEditor : 
public AudioProcessorEditor,
public ComponentListener
{
public:
    PluginAudioProcessorEditor (PluginAudioProcessor* pluginAudioProcessor);
    ~PluginAudioProcessorEditor();

    PluginAudioProcessor* getPluginAudioProcessor() const;

	// Component methods
    virtual void paint (Graphics& g);
	virtual void resized();
	
	// ComponentListener methods
	virtual void componentParentHierarchyChanged (Component& component);	

private:
	ResizableCornerComponent* resizer;
	ComponentBoundsConstrainer resizeLimits;
	MainComponent* mainComponent;
};

#endif 
