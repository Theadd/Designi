/*
  ==============================================================================

    InnerPanel.h
    Created: 18 Oct 2013 6:16:30pm
    Author:  admin

  ==============================================================================
*/

#ifndef __INNERPANEL_H_9AA31784__
#define __INNERPANEL_H_9AA31784__

#include "../../Globals.h"
#include "../../Core/DocumentManager.h"

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

	String getHeaderName();

	void paint (Graphics& g);
	bool showAsTab;

	//OpenDocumentManager::Document* getDocument() const override             { return nullptr; }
	virtual OpenDocumentManager::Document* getDocument() const = 0;
	//ValueTree* getNavigatorTree () override { return nullptr; }
	virtual ValueTree getNavigatorTree () = 0;
	//void setNeedsToBeSaved (bool needsToBeSaved = true);
	//bool getNeedsToBeSaved ();
	//bool save (File initialDirectory = File::nonexistent) { return true; };
	void refresh();	//update its content

	void setLocalisedName (String name, String tooltip = String::empty);
	String& getLocalisedName ();
	void updateLocalisedStrings ();

	Globals::Position position;
	

private:
	//bool needsToBeSaved;	//if needs to be saved before closing
	bool isHeaderVisible;
	String headerName;
	int headerHeight;
	int indent;
	int headerNameMarginRight;
	int headerNameMarginLeft;
	String localisedName;
	String localisedTooltip;

};

class FileBasedInnerPanel : public InnerPanel
{
public:

	enum FileType
	{
		source,	//.cpp;.h;...
		design,	//.design
		unknown //images?
	};

private:

};



#endif  // __INNERPANEL_H_9AA31784__
