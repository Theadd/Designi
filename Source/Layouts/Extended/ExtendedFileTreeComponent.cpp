/*
  ==============================================================================

    ExtendedFileTreeComponent.cpp
    Created: 8 Nov 2013 7:47:58pm
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "ExtendedFileTreeComponent.h"
#include "../ExtendedLookAndFeel.h"
#include "plain-svg-icons.h"


class ExtendedFileListTreeItem   : public TreeViewItem,
                           private TimeSliceClient,
                           private AsyncUpdater,
                           private ChangeListener,
						   public Component
{
public:
    ExtendedFileListTreeItem (ExtendedFileTreeComponent& treeComp,
                      DirectoryContentsList* const parentContents,
                      const int indexInContents,
                      const File& f,
                      TimeSliceThread& t)
        : file (f),
          owner (treeComp),
          parentContentsList (parentContents),
          indexInContentsList (indexInContents),
          subContentsList (nullptr, false),
          thread (t),
		  Component("ExtendedFileListTreeItem")
    {
		setName("ExtendedFileListTreeItem for "+f.getFileName());
		normalIcon = nullptr;
		hoverIcon = nullptr;
		selectedIcon = nullptr;
        DirectoryContentsList::FileInfo fileInfo;

        if (parentContents != nullptr
             && parentContents->getFileInfo (indexInContents, fileInfo))
        {
            fileSize = File::descriptionOfSizeInBytes (fileInfo.fileSize);
            modTime = fileInfo.modificationTime.formatted ("%d %b '%y %H:%M");
            isDirectory = fileInfo.isDirectory;
        }
        else
        {
            isDirectory = true;
        }
		//addMouseListener(this, false);
    }

    ~ExtendedFileListTreeItem()
    {
        thread.removeTimeSliceClient (this);
        clearSubItems();
        removeSubContentsList();
		normalIcon = nullptr;
		hoverIcon = nullptr;
		selectedIcon = nullptr;
    }

    //==============================================================================
    bool mightContainSubItems() override                 { return isDirectory; }
    String getUniqueName() const override                { return file.getFullPathName(); }
    int getItemHeight() const override                   { return owner.getItemHeight(); }

    var getDragSourceDescription() override              { return owner.getDragAndDropDescription(); }

    void itemOpennessChanged (bool isNowOpen) override
    {
        if (isNowOpen)
        {
            clearSubItems();

            isDirectory = file.isDirectory();

            if (isDirectory)
            {
                if (subContentsList == nullptr)
                {
                    jassert (parentContentsList != nullptr);

                    DirectoryContentsList* const l = new DirectoryContentsList (parentContentsList->getFilter(), thread);

                    l->setDirectory (file,
                                     parentContentsList->isFindingDirectories(),
                                     parentContentsList->isFindingFiles());

                    setSubContentsList (l, true);
                }

                changeListenerCallback (nullptr);
            }
        }
		updateIcon(true, true);
    }

    void removeSubContentsList()
    {
        if (subContentsList != nullptr)
        {
            subContentsList->removeChangeListener (this);
            subContentsList.clear();
        }
    }

    void setSubContentsList (DirectoryContentsList* newList, const bool canDeleteList)
    {
        removeSubContentsList();

        OptionalScopedPointer<DirectoryContentsList> newPointer (newList, canDeleteList);
        subContentsList = newPointer;
        newList->addChangeListener (this);
    }

    bool selectFile (const File& target)
    {
        if (file == target)
        {
            setSelected (true, true);
            return true;
        }

        if (target.isAChildOf (file))
        {
            setOpen (true);

            for (int maxRetries = 500; --maxRetries > 0;)
            {
                for (int i = 0; i < getNumSubItems(); ++i)
                    if (ExtendedFileListTreeItem* f = dynamic_cast <ExtendedFileListTreeItem*> (getSubItem (i)))
                        if (f->selectFile (target))
                            return true;

                // if we've just opened and the contents are still loading, wait for it..
                if (subContentsList != nullptr && subContentsList->isStillLoading())
                {
                    Thread::sleep (10);
                    rebuildItemsFromContentList();
                }
                else
                {
                    break;
                }
            }
        }

        return false;
    }

    void changeListenerCallback (ChangeBroadcaster*) override
    {
        rebuildItemsFromContentList();
    }

    void rebuildItemsFromContentList()
    {
        clearSubItems();

        if (isOpen() && subContentsList != nullptr)
        {
            for (int i = 0; i < subContentsList->getNumFiles(); ++i)
                addSubItem (new ExtendedFileListTreeItem (owner, subContentsList, i,
                                                  subContentsList->getFile(i), thread));
        }
    }

    void paintItem (Graphics& g, int width, int height) override
    {
		if (file != File::nonexistent)
		{
			updateIcon(true);

			if (normalIcon == nullptr)
				thread.addTimeSliceClient (this);
		}

		bool isItemUnderMouse = (owner.itemUnderMouse == this) ? true : false;
		bool selected = isSelected();
		//DBG("[ITEM] "+file.getFileName()+" getItemPosition(): "+getItemPosition(true).toString()+" owner.getScreenBounds(): "+owner.getScreenBounds().toString()+" Item size: "+String(width)+", "+String(height));
		//DBG("[ITEM] "+file.getFileName()+" getItemPosition(): "+getItemPosition(true).toString()+" isItemUnderMouse: "+String(isItemUnderMouse));

		

		Drawable *icon;
		if (selected)
			icon = selectedIcon;
		else if (isItemUnderMouse)
			icon = hoverIcon;
		else
			icon = normalIcon;

		((ExtendedLookAndFeel*) &getLookAndFeel())->drawFileBrowserRow (g, width, height,
                                         file.getFileName(), icon,
										 fileSize, modTime, false, selected,
										 isOpen(), isItemUnderMouse,
                                         indexInContentsList, owner);
        /*if (file != File::nonexistent)
        {
            updateIcon (true);

            if (icon.isNull())
                thread.addTimeSliceClient (this);
        }

        owner.getLookAndFeel().drawFileBrowserRow (g, width, height,
                                                   file.getFileName(),
                                                   &icon, fileSize, modTime,
                                                   isDirectory, false, //isOpen(),
                                                   indexInContentsList, owner);*/
    }

    void itemClicked (const MouseEvent& e) override
    {
        owner.sendMouseClickMessage (file, e);
    }

    void itemDoubleClicked (const MouseEvent& e) override
    {
        TreeViewItem::itemDoubleClicked (e);

        owner.sendDoubleClickMessage (file);
    }

    void itemSelectionChanged (bool) override
    {
        owner.sendSelectionChangeMessage();
    }

    int useTimeSlice() override
    {
        updateIcon (false);
        return -1;
    }

    void handleAsyncUpdate() override
    {
        owner.repaint();
    }

	/*bool isMouseHover()
	{
		MouseInputSource mouse = Desktop::getInstance().getMainMouseSource();

		Rectangle<int> ownerScreenBounds = owner.getScreenBounds();
		Rectangle<int> itemPosition = getItemPosition(true);
		Rectangle<int> itemScreenBounds(ownerScreenBounds.getX() + itemPosition.getX(), ownerScreenBounds.getY() + itemPosition.getY(), itemPosition.getWidth(), itemPosition.getHeight());
		
		if (itemScreenBounds.contains(mouse.getScreenPosition()))
			return true;

		return false;
	}*/

    const File file;

private:
    ExtendedFileTreeComponent& owner;
    DirectoryContentsList* parentContentsList;
    int indexInContentsList;
    OptionalScopedPointer<DirectoryContentsList> subContentsList;
    bool isDirectory;
    TimeSliceThread& thread;
    Image icon;
    String fileSize, modTime;
	ScopedPointer<Drawable> normalIcon;
	ScopedPointer<Drawable> hoverIcon;
	ScopedPointer<Drawable> selectedIcon;

	String getIconNameForFile(String filename)
	{
		String id;
		if (!isDirectory)
		{
			id = filename.fromLastOccurrenceOf(".", true, true);
			//DBG("[getIconNameForFile] "+filename+" id=["+id+"]");
			if (id.isEmpty())
				id = "note.svg";
			else
			{
				if (id.equalsIgnoreCase(".cpp"))
					id = "file-cpp.svg";
				else if (id.equalsIgnoreCase(".h"))
					id = "file-header.svg";
				else if (id.equalsIgnoreCase(".design"))
					id = "pen-brush.svg";
				else
					id = "file.svg";
			}
		}
		else
		{
			if (isOpen())
				id = "folder-open.svg";
			else
				id = "folder-close.svg";
		}

		return id;
	}

	void HighlightActiveColorFromSVG(XmlElement* xmlSource, bool blackAndWhite = false)
	{
		forEachXmlChildElement (*xmlSource, xmlnode)
		{
			forEachXmlChildElement (*xmlnode, xmlouterdefs)
			{
				forEachXmlChildElement (*xmlouterdefs, xmldefs)
				{
					String style = xmldefs->getStringAttribute("style");
					if (style.isNotEmpty())
					{
						if (!blackAndWhite)
						{
							style = style.replace("#008bff", "#e8d500", true);
							style = style.replace("#00aaff", "#ffea00", true);
							style = style.replace("#4eafff", "#ffdc00", true);
						}
						else
						{
							style = style.replace("#008bff", "#eaeaea", true);
							style = style.replace("#00aaff", "#d3d3d3", true);
							style = style.replace("#4eafff", "#d8d8d8", true);
						}
						
						xmldefs->setAttribute("style", style);
					}
				}
			}
		}
	}

	/** highlight: {0 = blue, 1 = yellow, 2 = light gray} */
	Drawable* getDrawableFromZipFile(String filename, int highlight = 0)
	{
		MemoryInputStream iconsFileStream (plainsvgicons_zip, plainsvgicons_zipSize, false);
		ZipFile icons (&iconsFileStream, false);

		const ZipFile::ZipEntry* zipEntry = icons.getEntry(filename);
		InputStream* stream = icons.createStreamForEntry(*zipEntry);
		String xmldata = stream->readEntireStreamAsString();
		delete stream;
		ScopedPointer<XmlElement> svg (XmlDocument::parse (xmldata));//(BinaryData::wrench_svg));

		if (highlight == 1)
			HighlightActiveColorFromSVG(svg);
		if (highlight == 2)
			HighlightActiveColorFromSVG(svg, true);

		if (svg != nullptr)
			return Drawable::createFromSVG (*svg);

		return nullptr;
	}

	/** Update icons for TreeView Item if they are not already set.
	 * @param onlyUpdateIfCached bool unused since we don't have a cache for drawables like ImageCache
	 * @param openStateChanged bool force update, used when a directory changes its open state.
	 */
    void updateIcon (const bool /*onlyUpdateIfCached*/, bool openStateChanged = false)
    {
		if (normalIcon == nullptr || openStateChanged == true)
		{
			String iconName = getIconNameForFile(file.getFileName());
			normalIcon = getDrawableFromZipFile(iconName, 0);
			hoverIcon = getDrawableFromZipFile(iconName, 1);
			selectedIcon = getDrawableFromZipFile(iconName, 2);

			triggerAsyncUpdate();
		}
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExtendedFileListTreeItem)
};


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
