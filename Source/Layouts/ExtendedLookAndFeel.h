/*
  ==============================================================================

    ExtendedLookAndFeel.h
    Created: 25 Oct 2013 8:54:58pm
    Author:  admin

  ==============================================================================
*/

#ifndef __EXTENDEDLOOKANDFEEL_H_E679DA2__
#define __EXTENDEDLOOKANDFEEL_H_E679DA2__


#include "../Globals.h"

class PanelContainer;
class Panel;
class InnerPanel;
class MainLayout;

class ExtendedLookAndFeel   : public LookAndFeel
{
public:

    ExtendedLookAndFeel();

	void drawPanelContainer (Graphics& g, Component& comp);
	void drawPanel (Graphics& g, Component& comp);
	void drawInnerPanel (Graphics& g, Component& comp);
	void drawMainLayout (Graphics& g, Component& comp);

private:

};


#endif  // __EXTENDEDLOOKANDFEEL_H_E679DA2__
