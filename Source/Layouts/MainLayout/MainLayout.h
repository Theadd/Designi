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
//#include "LeftPanelContainer.cpp"
#include "InnerPanelContainers.h"
#include "InnerPanels.h"
#include "../../Globals.h"

class MainWindow;

class FloatingComponentOverlay : public Component
{
public:
	FloatingComponentOverlay()
	{
		setInterceptsMouseClicks(false, false);
		setAlwaysOnTop(true);
	}

	void paint (Graphics& g)
	{
		/*int color = Random::getSystemRandom().nextInt(6);

		switch (color)
		{
		case 0:
			g.fillAll (Colours::cadetblue);
			DBG("0aquamarine");
			break;
		case 1:
			g.fillAll (Colours::darkblue);
			DBG("1aqua");
			break;
		case 2:
			g.fillAll (Colours::darkcyan);
			DBG("2azure");
			break;
		case 3:
			g.fillAll (Colours::darkkhaki);
			DBG("3beige");
			break;
		case 4:
			g.fillAll (Colours::darkorange);
			DBG("4bisque");
			break;
		case 5:
			g.fillAll (Colours::darkslateblue);
			DBG("5blanchedalmond");
			break;
		default:
			break;
		}*/
		g.fillAll (Colours::darkblue.withAlpha(0.4f));
	}

	void mouseEnter (const MouseEvent &event)
	{
		Component* mainLayout = getParentComponent();
		if (mainLayout != 0)
		{
			Rectangle<int> sBounds = event.eventComponent->getScreenBounds();
			Rectangle<int> mBounds = mainLayout->getScreenBounds();
			setBounds(sBounds.getX() - mBounds.getX(), sBounds.getY() - mBounds.getY(), sBounds.getWidth(), sBounds.getHeight());
			
			if (typeid(event.eventComponent) == typeid(InnerPanel))
				DBG("\t\t\tTYPEID == TextButton");
		}
	}

private:

};

class MainLayout :	public Component,
					public ComponentListener,
					public MenuBarModel,
					public ApplicationCommandTarget,
					public DragAndDropContainer
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

	bool isInnerPanelVisible(InnerPanel* innerPanel);
	void toggleInnerPanel(InnerPanel* innerPanel, Globals::Position position = Globals::left);
	PanelContainer* getPanelContainer(Globals::Position position);
	PanelContainer* getPanelContainerOf(InnerPanel* innerPanel, Globals::Position guessPosition = Globals::top);

private:
	MainWindow& mainWindow;
	//--
	//ScopedPointer <PanelContainer> rightPanelContainer;
	//ScopedPointer <PanelContainer> leftPanelContainer;
	OwnedArray <PanelContainer> panelContainers;
	ScopedPointer <FloatingComponentOverlay> floatingComponentOverlay;
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
		fileBrowser				= 0x2207,
		navigator				= 0x2208,
		properties				= 0x2209,
		toolbox					= 0x220A,
		modifiers				= 0x220B,
		help					= 0x220C,
		//WINDOW
		//...
		//Help
		webpage					= 0x2300,
		about					= 0x2301
    };
};




#endif  // __MAINLAYOUT_H_DBAC5B39__
