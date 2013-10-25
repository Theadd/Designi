/*
  ==============================================================================

    Globals.h
    Created: 13 Oct 2013 2:59:53am
    Author:  admin

  ==============================================================================
*/
//#include "../JuceLibraryCode/JuceHeader.h"

#ifndef __GLOBALS_H_D2823AC0__
#define __GLOBALS_H_D2823AC0__

#define RESIZABLEEDGESIZE 5
#define TOOLBARSIZE 32
#define MINIMUMPANELSIZE 90
#define MENUBARHEIGHT 24

namespace Globals
{
    enum Position
	{
		top,
		right,
		bottom,
		left,
		center
	};

	enum Orientation
	{
		none,
		vertical,
		horizontal
	};
}

enum ColourIds
{
    mainBackgroundColourId          = 0x2340000,
    treeviewHighlightColourId       = 0x2340002,
};


/*
namespace LayoutColourIds
{
	const Identifier headerBackgroundColour		("headerBackgroundColour");
	const Identifier headerTextColour	("headerTextColour");
}

namespace Layout
{
	inline Colour getColourFor (Identifier c)
	{
		if (c == LayoutColourIds::headerBackgroundColour)
			return Colour(Colour((juce::uint8) 83, (juce::uint8) 94, (juce::uint8) 104, (juce::uint8) 255));

		else if (c == LayoutColourIds::headerBackgroundColour)
			return Colour(Colour((juce::uint8) 83, (juce::uint8) 94, (juce::uint8) 104, (juce::uint8) 255));

		else
			return Colours::transparentBlack;
	}
}
*/

#endif  // __GLOBALS_H_D2823AC0__
