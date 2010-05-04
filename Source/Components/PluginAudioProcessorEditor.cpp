/*
 *  PluginAudioProcessorEditor.cpp
 *  plugin_template1
 *
 *  Created by Matt Sonic on 5/2/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "PluginAudioProcessor.h"

#include "PluginAudioProcessorEditor.h"

PluginAudioProcessorEditor::PluginAudioProcessorEditor (PluginAudioProcessor* ownerFilter) : 
AudioProcessorEditor (ownerFilter),
resizer (0)
{
	resizeLimits.setSizeLimits (600, 400, 1200, 800);
	addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    
	setSize (600, 400);
}

PluginAudioProcessorEditor::~PluginAudioProcessorEditor()
{
}

// Component methods
void PluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!",
                      0, 0, getWidth(), getHeight(),
                      Justification::centred, 1);
}

void PluginAudioProcessorEditor::resized() 
{
	resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
}
