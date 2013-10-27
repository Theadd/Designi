/*
  ==============================================================================

    MainLayout.h
    Created: 14 Oct 2013 9:37:32pm
    Author:  admin

  ==============================================================================
*/

#ifndef __MAINLAYOUT_H_DBAC5B39__
#define __MAINLAYOUT_H_DBAC5B39__


#include "../../Globals.h"

class ToolbarComponent;
class InnerPanel;
class FileBrowserPanel;
class NavigatorPanel;
class HelpPanel;
class CodeEditorPanel;
class Panel;
class PanelContainer;
class ExtendedLookAndFeel;
class MainWindow;

class FloatingComponentOverlay : public Component
{
public:
	FloatingComponentOverlay();

	void paint (Graphics& g);

	void mouseEnter (const MouseEvent &event);

private:

};

class MainLayout :	public Component,
					public ComponentListener,
					public MenuBarModel,
					public ApplicationCommandTarget,
					public DragAndDropContainer
{
public:

	enum ColourIds
    {
        backgroundColourId     = 0x2900001 /**< The background colour to fill MainLayer with. */
    };

    MainLayout(MainWindow& _mainWindow);
	~MainLayout();

	void resized();
	void paint (Graphics& g);

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

	bool isInnerPanelVisible(InnerPanel* innerPanel);
	void toggleInnerPanel(InnerPanel* innerPanel, Globals::Position position = Globals::left);
	PanelContainer* getPanelContainer(Globals::Position position);
	PanelContainer* getPanelContainerOf(InnerPanel* innerPanel, Globals::Position guessPosition = Globals::top);

	void loadDocument(File& file);

	ScopedPointer <FloatingComponentOverlay> floatingComponentOverlay;

private:
	MainWindow& mainWindow;
	//--
	Component panelContainerBox;
	OwnedArray <PanelContainer> panelContainers;
	OwnedArray <CodeEditorPanel> codeEditorPanels;
	
	// --
	//  --
	ScopedPointer <HelpPanel> helpPanel;
	ScopedPointer <FileBrowserPanel> fileBrowserPanel;
	ScopedPointer <NavigatorPanel> navigatorPanel;
	
	//--
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
			toolbarOrientation	= 0x220D,	//not in order, watch out!
			toolbarCustomize	= 0x220E,	//
		fileBrowser				= 0x2207,
		navigator				= 0x2208,
		properties				= 0x2209,
		toolbox					= 0x220A,
		modifiers				= 0x220B,
		help					= 0x220C,
		componentInspector		= 0x220F,
		//WINDOW
		//...
		//Help
		webpage					= 0x2300,
		about					= 0x2301
    };
};




#endif  // __MAINLAYOUT_H_DBAC5B39__
