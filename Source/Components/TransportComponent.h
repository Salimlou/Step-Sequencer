/*
 *  TransportComponent.h
 *  audio_playhead3
 *
 *  Created by Matt Sonic on 5/7/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#ifndef TransportComponent_H
#define TransportComponent_H

#include "JuceHeader.h"

class TransportComponent : 
public Component,
public ButtonListener,
public SliderListener
{
public:
	TransportComponent();
	~TransportComponent();
	
	// Component methods
	virtual void paint (Graphics& g);
	virtual void resized();
	
	// ButtonListener methods
	virtual void buttonClicked (Button* button);
	
	// SliderListener methods
	virtual void sliderValueChanged (Slider* slider);
	
private:
	Slider* bpmSlider;
	TextButton* playButton;
};

#endif
