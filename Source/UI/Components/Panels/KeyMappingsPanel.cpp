/*
  ==============================================================================

    KeyMappingsPanel.cpp
    Created: 25 Nov 2013 9:58:16pm
    Author:  admin

  ==============================================================================
*/
#include "../../../Headers.h"
#include "KeyMappingsPanel.h"
#include "../../../Application.h"

KeyMappingsPanel::KeyMappingsPanel() : keyMappingEditor (*(JUCEDesignerApp::getApp().getApplicationCommandManager()->getKeyMappings()), true)
{
    //setOpaque (true);
	setLocalisedName("Key Mappings", "Options page to view/change shortcut key mappings.");
    addAndMakeVisible (&keyMappingEditor);
}

/*void KeyMappingsPanel::paint (Graphics& g) override
{
    g.fillAll (Colour::greyLevel (0.93f));
}*/

void KeyMappingsPanel::resized() override
{
    keyMappingEditor.setBounds (getLocalBounds());
}