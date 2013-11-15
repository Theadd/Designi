/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2013 - Raw Material Software Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#ifndef __DOCUMENTEDITORCOMPONENT_H_5C0018A9__
#define __DOCUMENTEDITORCOMPONENT_H_5C0018A9__

#include "../../Core/DocumentManager.h"
#include "../MainLayout/InnerPanel.h"


//==============================================================================
/**
*/
class DocumentEditorComponent  : public InnerPanel,
                                 public OpenDocumentManager::DocumentCloseListener
{
public:
    //==============================================================================
    DocumentEditorComponent (OpenDocumentManager::Document* document);
    ~DocumentEditorComponent();

    OpenDocumentManager::Document* getDocument() const override				{ return document; }
	virtual CodeDocument& getCodeDocument () = 0;
	ValueTree getNavigatorTree () override									{ return ValueTree::invalid; }

    bool documentAboutToClose (OpenDocumentManager::Document*) override;

	ValueTree navigatorTree;

protected:
    OpenDocumentManager::Document* document;

    void setEditedState (bool hasBeenEdited);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DocumentEditorComponent)
};


#endif  // __DOCUMENTEDITORCOMPONENT_H_5C0018A9__