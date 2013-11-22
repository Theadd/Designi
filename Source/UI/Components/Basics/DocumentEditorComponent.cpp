
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

#include "../../../Headers.h"
#include "DocumentEditorComponent.h"

#include "InnerPanelContainers.h"
#include "../../../Application.h"


//==============================================================================
DocumentEditorComponent::DocumentEditorComponent (OpenDocumentManager::Document* doc)
    : document (doc), navigatorTree ("navigator")
{
	DBG("DocumentEditorComponent getName(): "+getName());
    JUCEDesignerApp::getApp().openDocumentManager.addListener (this);
}

DocumentEditorComponent::~DocumentEditorComponent()
{
    JUCEDesignerApp::getApp().openDocumentManager.removeListener (this);
}

bool DocumentEditorComponent::documentAboutToClose (OpenDocumentManager::Document* closingDoc)
{
    if (document == closingDoc)
    {
        jassert (document != nullptr);

		//TOFIX
		//if (Panel* panel = findParentComponentOfClass<Panel>())
        //    panel->removeInnerPanel (document);	//SOMETHING LIKE: JUCEDesignerApp::getApp().getInnerPanelForDocument(document)
    }

    return true;
}

void DocumentEditorComponent::setEditedState (bool /*hasBeenEdited*/)
{
    //TOFIX
	//if (ProjectContentComponent* pcc = findParentComponentOfClass<ProjectContentComponent>())
    //    pcc->updateMainWindowTitle();
}
