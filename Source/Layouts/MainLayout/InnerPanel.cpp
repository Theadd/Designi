/*
  ==============================================================================

    InnerPanel.cpp
    Created: 18 Oct 2013 6:16:30pm
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../Globals.h"

#include "InnerPanel.h"
#include "../ExtendedLookAndFeel.h"

InnerPanel::InnerPanel(bool showAsTab_, Globals::Position _position) : Component(), showAsTab(showAsTab_), position(_position)
{
	isHeaderVisible = false;
	needsToBeSaved = false;
}

void InnerPanel::setHeader(bool showHeader_, String headerName_, int headerHeight_, int indent_, int headerNameMarginRight_, int headerNameMarginLeft_)
{
	isHeaderVisible = showHeader_;
	headerName = headerName_;
	headerHeight = headerHeight_;
	indent = indent_;
	headerNameMarginRight = headerNameMarginRight_;
	headerNameMarginLeft = headerNameMarginLeft_;

	repaint();
}

String InnerPanel::getHeaderName()
{
	return headerName;
}

void InnerPanel::paint (Graphics& g)
{
	//drawInnerPanel	(Graphics& g, InnerPanel& comp, const String& panelHeaderName, int headerNameMarginRight = 0, headerNameMarginLeft = 0, int panelHeaderHeight = 30, int indent = 5);
	if (isHeaderVisible)
		((ExtendedLookAndFeel*) &getLookAndFeel())->drawInnerPanel (g, *this, true, headerName, headerNameMarginRight, headerNameMarginLeft, headerHeight, indent);
	else
		((ExtendedLookAndFeel*) &getLookAndFeel())->drawInnerPanel (g, *this);
}

void InnerPanel::setNeedsToBeSaved(bool needs)
{
	needsToBeSaved = needs;
}

bool InnerPanel::getNeedsToBeSaved()
{
	return needsToBeSaved;
}

