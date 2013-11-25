/*
  ==============================================================================

    KeyMappingsPanel.h
    Created: 25 Nov 2013 9:58:16pm
    Author:  admin

  ==============================================================================
*/

#ifndef KEYMAPPINGSPANEL_H_INCLUDED
#define KEYMAPPINGSPANEL_H_INCLUDED

#include "../Basics/InnerPanel.h"

class KeyMappingsPanel   : public InnerPanel
{
public:
    KeyMappingsPanel();

	OpenDocumentManager::Document* getDocument() const override             { return nullptr; }
	ValueTree getNavigatorTree () override									{ return ValueTree::invalid; }

    void paint (Graphics& g) override;

    void resized() override;

private:
    KeyMappingEditorComponent keyMappingEditor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyMappingsPanel);
};


#endif  // KEYMAPPINGSPANEL_H_INCLUDED
