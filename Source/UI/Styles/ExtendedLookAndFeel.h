/*
  ==============================================================================

    ExtendedLookAndFeel.h
    Created: 25 Oct 2013 8:54:58pm
    Author:  admin

  ==============================================================================
*/

#ifndef __EXTENDEDLOOKANDFEEL_H_E679DA2__
#define __EXTENDEDLOOKANDFEEL_H_E679DA2__


class PanelContainer;
class Panel;
class InnerPanel;
class MainLayout;

class ExtendedLookAndFeel   : public LookAndFeel_V3
{
public:

    ExtendedLookAndFeel();

	void drawPanelContainer (Graphics& g, Component& comp);
	void drawPanel (Graphics& g, Component& comp);
	//void drawInnerPanel (Graphics& g, Component& comp);
	void drawInnerPanel	(Graphics& g, Component& comp, bool drawHeader = false, String panelHeaderName = String::empty, int headerNameMarginRight = 0, int headerNameMarginLeft = 0, int panelHeaderHeight = 30, int indent = 5, float borderRadius = 5.0f);
	void drawMainLayout (Graphics& g, Component& comp);

	void drawFileBrowserRow (Graphics& g, int width, int height,
                                         const String& filename, Drawable* icon,
                                         const String& fileSizeDescription,
                                         const String& fileTimeDescription,
                                         const bool isDirectory, const bool isItemSelected,
										 const bool isOpen, const bool isHover,
                                         const int /*itemIndex*/, DirectoryContentsDisplayComponent& dcc);

private:

};


#endif  // __EXTENDEDLOOKANDFEEL_H_E679DA2__
