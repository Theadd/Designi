/*
  ==============================================================================

    MainLayout.cpp
    Created: 14 Oct 2013 9:37:33pm
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../Globals.h";
#include "MainLayout.h"

#include "../MainWindow.h"


MainLayout::MainLayout(MainWindow& _mainWindow) : Component(), mainWindow(_mainWindow)
{
	DBG("dbg: MainLayout()");
    //setBounds(0, 0, 490, 414);
    setName("MainLayout");

	toolbarComponent = nullptr;
	addAndMakeVisible(toolbarComponent = new ToolbarComponent(32));

    addAndMakeVisible(&leftpanelcontainer);
	
	//TEST
	rightPanelContainer = nullptr;
	addAndMakeVisible(rightPanelContainer = new PanelContainer(PanelContainer::right));
	rightPanelContainer->setBounds(400,32,250,600);

	DBG("ADDING PANEL A TO RIGHT");
	Panel *panelA;
	Panel *panelB;
	Panel *panelC;
	rightPanelContainer->addAndMakeVisible(panelA = new Panel("Panel A"));
	DBG("ADDING PANEL B TO RIGHT");
	rightPanelContainer->addAndMakeVisible(panelB = new Panel("Panel B"));
	DBG("ADDING PANEL C TO RIGHT");
	rightPanelContainer->addAndMakeVisible(panelC = new Panel("Panel C"));
	Panel innerPanel("Inner Panel");
	panelA->addAndMakeVisible(&innerPanel);
	//

	resized();
}

MainLayout::~MainLayout()
{
	toolbarComponent = nullptr;
}

void MainLayout::resized()
{
	Rectangle<int> r = this->getLocalBounds();

	if (toolbarComponent != nullptr)
		toolbarComponent->setBounds(this->getLocalBounds());

	leftpanelcontainer.setBounds(0, TOOLBARSIZE, 250, this->getHeight() - TOOLBARSIZE);

	if  (rightPanelContainer != nullptr)
	{
		rightPanelContainer->setBounds(r.getWidth() - rightPanelContainer->getWidth(), TOOLBARSIZE, rightPanelContainer->getWidth(), r.getHeight() - TOOLBARSIZE);
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
		menu.addCommandItem (commandManager, leftPanel);
		menu.addCommandItem (commandManager, rightPanel);
		menu.addSeparator();

			PopupMenu toolbarsSubMenu;
            
			toolbarsSubMenu.addCommandItem (commandManager, fileToolbar);
			toolbarsSubMenu.addCommandItem (commandManager, clipboardToolbar);
			toolbarsSubMenu.addCommandItem (commandManager, historyToolbar);
			toolbarsSubMenu.addCommandItem (commandManager, drawableToolbar);

			menu.addSubMenu ("Toolbars", toolbarsSubMenu);

		menu.addSeparator();
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
	const CommandID ids[] = {newProject, newDesign, openProject, openRecentProject, closeProject, save, saveAs, saveAll, print, undo, redo, cut, copy, paste, delete_, find, replace, preferences, leftPanel, rightPanel, fileToolbar, clipboardToolbar, historyToolbar, drawableToolbar, help, webpage, about};

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
		result.setTicked (true);
		result.addDefaultKeypress ('l', ModifierKeys::commandModifier | ModifierKeys::altModifier);
		break;
	case rightPanel:
		result.setInfo ("Right Panel", "", generalCategory, 0);
		result.setTicked (true);
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
	case help:
		result.setInfo ("Help", "", generalCategory, 0);
		result.setTicked (true);
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
		break;
	case rightPanel:
		break;
	case fileToolbar:
		break;
	case clipboardToolbar:
		break;
	case historyToolbar:
		break;
	case drawableToolbar:
		break;
	case help:
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
