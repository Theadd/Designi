/*
  ==============================================================================

    ExtendedFileTreeComponent.h
    Created: 8 Nov 2013 7:47:58pm
    Author:  admin

  ==============================================================================
*/

#ifndef __EXTENDEDFILETREECOMPONENT_H_2096201E__
#define __EXTENDEDFILETREECOMPONENT_H_2096201E__

class ExtendedLookAndFeel;
class ExtendedFileListTreeItem;

class ExtendedFileTreeComponent : public TreeView,
                                  public DirectoryContentsDisplayComponent
{
public:
	ExtendedFileTreeComponent (DirectoryContentsList& listToShow);
	/** Destructor. */
    ~ExtendedFileTreeComponent();

	void mouseMove (const MouseEvent &event);
	void mouseExit (const MouseEvent &event);

    //==============================================================================
    /** Returns the number of files the user has got selected.
        @see getSelectedFile
    */
    int getNumSelectedFiles() const                 { return TreeView::getNumSelectedItems(); }

    /** Returns one of the files that the user has currently selected.
        The index should be in the range 0 to (getNumSelectedFiles() - 1).
        @see getNumSelectedFiles
    */
    File getSelectedFile (int index = 0) override const;

    /** Deselects any files that are currently selected. */
    void deselectAllFiles() override;

    /** Scrolls the list to the top. */
    void scrollToTop() override;

    /** If the specified file is in the list, it will become the only selected item
        (and if the file isn't in the list, all other items will be deselected). */
    void setSelectedFile (const File&) override;

    /** Updates the files in the list. */
    void refresh() override;

    /** Setting a name for this allows tree items to be dragged.

        The string that you pass in here will be returned by the getDragSourceDescription()
        of the items in the tree. For more info, see TreeViewItem::getDragSourceDescription().
    */
    void setDragAndDropDescription (const String& description) override;

    /** Returns the last value that was set by setDragAndDropDescription().
    */
    const String& getDragAndDropDescription() override const noexcept    { return dragAndDropDescription; }

    /** Changes the height of the treeview items. */
    void setItemHeight (int newHeight) override;

    /** Returns the height of the treeview items. */
    int getItemHeight() override const noexcept                          { return itemHeight; }

	ExtendedFileListTreeItem* itemUnderMouse;

private:
    //==============================================================================
    String dragAndDropDescription;
    int itemHeight;

	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExtendedFileTreeComponent)
};


#endif  // __EXTENDEDFILETREECOMPONENT_H_2096201E__
