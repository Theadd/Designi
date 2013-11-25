/*
  ==============================================================================

    ExtendedFileTreeComponent.cpp
    Created: 8 Nov 2013 7:47:58pm
    Author:  admin

  ==============================================================================
*/

#include "../../../Headers.h"
#include "ExtendedFileTreeComponent.h"
#include "../../Styles/ExtendedLookAndFeel.h"
#include "../../Styles/plain-svg-icons.h"


#include "ExtendedFileListTreeItem.h"

ExtendedFileTreeComponent::ExtendedFileTreeComponent (DirectoryContentsList& listToShow) : DirectoryContentsDisplayComponent (listToShow),
      itemHeight (22)
{
    setRootItemVisible (false);
    refresh();
	addMouseListener(this, true);
}


ExtendedFileTreeComponent::~ExtendedFileTreeComponent()
{
    deleteRootItem();
}
 
void ExtendedFileTreeComponent::mouseMove (const MouseEvent &event)
{
	int mousePosition = event.getPosition().getY() - getViewport()->getViewPositionY();
	ExtendedFileListTreeItem* item = (ExtendedFileListTreeItem *) getItemAt(mousePosition);

	if (item != nullptr && itemUnderMouse != item)
	{
		itemUnderMouse = item;
		repaint();
	}
}

void ExtendedFileTreeComponent::mouseExit (const MouseEvent& /*event*/)
{
	itemUnderMouse = nullptr;
	repaint();
}

void ExtendedFileTreeComponent::refresh()
{
    deleteRootItem();

    ExtendedFileListTreeItem* const root
        = new ExtendedFileListTreeItem (*this, nullptr, 0, fileList.getDirectory(),
                                fileList.getTimeSliceThread());

    root->setSubContentsList (&fileList, false);
    setRootItem (root);
}

//==============================================================================
File ExtendedFileTreeComponent::getSelectedFile (const int index) const
{
    if (const ExtendedFileListTreeItem* const item = dynamic_cast <const ExtendedFileListTreeItem*> (getSelectedItem (index)))
        return item->file;

    return File::nonexistent;
}

void ExtendedFileTreeComponent::deselectAllFiles()
{
    clearSelectedItems();
}

void ExtendedFileTreeComponent::scrollToTop()
{
    getViewport()->getVerticalScrollBar()->setCurrentRangeStart (0);
}

void ExtendedFileTreeComponent::setDragAndDropDescription (const String& description)
{
    dragAndDropDescription = description;
}

void ExtendedFileTreeComponent::setSelectedFile (const File& target)
{
    if (ExtendedFileListTreeItem* t = dynamic_cast <ExtendedFileListTreeItem*> (getRootItem()))
        if (! t->selectFile (target))
            clearSelectedItems();
}

void ExtendedFileTreeComponent::setItemHeight (int newHeight)
{
    if (itemHeight != newHeight)
    {
        itemHeight = newHeight;

        if (TreeViewItem* root = getRootItem())
            root->treeHasChanged();
    }
}
