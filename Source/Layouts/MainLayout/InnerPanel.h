/*
  ==============================================================================

    InnerPanel.h
    Created: 18 Oct 2013 6:16:30pm
    Author:  admin

  ==============================================================================
*/

#ifndef __INNERPANEL_H_9AA31784__
#define __INNERPANEL_H_9AA31784__

class ExtendedLookAndFeel;

class InnerPanel : public Component, public SettableTooltipClient
{
public:

	enum ColourIds
    {
		backgroundColourId				= 0x2902000, /**< Used to fill panel's background if there is no header, if there is a header it will be used to fill the header background. */
        headerNameBackgroundColourId    = 0x2902001, /**< The background colour to fill the panel header name with. */
		headerNameBorderColourId		= 0x2902002, /**< The border colour of the header name. */
		borderColourId					= 0x2902003, /**< The border colour that splits the panel header from the rest. */
		headerNameTextColourId			= 0x2902004, /**< The header name text colour. */
		nonHeaderBackgroundColourId		= 0x2902005  /**< The background colour to fill the rest of the panel with. Only used if there is a header, it will use backgroundColourId otherwise. */
    };

	InnerPanel(bool showAsTab_ = true, Globals::Position _position = Globals::left);

	void setHeader(bool showHeader = true, String headerName = "Panel Header", int headerHeight = 30, int indent = 5, int headerNameMarginRight = 0, int headerNameMarginLeft = 0);

	void paint (Graphics& g);
	bool showAsTab;
	Globals::Position position;


private:
	bool isHeaderVisible;
	String headerName;
	int headerHeight;
	int indent;
	int headerNameMarginRight;
	int headerNameMarginLeft;
};



#endif  // __INNERPANEL_H_9AA31784__
