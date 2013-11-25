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
	setLocalisedName("Project Explorer", "Your project directory tree");
	addAndMakeVisible(fileTreePanelA = new FileTreePanel(p));
	addAndMakeVisible(fileTreePanelB = new FileTreePanel(p));
	fileTreePanelB->setVisible(false);

	selectfileTreePanelA.setBounds(120, 5, 20, 20);
	selectfileTreePanelA.setName("selectProjectTreeA");
	selectfileTreePanelA.setButtonText("A");
	selectfileTreePanelA.setConnectedEdges(Button::ConnectedOnRight);
	selectfileTreePanelA.setTooltip("Project explorer remembers two locations, A and B. Use these buttons to switch between them.");
	addAndMakeVisible(&selectfileTreePanelA);

	selectfileTreePanelB.setBounds(140, 5, 20, 20);
	selectfileTreePanelB.setName("selectProjectTreeB");
	selectfileTreePanelB.setButtonText("B");
	selectfileTreePanelB.setConnectedEdges(Button::ConnectedOnLeft);
	selectfileTreePanelB.setTooltip("Project explorer remembers two locations, A and B. Use these buttons to switch between them.");
	addAndMakeVisible(&selectfileTreePanelB);

	//ADD this to the mouse listeners of "A" and "B" buttons.
	selectfileTreePanelA.addMouseListener(this, false);
	selectfileTreePanelB.addMouseListener(this, false);
	setHeader(true, p.getTitle(), 30, 5, 45, 0);
}

ProjectExplorerPanel::~ProjectExplorerPanel ()
{
	fileTreePanelA = nullptr;
}

void ProjectExplorerPanel::resized ()
{
	if (fileTreePanelA != nullptr)
		fileTreePanelA->setBoundsInset (BorderSize<int> (31, 0, 0, 0));
	if (fileTreePanelB != nullptr)
		fileTreePanelB->setBoundsInset (BorderSize<int> (31, 0, 0, 0));

	selectfileTreePanelA.setBounds(getWidth() - 45, 5, 20, 20);
	selectfileTreePanelB.setBounds(getWidth() - 25, 5, 20, 20);
}

void ProjectExplorerPanel::mouseUp (const MouseEvent &event)
{
	if (event.mouseWasClicked()) {
		if (event.eventComponent == &selectfileTreePanelA) {
			fileTreePanelA->setVisible(true);
			fileTreePanelB->setVisible(false);
		} else if (event.eventComponent == &selectfileTreePanelB) {
			fileTreePanelA->setVisible(false);
			fileTreePanelB->setVisible(true);
		}
	}
}
