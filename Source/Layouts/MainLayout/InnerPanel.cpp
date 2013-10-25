/*
  ==============================================================================

    InnerPanel.cpp
    Created: 18 Oct 2013 6:16:30pm
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../Globals.h"
#include "../ExtendedLookAndFeel.h"
#include "InnerPanel.h"

InnerPanel::InnerPanel(bool showAsTab_, Globals::Position _position) : Component(), showAsTab(showAsTab_), position(_position)
{
	
}


void InnerPanel::paint (Graphics& g)
{
	((ExtendedLookAndFeel*) &getLookAndFeel())->drawInnerPanel (g, *this);
}