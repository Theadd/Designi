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

ExtendedLookAndFeel::ExtendedLookAndFeel() : LookAndFeel()
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
		

		DBG("[ELAF] panelHeaderName: "+panelHeaderName);
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