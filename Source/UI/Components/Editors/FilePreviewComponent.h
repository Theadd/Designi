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
//#include "../../../JuceLibraryCode/JuceHeader.h"

#ifndef __FILEPREVIEWCOMPONENT_H_1B659331__
#define __FILEPREVIEWCOMPONENT_H_1B659331__

#include "../Basics/InnerPanel.h"

//==============================================================================
/**
*/
class ItemPreviewComponent  : public InnerPanel
{
public:
    ItemPreviewComponent (const File& f)
        : file (f)
    {
		setName(f.getFileName());
        setOpaque (true);
        tryToLoadImage();
    }

	OpenDocumentManager::Document* getDocument() const override             { return nullptr; }
	ValueTree getNavigatorTree () override									{ return ValueTree::invalid; }

    void paint (Graphics& g)
    {
        //IntrojucerLookAndFeel::fillWithBackgroundTexture (*this, g);
		//InnerPanel::paint(g);
		//g.fillAll(Colour((juce::uint8) 51, (juce::uint8) 57, (juce::uint8) 61, (juce::uint8) 255));
		Colour tabsColour((juce::uint8) 22, (juce::uint8) 25, (juce::uint8) 27, (juce::uint8) 255);
		g.fillAll(tabsColour);

        if (drawable != nullptr)
        {
            Rectangle<int> area = RectanglePlacement (RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize)
                                    .appliedTo (drawable->getBounds(), Rectangle<int> (4, 22, getWidth() - 8, getHeight() - 26));

            Path p;
            p.addRectangle (area);
            DropShadow (Colours::black.withAlpha (0.5f), 6, Point<int> (0, 1)).drawForPath (g, p);

            g.fillCheckerBoard (area, 24, 24, Colour (0xffffffff), Colour (0xffeeeeee));

            g.setOpacity (1.0f);
            drawable->drawWithin (g, area.toFloat(), RectanglePlacement::stretchToFit, 1.0f);
        }

        g.setFont (Font (14.0f, Font::bold));
        g.setColour (findColour (Label::textColourId));
        g.drawMultiLineText (facts.joinIntoString ("\n"), 10, 15, getWidth() - 16);
    }

private:
    StringArray facts;
    File file;
    ScopedPointer<Drawable> drawable;

    void tryToLoadImage()
    {
        facts.clear();
        facts.add (file.getFullPathName());
        drawable = nullptr;

        {
            ScopedPointer <InputStream> input (file.createInputStream());

            if (input != nullptr)
            {
                const int64 totalSize = input->getTotalLength();

                String formatName;
                if (ImageFileFormat* format = ImageFileFormat::findImageFormatForStream (*input))
                    formatName = " " + format->getFormatName();

                input = nullptr;

                Image image (ImageCache::getFromFile (file));

                if (image.isValid())
                {
                    DrawableImage* d = new DrawableImage();
                    d->setImage (image);
                    drawable = d;

                    facts.add (String (image.getWidth()) + " x " + String (image.getHeight()) + formatName);
                }

                if (totalSize > 0)
                    facts.add (File::descriptionOfSizeInBytes (totalSize));
            }
        }

        if (drawable == nullptr)
        {
            ScopedPointer<XmlElement> svg (XmlDocument::parse (file));

            if (svg != nullptr)
                drawable = Drawable::createFromSVG (*svg);
        }

        facts.removeEmptyStrings (true);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ItemPreviewComponent)
};


#endif  // __FILEPREVIEWCOMPONENT_H_1B659331__
