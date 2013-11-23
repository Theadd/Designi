/*
  ==============================================================================

    ProjectExplorerPanel.h
    Created: 22 Nov 2013 10:44:01pm
    Author:  admin

  ==============================================================================
*/

#ifndef PROJECTEXPLORERPANEL_H_INCLUDED
#define PROJECTEXPLORERPANEL_H_INCLUDED

#include "../Basics/InnerPanel.h"

class FileTreePanel;

class ProjectExplorerPanel :	public InnerPanel
{
public:

	ProjectExplorerPanel (Project& p);
	~ProjectExplorerPanel ();

	OpenDocumentManager::Document* getDocument() const override             { return nullptr; }
	ValueTree getNavigatorTree () override									{ return ValueTree::invalid; }

	void resized ();
	void mouseUp (const MouseEvent &event);


private:
	ScopedPointer <FileTreePanel> fileTreePanelA;
	//ScopedPointer <ExtendedFileTreeComponent> fileTreeCompB;

    TextButton selectfileTreePanelA;
	//TextButton selectFileTreeB;
};


#endif  // PROJECTEXPLORERPANEL_H_INCLUDED
