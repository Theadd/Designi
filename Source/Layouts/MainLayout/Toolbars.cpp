/*
  ==============================================================================

    Toolbars.cpp
    Created: 15 Oct 2013 1:23:41am
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "Toolbars.h"

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
    ids.add (edit_undo);
    ids.add (edit_redo);
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
    ids.add (separatorBarId);
    ids.add (edit_undo);
    ids.add (edit_redo);
    ids.add (flexibleSpacerId);

}

ToolbarItemComponent* ToolbarComponent::ToolbarComponentItemFactory::createItem (int itemId)
{
	ToolbarButton* button;

    switch (itemId)
    {
        case doc_open:
			button = createButtonFromZipFileSVG (itemId, "Open", "Download.svg");
			button->setTooltip("Open file");
			return button;
        case doc_save:
			button = createButtonFromZipFileSVG (itemId, "Save", "Upload.svg");
			button->setTooltip("Save file");
			return button;
        case edit_undo:
			button = createButtonFromZipFileSVG (itemId, "Undo", "Undo.svg");
			button->setTooltip("Undo");
			return button;
        case edit_redo:
			button = createButtonFromZipFileSVG (itemId, "Redo", "Redo.svg");
			button->setTooltip("Redo");
			return button;
        default:
			break;
    }

    return 0;
}

ToolbarButton* ToolbarComponent::ToolbarComponentItemFactory::createButtonFromZipFileSVG (const int itemId, const String& text, const String& filename)
{
    if (iconsFromZipFile.size() == 0)
    {
        // If we've not already done so, load all the images from the zip file..
        MemoryInputStream iconsFileStream (BinaryData::icons2_zip, BinaryData::icons2_zipSize, false);
        ZipFile icons (&iconsFileStream, false);

        for (int i = 0; i < icons.getNumEntries(); ++i)
        {
            ScopedPointer<InputStream> svgFileStream (icons.createStreamForEntry (i));

            if (svgFileStream != 0)
            {
                iconNames.add (icons.getEntry(i)->filename);
                iconsFromZipFile.add (Drawable::createFromImageDataStream (*svgFileStream));
            }
        }
    }

    Drawable* image = iconsFromZipFile [iconNames.indexOf (filename)]->createCopy();
    return new ToolbarButton (itemId, text, image, 0);
}



