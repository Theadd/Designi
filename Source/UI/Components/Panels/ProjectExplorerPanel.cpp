/*
  ==============================================================================

    ProjectExplorerPanel.cpp
    Created: 22 Nov 2013 10:44:02pm
    Author:  admin

  ==============================================================================
*/

#include "../../../Headers.h"
#include "../../../Core/Project.h"
#include "ProjectExplorerPanel.h"
#include "ProjectExplorerPanel/JucerTreeViewBase.h"

#include "../../Windows/MainWindow/MainLayout.h"
#include "../../../Application.h"


class FileTreePanel   : public TreePanelBase
{
public:
    FileTreePanel (Project& p)
        : TreePanelBase (&p, "fileTreeState")
    {
        tree.setMultiSelectEnabled (true);
        setRoot (new GroupItem (p.getMainGroup()));
    }

    void updateMissingFileStatuses()
    {
        if (ProjectTreeItemBase* p = dynamic_cast<ProjectTreeItemBase*> (rootItem.get()))
            p->checkFileStatus();
    }

	
    #include "ProjectExplorerPanel/ProjectTree_Base.h"
    #include "ProjectExplorerPanel/ProjectTree_Group.h"
    #include "ProjectExplorerPanel/ProjectTree_File.h"
};

ProjectExplorerPanel::ProjectExplorerPanel (Project& p)
{
	setName ("Project Explorer");
	addAndMakeVisible(fileTreePanelA = new FileTreePanel(p));
	selectfileTreePanelA.setBounds(120, 5, 20, 20);
	selectfileTreePanelA.setName("selectFileTreeA");
	selectfileTreePanelA.setButtonText("A");
	selectfileTreePanelA.setConnectedEdges(Button::ConnectedOnRight);
	selectfileTreePanelA.setTooltip("File browser remembers two locations, A and B. Use these buttons to switch between them.");
	addAndMakeVisible(&selectfileTreePanelA);

	/*selectfileTreePanelB.setBounds(140, 5, 20, 20);
	selectfileTreePanelB.setName("selectFileTreeB");
	selectfileTreePanelB.setButtonText("B");
	selectfileTreePanelB.setConnectedEdges(Button::ConnectedOnLeft);
	selectfileTreePanelB.setTooltip("File browser remembers two locations, A and B. Use these buttons to switch between them.");
	addAndMakeVisible(&selectfileTreePanelB);*/

	//ADD this to the mouse listeners of "A" and "B" buttons.
	selectfileTreePanelA.addMouseListener(this, false);
	//selectFileTreeB.addMouseListener(this, false);
}

ProjectExplorerPanel::~ProjectExplorerPanel ()
{
	fileTreePanelA = nullptr;
}

void ProjectExplorerPanel::resized ()
{
	if (fileTreePanelA != nullptr)
		fileTreePanelA->setBoundsInset (BorderSize<int> (31, 0, 0, 0));
	/*if (fileTreeCompB != nullptr)
		fileTreeCompB->setBoundsInset (BorderSize<int> (31, 0, 0, 0));*/

	selectfileTreePanelA.setBounds(getWidth() - 45, 5, 20, 20);
	//selectfileTreePanelB.setBounds(getWidth() - 25, 5, 20, 20);
}

void ProjectExplorerPanel::mouseUp (const MouseEvent &event)
{

}
