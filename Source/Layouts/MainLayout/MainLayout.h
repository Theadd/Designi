/*
  ==============================================================================

    MainLayout.h
    Created: 14 Oct 2013 9:37:32pm
    Author:  admin

  ==============================================================================
*/

#ifndef __MAINLAYOUT_H_DBAC5B39__
#define __MAINLAYOUT_H_DBAC5B39__

#include "Toolbars.h"
#include "LeftPanelContainer.cpp"
#include "RightPanelContainer.h"


class MainWindow;

class MainLayout :	public Component,
					public ComponentListener,
					public MenuBarModel,
					public ApplicationCommandTarget
{
public:

    MainLayout(MainWindow& _mainWindow);
	~MainLayout();

	void resized();

    void mouseUp (const MouseEvent& event);

    void mouseDrag (const MouseEvent& event);

    void mouseDoubleClick (const MouseEvent& event);

	
	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex (int menuIndex, const String& /*menuName*/);
	void menuItemSelected (int menuItemID, int /*topLevelMenuIndex*/);

	ApplicationCommandTarget* getNextCommandTarget();

	void getAllCommands (Array <CommandID>& commands);

	void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result);

	bool perform (const InvocationInfo& info);


private:
	MainWindow& mainWindow;
    LeftPanelContainer leftpanelcontainer;
	ScopedPointer <PanelContainer> rightPanelContainer;
	ScopedPointer <ToolbarComponent> toolbarComponent;

	enum CommandIDs
    {
		//FILE
        newProject              = 0x2000,
		newDesign				= 0x2001,
		openProject				= 0x2002,
		openRecentProject		= 0x2003,
		closeProject			= 0x2004,
		save					= 0x2005,
		saveAs					= 0x2006,
		saveAll					= 0x2007,
		print					= 0x2008,
		//EDIT
		undo					= 0x2100,
		redo					= 0x2101,
		cut						= 0x2102,
		copy					= 0x2103,
		paste					= 0x2104,
		delete_					= 0x2105,
		find					= 0x2106,
		replace					= 0x2107,
		preferences				= 0x2108,
		//VIEW
		leftPanel				= 0x2200,
		rightPanel				= 0x2201,
			//toolbars
			fileToolbar			= 0x2203,
			clipboardToolbar	= 0x2204,
			historyToolbar		= 0x2205,
			drawableToolbar		= 0x2206,
		help					= 0x2207,
		//WINDOW
		//...
		//Help
		webpage					= 0x2300,
		about					= 0x2301
    };
};




#endif  // __MAINLAYOUT_H_DBAC5B39__
