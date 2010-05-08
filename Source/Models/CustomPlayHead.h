/*
 *  CustomPlayHead.h
 *  audio_playhead3
 *
 *  Created by Matt Sonic on 5/7/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#ifndef CustomPlayHead_H
#define CustomPlayHead_H

#include "CustomPlayHead.h"
#include "AudioProcessorCallback.h"

#include "JuceHeader.h"

class CustomPlayHead : 
public AudioPlayHead,
public AudioProcessorCallback
{
public:
	CustomPlayHead (AudioProcessor* audioProcessor);
	~CustomPlayHead();
	
	// AudioPlayHead methods
	virtual bool getCurrentPosition (CurrentPositionInfo& result);
	
	// AudioProcessorCallback methods
	virtual void prepareToPlay (double sampleRate, int samplesPerBlock);
    virtual void releaseResources();
    virtual void processBlock (AudioSampleBuffer& buffer, 
							   MidiBuffer& midiMessages);
};

#endif
