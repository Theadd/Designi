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
}

void ExtendedLookAndFeel::drawPanelContainer (Graphics& g, Component& /*comp*/)
{
	g.fillAll (findColour (PanelContainer::backgroundColourId));
}

void ExtendedLookAndFeel::drawPanel (Graphics& g, Component& /*comp*/)
{
	g.fillAll (findColour (Panel::backgroundColourId));
}

void ExtendedLookAndFeel::drawInnerPanel (Graphics& /*g*/, Component& /*comp*/)
{
	//g.fillAll(Colours::black.withAlpha (0.5f));
}

void ExtendedLookAndFeel::drawMainLayout (Graphics& g, Component& /*comp*/)
{
	g.fillAll (findColour (MainLayout::backgroundColourId));
}