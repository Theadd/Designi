/*
  ==============================================================================

    ExtendedLookAndFeel.cpp
    Created: 25 Oct 2013 8:54:58pm
    Author:  admin

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "ExtendedLookAndFeel.h"
#include "MainLayout/InnerPanelContainers.h"
#include "MainLayout/InnerPanel.h"
#include "MainLayout/MainLayout.h"

ExtendedLookAndFeel::ExtendedLookAndFeel() : LookAndFeel_V3()
{
	setColour (PanelContainer::backgroundColourId, Colour((juce::uint8) 51, (juce::uint8) 57, (juce::uint8) 61, (juce::uint8) 255));
	setColour (Panel::backgroundColourId, Colours::transparentBlack);
	setColour (MainLayout::backgroundColourId, Colour((juce::uint8) 51, (juce::uint8) 57, (juce::uint8) 61, (juce::uint8) 255));
	setColour (InnerPanel::headerNameBackgroundColourId, Colours::white.withAlpha(0.2f));
	setColour (InnerPanel::headerNameBorderColourId, Colours::black);
	setColour (InnerPanel::borderColourId, Colours::black);
	setColour (InnerPanel::headerNameTextColourId, Colours::white);
	setColour (InnerPanel::nonHeaderBackgroundColourId, Colours::black.withAlpha(0.4f));
	setColour (InnerPanel::backgroundColourId, Colours::transparentBlack);
	setColour (DirectoryContentsDisplayComponent::highlightColourId, findColour (PanelContainer::backgroundColourId).interpolatedWith(Colours::black, 0.3f));
	
}

void ExtendedLookAndFeel::drawPanelContainer (Graphics& g, Component& /*comp*/)
{
	g.fillAll (findColour (PanelContainer::backgroundColourId));
}

void ExtendedLookAndFeel::drawPanel (Graphics& g, Component& /*comp*/)
{
	g.fillAll (findColour (Panel::backgroundColourId));
}

void ExtendedLookAndFeel::drawInnerPanel (Graphics& g, Component& comp, bool drawHeader, String panelHeaderName, int headerNameMarginRight, int headerNameMarginLeft, int panelHeaderHeight, int indent, float borderRadius)
{
	if (drawHeader)
	{
		Rectangle<int> bounds = comp.getLocalBounds();
		int panelHeaderNameWidth = bounds.getWidth() - (2 * indent) - headerNameMarginLeft - headerNameMarginRight;
		//Fill header background
		g.setColour(comp.findColour(InnerPanel::backgroundColourId));
		g.drawRect(0, 0, bounds.getWidth(), panelHeaderHeight);
		//Draw header name background colour
		Path name;
		name.addRoundedRectangle ((float) indent + (float) headerNameMarginLeft, (float) indent, (float) panelHeaderNameWidth, (float) panelHeaderHeight - (2 * indent), borderRadius, borderRadius, true, true, true, true);
		g.setColour(comp.findColour(InnerPanel::headerNameBackgroundColourId));
		g.fillPath(name);
		//draw header name border (1px)
		g.setColour(comp.findColour(InnerPanel::headerNameBorderColourId));
		g.strokePath (name, PathStrokeType (1.0f));
		//draw header name text
		int padding = 5;
		g.setColour(comp.findColour(InnerPanel::headerNameTextColourId));
		g.drawFittedText (panelHeaderName, indent + headerNameMarginLeft + padding, indent, panelHeaderNameWidth - (2 * padding), panelHeaderHeight - (2 * indent), Justification::centredLeft, 1);
		
		//Paint the rest of the component background
		g.setColour(comp.findColour(InnerPanel::nonHeaderBackgroundColourId));
		Rectangle<int> rest(0, panelHeaderHeight, bounds.getWidth(), bounds.getHeight() - panelHeaderHeight);
		g.fillRect(rest);
		
		//draw border line at the bottom of the header
		g.setColour(comp.findColour(InnerPanel::borderColourId));
		g.drawHorizontalLine(panelHeaderHeight, 0.0f, (float) comp.getWidth());
		

		//DBG("[ELAF] panelHeaderName: "+panelHeaderName);
	}
	else
	{
		g.fillAll(comp.findColour(InnerPanel::backgroundColourId));
	}
}

void ExtendedLookAndFeel::drawMainLayout (Graphics& g, Component& /*comp*/)
{
	g.fillAll (findColour (MainLayout::backgroundColourId));
}

void ExtendedLookAndFeel::drawFileBrowserRow (Graphics& g, int width, int height,
                                         const String& filename, Drawable* icon,
                                         const String& fileSizeDescription,
                                         const String& fileTimeDescription,
                                         const bool isDirectory, const bool isItemSelected,
										 const bool /*isOpen*/, const bool /*isHover*/,
                                         const int /*itemIndex*/, DirectoryContentsDisplayComponent& dcc)
{
    Component* const fileListComp = dynamic_cast<Component*> (&dcc);

    if (isItemSelected)
        g.fillAll (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightColourId)
                                           : findColour (DirectoryContentsDisplayComponent::highlightColourId));

    const int x = 32;
    g.setColour (Colours::black);

    if (icon != nullptr)
    {
        icon->drawWithin (g, Rectangle<float> (2.0f, 2.0f, x - 4.0f, height - 4.0f),
                        RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
    }

    g.setColour (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::textColourId)
                                         : findColour (DirectoryContentsDisplayComponent::textColourId));
    g.setFont (height * 0.7f);

    if (width > 450 && ! isDirectory)
    {
        const int sizeX = roundToInt (width * 0.7f);
        const int dateX = roundToInt (width * 0.8f);

        g.drawFittedText (filename,
                          x, 0, sizeX - x, height,
                          Justification::centredLeft, 1);

        g.setFont (height * 0.5f);
        g.setColour (Colours::darkgrey);

        if (! isDirectory)
        {
            g.drawFittedText (fileSizeDescription,
                              sizeX, 0, dateX - sizeX - 8, height,
                              Justification::centredRight, 1);

            g.drawFittedText (fileTimeDescription,
                              dateX, 0, width - 8 - dateX, height,
                              Justification::centredRight, 1);
        }
    }
    else
    {
        g.drawFittedText (filename,
                          x, 0, width - x, height,
                          Justification::centredLeft, 1);

    }
}