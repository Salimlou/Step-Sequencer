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
AudioProcessorEditor (ownerFilter)
{
    setSize (400, 300);
}

PluginAudioProcessorEditor::~PluginAudioProcessorEditor()
{
}

void PluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!",
                      0, 0, getWidth(), getHeight(),
                      Justification::centred, 1);
}
