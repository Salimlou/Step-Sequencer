/*
 *  MyTableListBox.cpp
 *  midi_sequencer1
 *
 *  Created by Matt Sonic on 6/15/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "MyTableListBox.h"

MyTableListBox::MyTableListBox(const String& componentName,
							   TableListBoxModel* model) :
TableListBox (componentName, model)
{
}

MyTableListBox::~MyTableListBox()
{
}

// ListBox methods
bool MyTableListBox::keyPressed (const KeyPress& key)
{
	if (key.isKeyCode (KeyPress::upKey)
		|| key.isKeyCode (KeyPress::downKey)) {
		return false;
	}

	return TableListBox::keyPressed (key);
}

