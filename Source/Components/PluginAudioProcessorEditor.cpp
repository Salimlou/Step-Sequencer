/*
 *  PluginAudioProcessorEditor.cpp
 *  plugin_template1
 *
 *  Created by Matt Sonic on 5/2/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "MainComponent.h"
#include "PluginAudioProcessor.h"

#include "PluginAudioProcessorEditor.h"

PluginAudioProcessorEditor::PluginAudioProcessorEditor (PluginAudioProcessor* pluginAudioProcessor) : 
AudioProcessorEditor (pluginAudioProcessor),
resizer (0),
mainComponent (0)
{
	addAndMakeVisible (mainComponent = new MainComponent());

	resizeLimits.setSizeLimits (600, 400, 1200, 800);
	addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
	
	setSize (600, 400);
}

PluginAudioProcessorEditor::~PluginAudioProcessorEditor()
{
	deleteAllChildren();
}

PluginAudioProcessor* PluginAudioProcessorEditor::getPluginAudioProcessor() const
{
	return static_cast <PluginAudioProcessor*> (getAudioProcessor());
}	

// Component methods
void PluginAudioProcessorEditor::paint (Graphics& g)
{
}

void PluginAudioProcessorEditor::resized() 
{
	mainComponent->setBounds (0, 0, getWidth(), getHeight());
	resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
}
