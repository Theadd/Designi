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

#ifndef __JUCER_JUCERTREEVIEWBASE_JUCEHEADER__
#define __JUCER_JUCERTREEVIEWBASE_JUCEHEADER__

#include "../../../../Headers.h"
#include "../../../Styles/plain-svg-icons.h"
//class ProjectContentComponent;
#include "../../../../Core/Project.h"
//class Project;
class MainLayout;
//class Project::Item;

//==============================================================================
class JucerTreeViewBase   : public TreeViewItem
{
public:

    JucerTreeViewBase();
    ~JucerTreeViewBase();

    int getItemWidth() const override                   { return -1; }
    int getItemHeight() const override                  { return 20; }

    void paintOpenCloseButton (Graphics&, const Rectangle<float>& area, Colour backgroundColour, bool isMouseOver) override;
    Component* createItemComponent() override;
    void itemClicked (const MouseEvent& e) override;
    void itemSelectionChanged (bool isNowSelected) override;
    void itemDoubleClicked (const MouseEvent&) override;

    void cancelDelayedSelectionTimer();

    //==============================================================================
    virtual Font getFont() const;
    virtual String getRenamingName() const = 0;
    virtual String getDisplayName() const = 0;
    virtual void setName (const String& newName) = 0;
    virtual bool isMissing() = 0;
    virtual Drawable* getIcon() = 0;
    virtual float getIconSize() const;
    virtual bool isIconCrossedOut() const               { return false; }
    virtual void paintContent (Graphics& g, const Rectangle<int>& area);
    virtual int getMillisecsAllowedForDragGesture()     { return 120; };
    virtual File getDraggableFile() const               { return File::nonexistent; }

    void refreshSubItems();
    virtual void deleteItem();
    virtual void deleteAllSelectedItems();
    virtual void showDocument();
    virtual void showMultiSelectionPopupMenu();
    virtual void showRenameBox();

    void launchPopupMenu (PopupMenu&); // runs asynchronously, and produces a callback to handlePopupMenuResult().
    virtual void showPopupMenu();
    virtual void handlePopupMenuResult (int resultCode);

    //==============================================================================
    // To handle situations where an item gets deleted before openness is
    // restored for it, this OpennessRestorer keeps only a pointer to the
    // topmost tree item.
    struct WholeTreeOpennessRestorer   : public OpennessRestorer
    {
        WholeTreeOpennessRestorer (TreeViewItem& item)  : OpennessRestorer (getTopLevelItem (item))
        {}

    private:
        static TreeViewItem& getTopLevelItem (TreeViewItem& item)
        {
            if (TreeViewItem* const p = item.getParentItem())
                return getTopLevelItem (*p);

            return item;
        }
    };

    int textX;
	bool isItemSelected;
	bool isItemMouseHover;
	ScopedPointer <Project::Item> projectItem;

protected:
    MainLayout* getProjectContentComponent() const;
    virtual void addSubItems() {}

    Colour getBackgroundColour() const;
    Colour getContrastingColour (float contrast) const;
    Colour getContrastingColour (Colour targetColour, float minContrast) const;

private:
    class ItemSelectionTimer;
    friend class ItemSelectionTimer;
    ScopedPointer<Timer> delayedSelectionTimer;

    WeakReference<JucerTreeViewBase>::Master masterReference;
    friend class WeakReference<JucerTreeViewBase>;

    void invokeShowDocument();
};

//==============================================================================
class TreePanelBase   : public Component
{
public:
    TreePanelBase (const Project* p, const String& treeviewID)
        : project (p), opennessStateKey (treeviewID)
    {
        addAndMakeVisible (&tree);
        tree.setRootItemVisible (false);
        tree.setDefaultOpenness (true);
        //tree.setColour (TreeView::backgroundColourId, Colours::transparentBlack);
        //tree.setIndentSize (14);
        //tree.getViewport()->setScrollBarThickness (14);
		itemUnderMouse = nullptr;
		addMouseListener(this, true);
    }

    ~TreePanelBase()
    {
        tree.setRootItem (nullptr);
    }

	void mouseMove (const MouseEvent &event)
	{
		int mousePosition = event.getPosition().getY() - tree.getViewport()->getViewPositionY();
		JucerTreeViewBase* item = (JucerTreeViewBase *) tree.getItemAt(mousePosition);

		if (item != nullptr && itemUnderMouse != item)
		{
			if (itemUnderMouse != nullptr)
				itemUnderMouse->isItemMouseHover = false;	//unset mouse hover from last mouse hovered item

			itemUnderMouse = item;
			item->isItemMouseHover = true;
			repaint();
		}
	}

	void mouseExit (const MouseEvent &event)
	{
		if (itemUnderMouse != nullptr)
				itemUnderMouse->isItemMouseHover = false;	//unset mouse hover from last mouse hovered item

		itemUnderMouse = nullptr;
		repaint();
	}

    void setRoot (JucerTreeViewBase* root);
    void saveOpenness();

    void deleteSelectedItems()
    {
        if (rootItem != nullptr)
            rootItem->deleteAllSelectedItems();
    }

    void setEmptyTreeMessage (const String& newMessage)
    {
        if (emptyTreeMessage != newMessage)
        {
            emptyTreeMessage = newMessage;
            repaint();
        }
    }

    static void drawEmptyPanelMessage (Component& comp, Graphics& g, const String& message)
    {
        const int fontHeight = 13;
        const Rectangle<int> area (comp.getLocalBounds());
        g.setColour (comp.findColour (mainBackgroundColourId).contrasting (0.7f));
        g.setFont ((float) fontHeight);
        g.drawFittedText (message, area.reduced (4, 2), Justification::centred, area.getHeight() / fontHeight);
    }

    void paint (Graphics& g) override
    {
        if (emptyTreeMessage.isNotEmpty() && (rootItem == nullptr || rootItem->getNumSubItems() == 0))
            drawEmptyPanelMessage (*this, g, emptyTreeMessage);
    }

    void resized() override
    {
        tree.setBounds (getAvailableBounds());
    }

    Rectangle<int> getAvailableBounds() const
    {
        return Rectangle<int> (0, 0, getWidth(), getHeight());
    }

    const Project* project;
    TreeView tree;
    ScopedPointer<JucerTreeViewBase> rootItem;
	JucerTreeViewBase* itemUnderMouse;

private:
    String opennessStateKey, emptyTreeMessage;
};

//==============================================================================
class TreeItemComponent   : public Component
{
public:
    TreeItemComponent (JucerTreeViewBase& i)  : item (i), activeItemIconName("")
    {
        setInterceptsMouseClicks (false, true);
		normalIcon = nullptr;
		hoverIcon = nullptr;
		selectedIcon = nullptr;
		isIconForOpenState = false;
    }

    void paint (Graphics& g) override
    {
        g.setColour (Colours::black);
        paintIcon (g);
        item.paintContent (g, Rectangle<int> (item.textX, 0, getWidth() - item.textX, getHeight()));
    }

    void paintIcon (Graphics& g)
    {
		if (normalIcon == nullptr || isIconForOpenState != item.isOpen())
		{
			String activeItemIconName = getIconNameForItem();
			normalIcon = Icons::get (activeItemIconName, Icons::lightgray);
			hoverIcon = Icons::get(activeItemIconName, Icons::yellow);
			selectedIcon = Icons::get(activeItemIconName, Icons::blue);
		}
		float opacity = (item.isIconCrossedOut()) ? 0.4f : 1.0f;
		Drawable* icon = (item.isItemSelected) ? selectedIcon : ((item.isItemMouseHover) ? hoverIcon : normalIcon);
        icon->drawWithin (g, Rectangle<float> (4.0f, 2.0f, item.getIconSize(), getHeight() - 4.0f),
                             RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, opacity);
	}

    void resized() override
    {
        item.textX = (int) item.getIconSize() + 8;
    }

    JucerTreeViewBase& item;
	ScopedPointer <Drawable> normalIcon;
	ScopedPointer <Drawable> hoverIcon;
	ScopedPointer <Drawable> selectedIcon;
	String activeItemIconName;
	bool isIconForOpenState;

private:

	String getIconNameForItem ()
	{
		if (item.projectItem == nullptr || !item.projectItem->isValid())
			return String("note.svg");

		String id;
		if (item.projectItem->isFile())
		{
			id = item.getDisplayName().fromLastOccurrenceOf(".", true, true);

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
				else if (id.equalsIgnoreCase(".zip"))
					id = "archive.svg";
				else if (id.equalsIgnoreCase(".gz"))
					id = "archive.svg";
				else if (id.equalsIgnoreCase(".bz2"))
					id = "archive.svg";
				else if (id.equalsIgnoreCase(".png"))
					id = "picture.svg";
				else if (id.equalsIgnoreCase(".svg"))
					id = "picture.svg";
				else
					id = "file.svg";
			}
		}
		else
		{
			if (item.isOpen())
				id = "folder-open.svg";
			else
				id = "folder-close.svg";
		}
		return id;
	}
};


#endif   // __JUCER_JUCERTREEVIEWBASE_JUCEHEADER__
