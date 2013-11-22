/*
  ==============================================================================

    Toolbars.cpp
    Created: 15 Oct 2013 1:23:41am
    Author:  admin

  ==============================================================================
*/

#include "../../../Headers.h"
#include "Toolbars.h"
#include "../../Styles/plain-svg-icons.h"
#include "../../../Application.h"
#include "MainLayout.h"

ToolbarComponent::ToolbarComponent(int _toolbarThickness) : toolbarThickness(_toolbarThickness)
{
    // Create and add the toolbar...
    addAndMakeVisible (&toolbar);
	_isVertical = false;

    // And use our item factory to add a set of default icons to it...
    toolbar.addDefaultItems (factory);
}

void ToolbarComponent::resized()
{
    

    if (toolbar.isVertical())
        toolbar.setBounds (getLocalBounds().removeFromLeft (toolbarThickness));
    else
        toolbar.setBounds (getLocalBounds().removeFromTop  (toolbarThickness));
}

void ToolbarComponent::setVertical (bool shouldBeVertical)
{
	_isVertical = shouldBeVertical;
	toolbar.setVertical(shouldBeVertical);
	resized();
}

bool ToolbarComponent::isVertical ()
{
	return _isVertical;
}

void ToolbarComponent::showCustomisationDialog ()
{
	toolbar.showCustomisationDialog (factory);
}

int ToolbarComponent::getToolbarThickness()
{
	return toolbarThickness;
}

void ToolbarComponent::setToolbarThickness(int newThickness)
{
	toolbarThickness = newThickness;
	resized();
}

ToolbarComponent::ToolbarComponentItemFactory::ToolbarComponentItemFactory()
{

}

void ToolbarComponent::ToolbarComponentItemFactory::getAllToolbarItemIds (Array <int>& ids)
{
    // This returns the complete list of all item IDs that are allowed to
    // go in our toolbar. Any items you might want to add must be listed here. The
    // order in which they are listed will be used by the toolbar customisation panel.

    ids.add (doc_open);
    ids.add (doc_save);
	ids.add (project_close);
    ids.add (edit_undo);
    ids.add (edit_redo);
	ids.add (edit_cut);
	ids.add (edit_copy);
	ids.add (edit_paste);
	ids.add (edit_delete);
	ids.add (component_inspector);
	/*
				doc_open		= 1,
			doc_save		= 2,
			edit_undo		= 3,
			edit_redo		= 4
			*/

    // If you're going to use separators, then they must also be added explicitly
    // to the list.
    ids.add (separatorBarId);
    ids.add (spacerId);
    ids.add (flexibleSpacerId);
}

void ToolbarComponent::ToolbarComponentItemFactory::getDefaultItemSet (Array <int>& ids)
{
    // This returns an ordered list of the set of items that make up a
    // toolbar's default set. Not all items need to be on this list, and
    // items can appear multiple times (e.g. the separators used here).
    ids.add (doc_open);
    ids.add (doc_save);
	ids.add (project_close);
    ids.add (separatorBarId);
    ids.add (edit_undo);
    ids.add (edit_redo);
	ids.add (separatorBarId);
	ids.add (edit_cut);
	ids.add (edit_copy);
	ids.add (edit_paste);
	ids.add (edit_delete);
	ids.add (separatorBarId);
	ids.add (component_inspector);
    ids.add (flexibleSpacerId);

}

ToolbarItemComponent* ToolbarComponent::ToolbarComponentItemFactory::createItem (int itemId)
{
	ToolbarButton* button;

    switch (itemId)
    {
        case doc_open:
			button = createButtonFromZipFileSVG (itemId, "Open", "folder-open.svg");
			button->setTooltip("Open file");
			return button;
        case doc_save:
			button = createButtonFromZipFileSVG (itemId, "Save", "save.svg");
			button->setTooltip("Save file");
			return button;
		case project_close:
			button = createButtonFromZipFileSVG (itemId, "Close Project", "remove.svg");
			button->setCommandToTrigger (&JUCEDesignerApp::getCommandManager (), MainLayout::closeProject, true);
			return button;
        case edit_undo:
			button = createButtonFromZipFileSVG (itemId, "Undo", "chevron-left.svg");
			button->setCommandToTrigger (&JUCEDesignerApp::getCommandManager (), StandardApplicationCommandIDs::undo, true);
			return button;
        case edit_redo:
			button = createButtonFromZipFileSVG (itemId, "Redo", "chevron-right.svg");
			button->setCommandToTrigger (&JUCEDesignerApp::getCommandManager (), StandardApplicationCommandIDs::redo, true);
			return button;
		case edit_cut:
			button = createButtonFromZipFileSVG (itemId, "Cut", "scissors.svg");
			button->setCommandToTrigger (&JUCEDesignerApp::getCommandManager (), StandardApplicationCommandIDs::cut, true);
			return button;
		case edit_copy:
			button = createButtonFromZipFileSVG (itemId, "Copy", "document-copy.svg");
			button->setCommandToTrigger (&JUCEDesignerApp::getCommandManager (), StandardApplicationCommandIDs::copy, true);
			return button;
		case edit_paste:
			button = createButtonFromZipFileSVG (itemId, "Paste", "document-import.svg");
			button->setCommandToTrigger (&JUCEDesignerApp::getCommandManager (), StandardApplicationCommandIDs::paste, true);
			return button;
		case edit_delete:
			button = createButtonFromZipFileSVG (itemId, "Delete", "trash.svg");
			button->setCommandToTrigger (&JUCEDesignerApp::getCommandManager (), StandardApplicationCommandIDs::del, true);
			return button;
		case component_inspector:
			button = createButtonFromZipFileSVG (itemId, "Inspector", "screenshot.svg");
			//button->setTooltip("Component Inspector");
			button->setCommandToTrigger (&JUCEDesignerApp::getCommandManager (), MainLayout::componentInspector, true);
			button->getToggleStateValue ().referTo (JUCEDesignerApp::getApp().shouldBeComponentInspectorActive);
			return button;
        default:
			break;
    }

    return 0;
}

ToolbarButton* ToolbarComponent::ToolbarComponentItemFactory::createButtonFromZipFileSVG (const int itemId, const String& text, const String& filename)
{
	icons.add(Icons::get(filename, Icons::blue));
	Drawable* image = icons.getLast()->createCopy();
	icons.add(Icons::get(filename, Icons::yellow));
	Drawable* activeImage = icons.getLast()->createCopy();
	return new ToolbarButton (itemId, text, image, activeImage);
}



