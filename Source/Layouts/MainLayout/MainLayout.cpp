/*
  ==============================================================================

    MainLayout.cpp
    Created: 14 Oct 2013 9:37:33pm
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"

#include "MainLayout.h"

#include "../MainWindow.h"




MainLayout::MainLayout(MainWindow& _mainWindow) : Component(), mainWindow(_mainWindow)
{
	DBG("dbg: MainLayout()");
    //setBounds(0, 0, 490, 414);
    setName("MainLayout");

	toolbarComponent = nullptr;
	addAndMakeVisible(toolbarComponent = new ToolbarComponent(32));
	
	//ADD PANEL CONTAINERS
	panelContainers.add(new PanelContainer(Globals::top, this));
	panelContainers.add(new PanelContainer(Globals::right, this));
	panelContainers.add(new PanelContainer(Globals::bottom, this));
	panelContainers.add(new PanelContainer(Globals::left, this));

	PanelContainer *leftPanelContainer = getPanelContainer(Globals::left);
	PanelContainer *rightPanelContainer = getPanelContainer(Globals::right);
	PanelContainer *topPanelContainer = getPanelContainer(Globals::top);
	PanelContainer *bottomPanelContainer = getPanelContainer(Globals::bottom);

	addChildComponent(rightPanelContainer);
	rightPanelContainer->setBounds(400,32,250,600);
	addChildComponent(leftPanelContainer);
	leftPanelContainer->setBounds(0,32,250,600);
	addChildComponent(topPanelContainer);
	topPanelContainer->setBounds(0,32,250,250);
	addChildComponent(bottomPanelContainer);
	bottomPanelContainer->setBounds(0,32,250,250);

	//DBG("ADDING PANEL A TO RIGHT");

	//rightPanelContainer->addAndMakeVisible(panelA = new Panel("Panel A", this));
	//DBG("ADDING PANEL B TO RIGHT");
	//rightPanelContainer->addAndMakeVisible(panelB = new Panel("Panel B", this));
	//DBG("ADDING PANEL C TO RIGHT");
	//rightPanelContainer->addAndMakeVisible(panelC = new Panel("Panel C", this));
	//DBG("ADDING PANEL D TO LEFT");
	//leftPanelContainer->addAndMakeVisible(panelD = new Panel("Panel D", this));
	//DBG("ADDING PANEL E TO LEFT");
	//leftPanelContainer->addAndMakeVisible(panelE = new Panel("Panel E", this));

	rightPanelContainer->addInnerPanel(navigatorPanel = new NavigatorPanel());
	//FileBrowserTab
	fileBrowserPanel = nullptr;
	leftPanelContainer->addInnerPanel(fileBrowserPanel = new FileBrowserPanel(), true);
	//helpPanel
	DBG("ADDING HELP PANEL!");
	helpPanel = nullptr;
	leftPanelContainer->addInnerPanel(helpPanel = new HelpPanel(), true);

	//
	addAndMakeVisible(floatingComponentOverlay = new FloatingComponentOverlay());
	addMouseListener(floatingComponentOverlay, true);

	resized();
}

MainLayout::~MainLayout()
{
	toolbarComponent = nullptr;
	helpPanel = nullptr;
	fileBrowserPanel = nullptr;
	navigatorPanel = nullptr;
	floatingComponentOverlay = nullptr;
}

void MainLayout::resized()
{
	Rectangle<int> r = this->getLocalBounds();
	PanelContainer *leftPanelContainer = getPanelContainer(Globals::left);
	PanelContainer *rightPanelContainer = getPanelContainer(Globals::right);
	PanelContainer *topPanelContainer = getPanelContainer(Globals::top);
	PanelContainer *bottomPanelContainer = getPanelContainer(Globals::bottom);

	if (toolbarComponent != nullptr)
		toolbarComponent->setBounds(this->getLocalBounds());

	if (bottomPanelContainer != nullptr)
	{
		bottomPanelContainer->setBounds(0, r.getHeight() - bottomPanelContainer->getHeight(), r.getWidth(), bottomPanelContainer->getHeight());
	}

	if  (leftPanelContainer != nullptr)
	{
		int modHeight = (bottomPanelContainer != nullptr && bottomPanelContainer->isVisible()) ? -1 * bottomPanelContainer->getHeight() : 0;
		leftPanelContainer->setBounds(0, TOOLBARSIZE, leftPanelContainer->getWidth(), r.getHeight() - TOOLBARSIZE + modHeight);
	}

	if  (rightPanelContainer != nullptr)
	{
		int modHeight = (bottomPanelContainer != nullptr && bottomPanelContainer->isVisible()) ? -1 * bottomPanelContainer->getHeight() : 0;
		rightPanelContainer->setBounds(r.getWidth() - rightPanelContainer->getWidth(), TOOLBARSIZE, rightPanelContainer->getWidth(), r.getHeight() - TOOLBARSIZE + modHeight);
	}

	if (topPanelContainer != nullptr)
	{
		int startX = 0;
		int modWidth = 0;
		if (leftPanelContainer != nullptr && leftPanelContainer->isVisible())
		{
			startX = leftPanelContainer->getX() + leftPanelContainer->getWidth();
			modWidth -= startX;
		}
		if (rightPanelContainer != nullptr && rightPanelContainer->isVisible())
			modWidth -= rightPanelContainer->getWidth();

		topPanelContainer->setBounds(0 + startX, TOOLBARSIZE, r.getWidth() + modWidth, topPanelContainer->getHeight());
	}

}

void MainLayout::mouseUp (const MouseEvent& event)
{
    if (event.eventComponent == this)
        Component::mouseUp(event);
}

void MainLayout::mouseDrag (const MouseEvent& event)
{
    if (event.eventComponent == this)
        Component::mouseDrag(event);
}

void MainLayout::mouseDoubleClick (const MouseEvent& event)
{
    if (event.eventComponent == this)
        Component::mouseDoubleClick(event);
}


StringArray MainLayout::getMenuBarNames()
{
	const char* const names[] = { "File", "Edit", "View", "Window", "Help", nullptr };

	return StringArray (names);
}

PopupMenu MainLayout::getMenuForIndex (int menuIndex, const String& /*menuName*/)
{
	ApplicationCommandManager* commandManager = &(mainWindow.commandManager);

	PopupMenu menu;

	if (menuIndex == 0)
	{
	    menu.addCommandItem (commandManager, newProject);
		menu.addCommandItem (commandManager, newDesign);
		menu.addSeparator();
		menu.addCommandItem (commandManager, openProject);
		menu.addCommandItem (commandManager, openRecentProject);
		menu.addCommandItem (commandManager, closeProject);
		menu.addSeparator();
		menu.addCommandItem (commandManager, save);
		menu.addCommandItem (commandManager, saveAs);
		menu.addCommandItem (commandManager, saveAll);
		menu.addSeparator();
		menu.addCommandItem (commandManager, print);
		menu.addSeparator();
		menu.addCommandItem (commandManager, StandardApplicationCommandIDs::quit);
	}
	if (menuIndex == 1)
	{
		//EDIT
		menu.addCommandItem (commandManager, undo);
		menu.addCommandItem (commandManager, redo);
		menu.addSeparator();
		menu.addCommandItem (commandManager, cut);
		menu.addCommandItem (commandManager, copy);
		menu.addCommandItem (commandManager, paste);
		menu.addCommandItem (commandManager, delete_);
		menu.addSeparator();
		menu.addCommandItem (commandManager, find);
		menu.addCommandItem (commandManager, replace);
		menu.addSeparator();
		menu.addCommandItem (commandManager, preferences);
	}
	if (menuIndex == 2)
	{
		//VIEW
		//menu.addCommandItem (commandManager, leftPanel);
		//menu.addCommandItem (commandManager, rightPanel);
		//menu.addSeparator();

			PopupMenu toolbarsSubMenu;
            
			toolbarsSubMenu.addCommandItem (commandManager, fileToolbar);
			toolbarsSubMenu.addCommandItem (commandManager, clipboardToolbar);
			toolbarsSubMenu.addCommandItem (commandManager, historyToolbar);
			toolbarsSubMenu.addCommandItem (commandManager, drawableToolbar);

			menu.addSubMenu ("Toolbars", toolbarsSubMenu);

		menu.addSeparator();
		//fileBrowser, navigator, properties, toolbox, modifiers,
		menu.addCommandItem (commandManager, fileBrowser);
		menu.addCommandItem (commandManager, navigator);
		menu.addCommandItem (commandManager, properties);
		menu.addCommandItem (commandManager, toolbox);
		menu.addCommandItem (commandManager, modifiers);
		menu.addCommandItem (commandManager, help);
	}
	if (menuIndex == 3)
	{
		//WINDOW
		//...
		//Help
	}
	if (menuIndex == 4)
	{
		menu.addCommandItem (commandManager, webpage);
		menu.addSeparator();
		menu.addCommandItem (commandManager, about);
	}

	return menu;
}

void MainLayout::menuItemSelected (int menuItemID, int /*topLevelMenuIndex*/)
{
	// most of our menu items are invoked automatically as commands, but we can handle the
	// other special cases here..

	DBG(("Selected menu item: " + String(menuItemID)));
}

ApplicationCommandTarget* MainLayout::getNextCommandTarget()
{
	// this will return the next parent component that is an ApplicationCommandTarget (in this
	// case, there probably isn't one, but it's best to use this method in your own apps).
	return findFirstTargetParentComponent();
}

void MainLayout::getAllCommands (Array <CommandID>& commands)
{
	// this returns the set of all commands that this target can perform..
	const CommandID ids[] = {newProject, newDesign, openProject, openRecentProject, closeProject, save, saveAs, saveAll, print, undo, redo, cut, copy, paste, delete_, find, replace, preferences, leftPanel, rightPanel, fileToolbar, clipboardToolbar, historyToolbar, drawableToolbar, fileBrowser, navigator, properties, toolbox, modifiers, help, webpage, about};

	commands.addArray (ids, numElementsInArray (ids));
}

void MainLayout::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
	const String generalCategory ("General");

	switch (commandID)
	{
	case newProject:
		result.setInfo ("New Project...", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('n', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
		break;
	case newDesign:
		result.setInfo ("New Design", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('n', ModifierKeys::commandModifier);
		break;
	case openProject:
		result.setInfo ("Open Project...", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('o', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
		break;
	case openRecentProject:
		result.setInfo ("Open Recent Project", "", generalCategory, 0);
		result.setTicked (false);
		break;
	case closeProject:
		result.setInfo ("Close Project", "", generalCategory, 0);
		result.setTicked (false);
		break;
	case save:
		result.setInfo ("Save", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('s', ModifierKeys::commandModifier);
		break;
	case saveAs:
		result.setInfo ("Save As", "", generalCategory, 0);
		result.setTicked (false);
		break;
	case saveAll:
		result.setInfo ("Save All", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('s', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
		break;
	case print:
		result.setInfo ("Print...", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('p', ModifierKeys::commandModifier | ModifierKeys::shiftModifier | ModifierKeys::altModifier);
		break;
	case undo:
		result.setInfo ("Undo", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('z', ModifierKeys::commandModifier);
		break;
	case redo:
		result.setInfo ("Redo", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('y', ModifierKeys::commandModifier);
		break;
	case cut:
		result.setInfo ("Cut", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('x', ModifierKeys::commandModifier);
		break;
	case copy:
		result.setInfo ("Copy", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('c', ModifierKeys::commandModifier);
		break;
	case paste:
		result.setInfo ("Paste", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('v', ModifierKeys::commandModifier);
		break;
	case delete_:
		result.setInfo ("Delete", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress (KeyPress::deleteKey, 0);
		break;
	case find:
		result.setInfo ("Find...", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('f', ModifierKeys::commandModifier);
		break;
	case replace:
		result.setInfo ("Replace...", "", generalCategory, 0);
		result.setTicked (false);
		result.addDefaultKeypress ('h', ModifierKeys::commandModifier);
		break;
	case preferences:
		result.setInfo ("Preferences...", "", generalCategory, 0);
		result.setTicked (false);
		break;
	case leftPanel:
		result.setInfo ("Left Panel", "", generalCategory, 0);
		result.addDefaultKeypress ('l', ModifierKeys::commandModifier | ModifierKeys::altModifier);
		break;
	case rightPanel:
		result.setInfo ("Right Panel", "", generalCategory, 0);
		result.addDefaultKeypress ('r', ModifierKeys::commandModifier | ModifierKeys::altModifier);
		break;
	case fileToolbar:
		result.setInfo ("File", "", generalCategory, 0);
		result.setTicked (true);
		break;
	case clipboardToolbar:
		result.setInfo ("Clipboard", "", generalCategory, 0);
		result.setTicked (true);
		break;
	case historyToolbar:
		result.setInfo ("History", "", generalCategory, 0);
		result.setTicked (true);
		break;
	case drawableToolbar:
		result.setInfo ("Drawable Components", "", generalCategory, 0);
		result.setTicked (true);
		break;
	case fileBrowser:
		result.setInfo ("File Browser", "", generalCategory, 0);
		result.setTicked ((fileBrowserPanel != nullptr && isInnerPanelVisible(fileBrowserPanel) ? true : false));
		result.setActive ((fileBrowserPanel != nullptr) ? true : false);
		result.addDefaultKeypress ('b', ModifierKeys::commandModifier | ModifierKeys::altModifier);
		break;
	case navigator:
		result.setInfo ("Navigator", "", generalCategory, 0);
		result.setTicked ((navigatorPanel != nullptr && isInnerPanelVisible(navigatorPanel) ? true : false));
		result.setActive ((navigatorPanel != nullptr) ? true : false);
		result.addDefaultKeypress ('n', ModifierKeys::commandModifier | ModifierKeys::altModifier);
		break;
	case properties:
		result.setInfo ("Properties", "", generalCategory, 0);
		//result.setTicked ((navigatorPanel != nullptr && isInnerPanelVisible(navigatorPanel) ? true : false));
		result.setActive (false);//((navigatorPanel != nullptr) ? true : false);
		result.addDefaultKeypress ('p', ModifierKeys::commandModifier | ModifierKeys::altModifier);
		break;
	case toolbox:
		result.setInfo ("Toolbox", "", generalCategory, 0);
		//result.setTicked ((navigatorPanel != nullptr && isInnerPanelVisible(navigatorPanel) ? true : false));
		result.setActive (false);//((navigatorPanel != nullptr) ? true : false);
		result.addDefaultKeypress ('t', ModifierKeys::commandModifier | ModifierKeys::altModifier);
		break;
	case modifiers:
		result.setInfo ("Modifiers", "", generalCategory, 0);
		//result.setTicked ((navigatorPanel != nullptr && isInnerPanelVisible(navigatorPanel) ? true : false));
		result.setActive (false);//((navigatorPanel != nullptr) ? true : false);
		result.addDefaultKeypress ('m', ModifierKeys::commandModifier | ModifierKeys::altModifier);
		break;
	case help:
		result.setInfo ("Help", "", generalCategory, 0);
		result.setTicked ((helpPanel != nullptr && isInnerPanelVisible(helpPanel) ? true : false));
		result.setActive ((helpPanel != nullptr) ? true : false);
		result.addDefaultKeypress ('h', ModifierKeys::commandModifier | ModifierKeys::altModifier);
		break;
	case webpage:
		result.setInfo ("Webpage", "", generalCategory, 0);
		result.setTicked (false);
		break;
	case about:
		result.setInfo ("About JUCE Designer", "", generalCategory, 0);
		result.setTicked (false);
		break;

	default:
		break;
	};
}

bool MainLayout::perform (const InvocationInfo& info)
{
	switch (info.commandID)
	{
	case newProject:
		break;
	case newDesign:
		break;
	case openProject:
		break;
	case openRecentProject:
		break;
	case closeProject:
		break;
	case save:
		break;
	case saveAs:
		break;
	case saveAll:
		break;
	case print:
		break;
	case undo:
		break;
	case redo:
		break;
	case cut:
		break;
	case copy:
		break;
	case paste:
		break;
	case delete_:
		break;
	case find:
		break;
	case replace:
		break;
	case preferences:
		break;
	case leftPanel:
		if (getPanelContainer(Globals::left) != nullptr)
			getPanelContainer(Globals::left)->setVisible(!getPanelContainer(Globals::left)->isVisible());
		break;
	case rightPanel:
		if (getPanelContainer(Globals::right) != nullptr)
			getPanelContainer(Globals::right)->setVisible(!getPanelContainer(Globals::right)->isVisible());
		break;
	case fileToolbar:
		break;
	case clipboardToolbar:
		break;
	case historyToolbar:
		break;
	case drawableToolbar:
		break;
	case fileBrowser:
		toggleInnerPanel(fileBrowserPanel, Globals::left);
		break;
	case navigator:
		toggleInnerPanel(navigatorPanel, Globals::right);
		break;
	case properties:
		break;
	case toolbox:
		break;
	case modifiers:
		break;
	case help:
		toggleInnerPanel(helpPanel, Globals::left);
		break;
	case webpage:
		break;
	case about:
		break;

	default:
		return false;
	};

	return true;
}

bool MainLayout::isInnerPanelVisible(InnerPanel* innerPanel)
{
	if (innerPanel->isVisible())
		return true;
	if (getPanelContainerOf(innerPanel, innerPanel->position) != nullptr)
		return true;
	return false;
}

void MainLayout::toggleInnerPanel(InnerPanel* innerPanel, Globals::Position position)
{
	if (innerPanel != nullptr)
	{
		PanelContainer *panel = getPanelContainerOf(innerPanel, position);
		if (panel != nullptr)
		{
			panel->removeInnerPanel(innerPanel);
		}
		else
		{
			if (position == Globals::left)
			{
				getPanelContainer(Globals::left)->addInnerPanel(innerPanel, true);
			}
			else if (position == Globals::right)
			{
				getPanelContainer(Globals::right)->addInnerPanel(innerPanel, true);
			}
			else if (position == Globals::top)
			{
				getPanelContainer(Globals::top)->addInnerPanel(innerPanel, true);
			}
			else if (position == Globals::bottom)
			{
				getPanelContainer(Globals::bottom)->addInnerPanel(innerPanel, true);
			}
		}
	}
	resized();
}


PanelContainer* MainLayout::getPanelContainer(Globals::Position position)
{
	if (position == Globals::top)
		return panelContainers[0];
	if (position == Globals::right)
		return panelContainers[1];
	if (position == Globals::bottom)
		return panelContainers[2];
	if (position == Globals::left)
		return panelContainers[3];

	return nullptr;
}

PanelContainer* MainLayout::getPanelContainerOf(InnerPanel* innerPanel, Globals::Position guessPosition)
{
	if (getPanelContainer(guessPosition)->isInnerPanelVisible(innerPanel))
	{
		return getPanelContainer(guessPosition);
	}
	else
	{
		if (guessPosition != Globals::top && getPanelContainer(Globals::top)->isInnerPanelVisible(innerPanel))
		{
			return getPanelContainer(Globals::top);
		}
		if (guessPosition != Globals::right && getPanelContainer(Globals::right)->isInnerPanelVisible(innerPanel))
		{
			return getPanelContainer(Globals::right);
		}
		if (guessPosition != Globals::bottom && getPanelContainer(Globals::bottom)->isInnerPanelVisible(innerPanel))
		{
			return getPanelContainer(Globals::bottom);
		}
		if (guessPosition != Globals::left && getPanelContainer(Globals::left)->isInnerPanelVisible(innerPanel))
		{
			return getPanelContainer(Globals::left);
		}
	}

	return nullptr;
}
