/*
  ==============================================================================

    MainLayout.cpp
    Created: 14 Oct 2013 9:37:33pm
    Author:  admin

  ==============================================================================
*/

#include "../../../Headers.h"

#include "MainLayout.h"

#include "Toolbars.h"
#include "../../Components/Basics/InnerPanelContainers.h"
//#include "InnerPanel.h"
#include "../../Components/Panels/InnerPanels.h"
#include "../../Components/Panels/ProjectExplorerPanel.h"
#include "../../Components/Panels/KeyMappingsPanel.h"
#include "../../Styles/ExtendedLookAndFeel.h"
#include "../MainWindow.h"
#include "../../../Core/Project.h"
#include "../../../Application.h"
#include "../../Components/Editors/FilePreviewComponent.h"


FloatingComponentOverlay::FloatingComponentOverlay() : text("")
{
	setInterceptsMouseClicks(false, false);
	setWantsKeyboardFocus(false);
	setAlwaysOnTop(true);
}

void FloatingComponentOverlay::paint (Graphics& g)
{
	g.fillAll (Colours::darkblue.withAlpha(0.4f));
	g.setColour (Colours::white);
    g.drawFittedText (text, getLocalBounds().reduced (8, 0), Justification::centred, 5);
	g.setColour (Colours::black);
    g.drawRect (getLocalBounds());
}

void FloatingComponentOverlay::mouseEnter (const MouseEvent &event)
{
	if (!isVisible())
		return;

	String objClass("Undefined");
	//ArrowButton, DrawableButton, HyperlinkButton, ImageButton, ShapeButton, 
	//TabBarButton, TextButton, ToggleButton, and ToolbarItemComponent.
	if(ToolbarItemComponent* obj = dynamic_cast<ToolbarItemComponent*>(event.eventComponent))
		 objClass = "ToolbarItemComponent";
	else if(ToggleButton* obj = dynamic_cast<ToggleButton*>(event.eventComponent))
		 objClass = "ToggleButton";
	else if(TextButton* obj = dynamic_cast<TextButton*>(event.eventComponent))
		 objClass = "TextButton";
	else if(TabBarButton* obj = dynamic_cast<TabBarButton*>(event.eventComponent))
		 objClass = "TabBarButton";
	else if(ShapeButton* obj = dynamic_cast<ShapeButton*>(event.eventComponent))
		 objClass = "ShapeButton";
	else if(ImageButton* obj = dynamic_cast<ImageButton*>(event.eventComponent))
		 objClass = "ImageButton";
	else if(HyperlinkButton* obj = dynamic_cast<HyperlinkButton*>(event.eventComponent))
		 objClass = "HyperlinkButton";
	else if(DrawableButton* obj = dynamic_cast<DrawableButton*>(event.eventComponent))
		 objClass = "DrawableButton";
	else if(ArrowButton* obj = dynamic_cast<ArrowButton*>(event.eventComponent))
		 objClass = "ArrowButton";
	else if(Button* obj = dynamic_cast<Button*>(event.eventComponent))
		 objClass = "Button";
	/*TableHeaderComponent, TextEditor, Toolbar, ToolbarItemPalette, TooltipWindow, TopLevelWindow, 
	++AlertWindow, and ResizableWindow. ++DocumentWindow, and FileChooserDialogBox. 
	++DialogWindow, MultiDocumentPanelWindow, and --StandaloneFilterWindow., TreeView,
	++FileTreeComponent, --UIViewComponent, Viewport, and WebBrowserComponent.
	*/
	else if(WebBrowserComponent* obj = dynamic_cast<WebBrowserComponent*>(event.eventComponent))
		 objClass = "WebBrowserComponent";
	else if(Viewport* obj = dynamic_cast<Viewport*>(event.eventComponent))
		 objClass = "Viewport";
	else if(FileTreeComponent* obj = dynamic_cast<FileTreeComponent*>(event.eventComponent))
		 objClass = "FileTreeComponent";
	else if(TreeView* obj = dynamic_cast<TreeView*>(event.eventComponent))
		 objClass = "TreeView";
	else if(MultiDocumentPanelWindow* obj = dynamic_cast<MultiDocumentPanelWindow*>(event.eventComponent))
		 objClass = "MultiDocumentPanelWindow";
	else if(DialogWindow* obj = dynamic_cast<DialogWindow*>(event.eventComponent))
		 objClass = "DialogWindow";
	else if(FileChooserDialogBox* obj = dynamic_cast<FileChooserDialogBox*>(event.eventComponent))
		 objClass = "FileChooserDialogBox";
	else if(DocumentWindow* obj = dynamic_cast<DocumentWindow*>(event.eventComponent))
		 objClass = "DocumentWindow";
	else if(ResizableWindow* obj = dynamic_cast<ResizableWindow*>(event.eventComponent))
		 objClass = "ResizableWindow";
	else if(AlertWindow* obj = dynamic_cast<AlertWindow*>(event.eventComponent))
		 objClass = "AlertWindow";
	else if(TopLevelWindow* obj = dynamic_cast<TopLevelWindow*>(event.eventComponent))
		 objClass = "TopLevelWindow";
	else if(TooltipWindow* obj = dynamic_cast<TooltipWindow*>(event.eventComponent))
		 objClass = "TooltipWindow";
	else if(ToolbarItemPalette* obj = dynamic_cast<ToolbarItemPalette*>(event.eventComponent))
		 objClass = "ToolbarItemPalette";
	else if(Toolbar* obj = dynamic_cast<Toolbar*>(event.eventComponent))
		 objClass = "Toolbar";
	else if(TextEditor* obj = dynamic_cast<TextEditor*>(event.eventComponent))
		 objClass = "TextEditor";
	else if(TableHeaderComponent* obj = dynamic_cast<TableHeaderComponent*>(event.eventComponent))
		 objClass = "TableHeaderComponent";
	/*PropertyPanel, ResizableBorderComponent, ResizableCornerComponent, ResizableEdgeComponent, ScrollBar, Slider, 
	SplashScreen, StretchableLayoutResizerBar, SystemTrayIconComponent, TabbedButtonBar, TabbedComponent, */
	else if(TabbedComponent* obj = dynamic_cast<TabbedComponent*>(event.eventComponent))
		 objClass = "TabbedComponent";
	else if(TabbedButtonBar* obj = dynamic_cast<TabbedButtonBar*>(event.eventComponent))
		 objClass = "TabbedButtonBar";
	else if(SystemTrayIconComponent* obj = dynamic_cast<SystemTrayIconComponent*>(event.eventComponent))
		 objClass = "SystemTrayIconComponent";
	else if(StretchableLayoutResizerBar* obj = dynamic_cast<StretchableLayoutResizerBar*>(event.eventComponent))
		 objClass = "StretchableLayoutResizerBar";
	else if(SplashScreen* obj = dynamic_cast<SplashScreen*>(event.eventComponent))
		 objClass = "SplashScreen";
	else if(Slider* obj = dynamic_cast<Slider*>(event.eventComponent))
		 objClass = "Slider";
	else if(ScrollBar* obj = dynamic_cast<ScrollBar*>(event.eventComponent))
		 objClass = "ScrollBar";
	else if(ResizableEdgeComponent* obj = dynamic_cast<ResizableEdgeComponent*>(event.eventComponent))
		 objClass = "ResizableEdgeComponent";
	else if(ResizableCornerComponent* obj = dynamic_cast<ResizableCornerComponent*>(event.eventComponent))
		 objClass = "ResizableCornerComponent";
	else if(ResizableBorderComponent* obj = dynamic_cast<ResizableBorderComponent*>(event.eventComponent))
		 objClass = "ResizableBorderComponent";
	else if(PropertyPanel* obj = dynamic_cast<PropertyPanel*>(event.eventComponent))
		 objClass = "PropertyPanel";
	/*--LassoComponent< SelectableItemType >, ListBox, ++ FileListComponent, and TableListBox., MenuBarComponent, 
	--MidiKeyboardComponent, MultiDocumentPanel, 
	--NSViewComponent, --PluginListComponent, PopupMenu::CustomComponent, PreferencesPanel, ProgressBar, PropertyComponent,
	++BooleanPropertyComponent, ButtonPropertyComponent, ChoicePropertyComponent, SliderPropertyComponent,
	and TextPropertyComponent.*/
	else if(TextPropertyComponent* obj = dynamic_cast<TextPropertyComponent*>(event.eventComponent))
		 objClass = "TextPropertyComponent";
	else if(SliderPropertyComponent* obj = dynamic_cast<SliderPropertyComponent*>(event.eventComponent))
		 objClass = "SliderPropertyComponent";
	else if(ChoicePropertyComponent* obj = dynamic_cast<ChoicePropertyComponent*>(event.eventComponent))
		 objClass = "ChoicePropertyComponent";
	else if(ButtonPropertyComponent* obj = dynamic_cast<ButtonPropertyComponent*>(event.eventComponent))
		 objClass = "ButtonPropertyComponent";
	else if(BooleanPropertyComponent* obj = dynamic_cast<BooleanPropertyComponent*>(event.eventComponent))
		 objClass = "BooleanPropertyComponent";
	else if(PropertyComponent* obj = dynamic_cast<PropertyComponent*>(event.eventComponent))
		 objClass = "PropertyComponent";
	else if(ProgressBar* obj = dynamic_cast<ProgressBar*>(event.eventComponent))
		 objClass = "ProgressBar";
	else if(PreferencesPanel* obj = dynamic_cast<PreferencesPanel*>(event.eventComponent))
		 objClass = "PreferencesPanel";
	else if(PopupMenu::CustomComponent* obj = dynamic_cast<PopupMenu::CustomComponent*>(event.eventComponent))
		 objClass = "PopupMenu::CustomComponent";
	else if(MultiDocumentPanel* obj = dynamic_cast<MultiDocumentPanel*>(event.eventComponent))
		 objClass = "MultiDocumentPanel";
	else if(MenuBarComponent* obj = dynamic_cast<MenuBarComponent*>(event.eventComponent))
		 objClass = "MenuBarComponent";
	else if(TableListBox* obj = dynamic_cast<TableListBox*>(event.eventComponent))
		 objClass = "TableListBox";
	else if(FileListComponent* obj = dynamic_cast<FileListComponent*>(event.eventComponent))
		 objClass = "FileListComponent";
	else if(ListBox* obj = dynamic_cast<ListBox*>(event.eventComponent))
		 objClass = "ListBox";
	/*Drawable, ++DrawableComposite, DrawableImage, DrawableShape, 
	and DrawableText. ++DrawablePath, and DrawableRectangle., FileBrowserComponent,
	FilenameComponent, FilePreviewComponent, ++ImagePreviewComponent.
	FileSearchPathListComponent, GroupComponent, ImageComponent, KeyMappingEditorComponent, Label,*/
	else if(Label* obj = dynamic_cast<Label*>(event.eventComponent))
		 objClass = "Label";
	else if(KeyMappingEditorComponent* obj = dynamic_cast<KeyMappingEditorComponent*>(event.eventComponent))
		 objClass = "KeyMappingEditorComponent";
	else if(ImageComponent* obj = dynamic_cast<ImageComponent*>(event.eventComponent))
		 objClass = "ImageComponent";
	else if(GroupComponent* obj = dynamic_cast<GroupComponent*>(event.eventComponent))
		 objClass = "GroupComponent";
	else if(FileSearchPathListComponent* obj = dynamic_cast<FileSearchPathListComponent*>(event.eventComponent))
		 objClass = "FileSearchPathListComponent";
	else if(ImagePreviewComponent* obj = dynamic_cast<ImagePreviewComponent*>(event.eventComponent))
		 objClass = "ImagePreviewComponent";
	else if(FilePreviewComponent* obj = dynamic_cast<FilePreviewComponent*>(event.eventComponent))
		 objClass = "FilePreviewComponent";
	else if(FilenameComponent* obj = dynamic_cast<FilenameComponent*>(event.eventComponent))
		 objClass = "FilenameComponent";
	else if(FileBrowserComponent* obj = dynamic_cast<FileBrowserComponent*>(event.eventComponent))
		 objClass = "FileBrowserComponent";
	else if(DrawableRectangle* obj = dynamic_cast<DrawableRectangle*>(event.eventComponent))
		 objClass = "DrawableRectangle";
	else if(DrawablePath* obj = dynamic_cast<DrawablePath*>(event.eventComponent))
		 objClass = "DrawablePath";
	else if(DrawableText* obj = dynamic_cast<DrawableText*>(event.eventComponent))
		 objClass = "DrawableText";
	else if(DrawableShape* obj = dynamic_cast<DrawableShape*>(event.eventComponent))
		 objClass = "DrawableShape";
	else if(DrawableImage* obj = dynamic_cast<DrawableImage*>(event.eventComponent))
		 objClass = "DrawableImage";
	else if(DrawableComposite* obj = dynamic_cast<DrawableComposite*>(event.eventComponent))
		 objClass = "DrawableComposite";
	else if(Drawable* obj = dynamic_cast<Drawable*>(event.eventComponent))
		 objClass = "Drawable";
	/*--ActiveXControlComponent, --AudioDeviceSelectorComponent, --AudioProcessorEditor, --BrowserPluginComponent, 
	BubbleComponent,++BubbleMessageComponent. Button, CallOutBox, CaretComponent, CodeEditorComponent, 
	ColourSelector, ComboBox, ConcertinaPanel, --DirectShowComponent, */
	else if(ConcertinaPanel* obj = dynamic_cast<ConcertinaPanel*>(event.eventComponent))
		 objClass = "ConcertinaPanel";
	else if(ComboBox* obj = dynamic_cast<ComboBox*>(event.eventComponent))
		 objClass = "ComboBox";
	else if(ColourSelector* obj = dynamic_cast<ColourSelector*>(event.eventComponent))
		 objClass = "ColourSelector";
	else if(CodeEditorComponent* obj = dynamic_cast<CodeEditorComponent*>(event.eventComponent))
		 objClass = "CodeEditorComponent";
	else if(CaretComponent* obj = dynamic_cast<CaretComponent*>(event.eventComponent))
		 objClass = "CaretComponent";
	else if(CallOutBox* obj = dynamic_cast<CallOutBox*>(event.eventComponent))
		 objClass = "CallOutBox";
	else if(BubbleMessageComponent* obj = dynamic_cast<BubbleMessageComponent*>(event.eventComponent))
		 objClass = "BubbleMessageComponent";
	else if(BubbleComponent* obj = dynamic_cast<BubbleComponent*>(event.eventComponent))
		 objClass = "BubbleComponent";

	text = objClass;
	//MainWindow* window = findParentComponentOfClass <MainWindow>();
	//if (window != 0)
	//{
	//	Rectangle<int> sBounds = event.eventComponent->getScreenBounds();
	//	Rectangle<int> mBounds = window->getScreenBounds();
	//	setBounds(sBounds.getX() - mBounds.getX(), sBounds.getY() - mBounds.getY() - window->getTitleBarHeight() - MENUBARHEIGHT, sBounds.getWidth(), sBounds.getHeight());
		setBounds(event.eventComponent->getScreenBounds());
		DBG("Inspector: "+event.eventComponent->getName()+" : " + objClass + " - " + event.eventComponent->getBounds().toString());
	//}
}

//////////////////////////////////////////////////////////////////

MainLayout::MainLayout(MainWindow& _mainWindow) : Component(), mainWindow(_mainWindow)
{
	DBG("dbg: MainLayout()");
    //setBounds(0, 0, 490, 414);
    setName("MainLayout");
	JUCEDesignerApp::getApp().mainLayout = this;

}

MainLayout::~MainLayout()
{
	panelContainerBox.removeAllChildren();
	toolbarComponent = nullptr;
	helpPanel = nullptr;
	fileBrowserPanel = nullptr;
	navigatorPanel = nullptr;
	floatingComponentOverlay = nullptr;
	//workingPath = nullptr;
}

void MainLayout::loadLayout ()
{
	
	addAndMakeVisible(toolbarComponent = new ToolbarComponent(TOOLBARSIZE));
	addAndMakeVisible(&panelContainerBox);
	
	//ADD PANEL CONTAINERS
	panelContainers.add(new PanelContainer(Globals::top, this));
	panelContainers.add(new PanelContainer(Globals::right, this));
	panelContainers.add(new PanelContainer(Globals::bottom, this));
	panelContainers.add(new PanelContainer(Globals::left, this));
	panelContainers.add(new PanelContainer(Globals::center, this));

	
	//ADD COMPONENT LISTENERS TO PANEL CONTAINERS
	for (int i = 0; i < panelContainers.size(); ++i)
		panelContainers[i]->addComponentListener(this);

	PanelContainer *leftPanelContainer = getPanelContainer(Globals::left);
	PanelContainer *rightPanelContainer = getPanelContainer(Globals::right);
	PanelContainer *topPanelContainer = getPanelContainer(Globals::top);
	PanelContainer *bottomPanelContainer = getPanelContainer(Globals::bottom);
	PanelContainer *centerPanelContainer = getPanelContainer(Globals::center);

	panelContainerBox.addChildComponent(rightPanelContainer);
	rightPanelContainer->setBounds(400,32,250,600);
	panelContainerBox.addChildComponent(leftPanelContainer);
	leftPanelContainer->setBounds(0,32,250,600);
	panelContainerBox.addChildComponent(topPanelContainer);
	topPanelContainer->setBounds(0,32,250,250);
	panelContainerBox.addChildComponent(bottomPanelContainer);
	bottomPanelContainer->setBounds(0,32,250,250);
	panelContainerBox.addChildComponent(centerPanelContainer);
	centerPanelContainer->setBounds(0,32,250,250);

	//navigatorPanel
	rightPanelContainer->addInnerPanel(navigatorPanel = new NavigatorPanel());
	JUCEDesignerApp::getApp().navigatorTree.addListener(navigatorPanel);
	//fileBrowserPanel
	fileBrowserPanel = nullptr;
	leftPanelContainer->addInnerPanel(fileBrowserPanel = new FileBrowserPanel(), true);
	fileBrowserPanel->setBrowserRoot(File::getSpecialLocation(File::userHomeDirectory));//(project->getProjectFolder());//*workingPath);
	//helpPanel
	helpPanel = nullptr;
	leftPanelContainer->addInnerPanel(helpPanel = new HelpPanel(), true);
	//keyMappingsPanel
	keyMappingsPanel = nullptr;
	centerPanelContainer->addInnerPanel(keyMappingsPanel = new KeyMappingsPanel(), (int) 0);

	//set project layout if it is already loaded
	if (JUCEDesignerApp::getApp().getProject() != nullptr)
		setProject(JUCEDesignerApp::getApp().getProject());

	resized();
}

void MainLayout::resized ()
{
	DBG("MainLayout::resized()");
	Rectangle<int> r = this->getLocalBounds();
	PanelContainer *leftPanelContainer = getPanelContainer(Globals::left);
	PanelContainer *rightPanelContainer = getPanelContainer(Globals::right);
	PanelContainer *topPanelContainer = getPanelContainer(Globals::top);
	PanelContainer *bottomPanelContainer = getPanelContainer(Globals::bottom);
	PanelContainer *centerPanelContainer = getPanelContainer(Globals::center);

	

	if (toolbarComponent != nullptr)
	{
		toolbarComponent->setBounds(this->getLocalBounds());
		int toolbarThickness = toolbarComponent->getToolbarThickness();
		if (!toolbarComponent->isVertical())
		{
			//toolbar is horizontal
			panelContainerBox.setBounds(0, toolbarThickness, r.getWidth(), r.getHeight() - toolbarThickness);
		}
		else
		{
			//toolbar is vertical
			panelContainerBox.setBounds(toolbarThickness, 0, r.getWidth() - toolbarThickness, r.getHeight());
		}
	}
	r = panelContainerBox.getLocalBounds();

	if (bottomPanelContainer != nullptr)
	{
		bottomPanelContainer->setBounds(0, r.getHeight() - bottomPanelContainer->getHeight(), r.getWidth(), bottomPanelContainer->getHeight());
	}

	if  (leftPanelContainer != nullptr)
	{
		int modHeight = (bottomPanelContainer != nullptr && bottomPanelContainer->isVisible()) ? -1 * bottomPanelContainer->getHeight() : 0;
		leftPanelContainer->setBounds(0, 0, leftPanelContainer->getWidth(), r.getHeight() + modHeight);
	}

	if  (rightPanelContainer != nullptr)
	{
		int modHeight = (bottomPanelContainer != nullptr && bottomPanelContainer->isVisible()) ? -1 * bottomPanelContainer->getHeight() : 0;
		rightPanelContainer->setBounds(r.getWidth() - rightPanelContainer->getWidth(), 0, rightPanelContainer->getWidth(), r.getHeight() + modHeight);
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

		topPanelContainer->setBounds(0 + startX, 0, r.getWidth() + modWidth, topPanelContainer->getHeight());
	}

	if (centerPanelContainer != nullptr)
	{
		int startX = 0;
		int startY = 0;
		int modWidth = 0;
		int modHeight = 0;

		if (leftPanelContainer != nullptr && leftPanelContainer->isVisible())
		{
			startX = leftPanelContainer->getX() + leftPanelContainer->getWidth();
			modWidth -= startX;
		}
		if (rightPanelContainer != nullptr && rightPanelContainer->isVisible())
			modWidth -= rightPanelContainer->getWidth();

		if (topPanelContainer != nullptr && topPanelContainer->isVisible())
		{
			startY = topPanelContainer->getY() + topPanelContainer->getHeight();
			modHeight -= startY;
		}
		if (bottomPanelContainer != nullptr && bottomPanelContainer->isVisible())
			modHeight -= bottomPanelContainer->getHeight();

		centerPanelContainer->setBounds(0 + startX, 0 + startY, r.getWidth() + modWidth, r.getHeight() + modHeight);
	}

}

void MainLayout::paint (Graphics& g)
{
	((ExtendedLookAndFeel*) &getLookAndFeel())->drawMainLayout (g, *this);
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


void MainLayout::componentMovedOrResized (Component& /*component*/, bool /*wasMoved*/, bool /*wasResized*/)
{
	resized();
}


StringArray MainLayout::getMenuBarNames()
{

	if (JUCEDesignerApp::getApp().getLanguage().equalsIgnoreCase("spanish"))
	{
		const char* const names[] = { "Archivo", "Editar", "Ver", "Ventana", "Ayuda", nullptr };
		return StringArray (names);
	}
	else if (JUCEDesignerApp::getApp().getLanguage().equalsIgnoreCase("catalan"))
	{
		const char* const names[] = { "Fitxer", "Editar", "Veure", "Finestra", "Ajuda", nullptr };
		return StringArray (names);
	}
	else
	{
		const char* const names[] = { "File", "Edit", "View", "Window", "Help", nullptr };
		return StringArray (names);
	}

	
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
		menu.addCommandItem (commandManager, StandardApplicationCommandIDs::undo);
		menu.addCommandItem (commandManager, StandardApplicationCommandIDs::redo);
		menu.addSeparator();
		menu.addCommandItem (commandManager, StandardApplicationCommandIDs::cut);
		menu.addCommandItem (commandManager, StandardApplicationCommandIDs::copy);
		menu.addCommandItem (commandManager, StandardApplicationCommandIDs::paste);
		menu.addCommandItem (commandManager, StandardApplicationCommandIDs::del);
		menu.addSeparator();
		menu.addCommandItem (commandManager, StandardApplicationCommandIDs::selectAll);
		menu.addCommandItem (commandManager, StandardApplicationCommandIDs::deselectAll);
		menu.addSeparator();
		menu.addCommandItem (commandManager, showFindPanel);
		menu.addCommandItem (commandManager, findSelection);
		menu.addCommandItem (commandManager, findNext);
		menu.addCommandItem (commandManager, findPrevious);
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
			toolbarsSubMenu.addSeparator();
			toolbarsSubMenu.addCommandItem (commandManager, toolbarOrientation);
			toolbarsSubMenu.addSeparator();
			toolbarsSubMenu.addCommandItem (commandManager, toolbarCustomize);

			menu.addSubMenu ("Toolbars", toolbarsSubMenu);

		menu.addSeparator();
		//fileBrowser, navigator, properties, toolbox, modifiers,
		menu.addCommandItem (commandManager, fileBrowser);
		menu.addCommandItem (commandManager, navigator);
		menu.addCommandItem (commandManager, properties);
		menu.addCommandItem (commandManager, toolbox);
		menu.addCommandItem (commandManager, modifiers);
		menu.addCommandItem (commandManager, help);
		menu.addSeparator();
		menu.addCommandItem (commandManager, componentInspector);
		menu.addSeparator();

			PopupMenu languageSubMenu;
			languageSubMenu.addCommandItem (commandManager, catalanLang);
			languageSubMenu.addCommandItem (commandManager, englishLang);
			languageSubMenu.addCommandItem (commandManager, spanishLang);
			

			menu.addSubMenu (T("Language"), languageSubMenu);
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
	const CommandID ids[] = {newProject, newDesign, openProject, openRecentProject, closeProject, save, saveAs, saveAll, print, preferences, showFindPanel, findSelection, findNext, findPrevious, leftPanel, rightPanel, fileToolbar, clipboardToolbar, historyToolbar, drawableToolbar, toolbarOrientation, toolbarCustomize, fileBrowser, navigator, properties, toolbox, modifiers, help, componentInspector, englishLang, spanishLang, catalanLang, webpage, about};

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
		result.setActive ((fileBrowserPanel != nullptr));
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
	/*case undo:
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
		break;*/
	case showFindPanel:
        result.setInfo (TRANS ("Find"), TRANS ("Searches for text in the current document."), "Editing", 0);
        result.defaultKeypresses.add (KeyPress ('f', ModifierKeys::commandModifier, 0));
        break;

    case findSelection:
        result.setInfo (TRANS ("Find Selection"), TRANS ("Searches for the currently selected text."), "Editing", 0);
        result.setActive (false);
        result.defaultKeypresses.add (KeyPress ('l', ModifierKeys::commandModifier, 0));
        break;

    case findNext:
        result.setInfo (TRANS ("Find Next"), TRANS ("Searches for the next occurrence of the current search-term."), "Editing", 0);
        result.defaultKeypresses.add (KeyPress ('g', ModifierKeys::commandModifier, 0));
        break;

    case findPrevious:
        result.setInfo (TRANS ("Find Previous"), TRANS ("Searches for the previous occurrence of the current search-term."), "Editing", 0);
        result.defaultKeypresses.add (KeyPress ('g', ModifierKeys::commandModifier | ModifierKeys::shiftModifier, 0));
        result.defaultKeypresses.add (KeyPress ('d', ModifierKeys::commandModifier, 0));
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
	case toolbarOrientation:
		result.setInfo ("Vertical/Horizontal", "", generalCategory, 0);
		result.setTicked (false);
		break;
	case toolbarCustomize:
		result.setInfo ("Customize...", "", generalCategory, 0);
		result.setTicked (false);
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
	case componentInspector:
		result.setInfo ("Component Inspector", "Shows a floating overlay over a component when mouse hover on it.", generalCategory, 0);
		result.setTicked ((floatingComponentOverlay != nullptr && floatingComponentOverlay->isVisible() ? true : false));
		result.setActive ((floatingComponentOverlay != nullptr) ? true : false);
		result.addDefaultKeypress (KeyPress::F2Key, 0);
		break;
	case englishLang:
		result.setInfo (T("English"), "", generalCategory, 0);
		result.setTicked ((JUCEDesignerApp::getApp().getLanguage().isEmpty() ? true : false));
		break;
	case spanishLang:
		result.setInfo (T(String(CharPointer_UTF8 ("Espa\xc3\xb1ol"))), "", generalCategory, 0);
		result.setTicked ((JUCEDesignerApp::getApp().getLanguage().equalsIgnoreCase("spanish") ? true : false));
		break;
	case catalanLang:
		result.setInfo (T(String(CharPointer_UTF8 ("Catal\xc3\xa0"))), "", generalCategory, 0);
		result.setTicked ((JUCEDesignerApp::getApp().getLanguage().equalsIgnoreCase("catalan") ? true : false));
		break;
	case webpage:
		result.setInfo ("Webpage", "", generalCategory, 0);
		result.setTicked (false);
		break;
	case about:
		result.setInfo ("About Designi", "", generalCategory, 0);
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
		showOpenProjectDialog();
		break;
	case openRecentProject:
		break;
	case closeProject:
		closeCurrentProject ();
		break;
	case save:
		break;
	case saveAs:
		break;
	case saveAll:
		break;
	case print:
		break;
	/*case undo:
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
		break;*/
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
	case toolbarOrientation:
		toolbarComponent->setVertical(!toolbarComponent->isVertical());
		resized();
		break;
	case toolbarCustomize:
		toolbarComponent->showCustomisationDialog();
		break;
	case fileBrowser:
		toggleInnerPanel(fileBrowserPanel, Globals::left, true);
		break;
	case navigator:
		toggleInnerPanel(navigatorPanel, Globals::right, true);
		break;
	case properties:
		break;
	case toolbox:
		break;
	case modifiers:
		break;
	case help:
		toggleInnerPanel(helpPanel, Globals::left, true);
		break;
	case componentInspector:
		//floatingComponentOverlay->setVisible(!floatingComponentOverlay->isVisible());
		JUCEDesignerApp::getApp().toggleComponentInspector();
		break;
	case englishLang:
		JUCEDesignerApp::getApp().setLanguage("");
		updateLocalisedStrings();
		break;
	case spanishLang:
		JUCEDesignerApp::getApp().setLanguage("spanish");
		updateLocalisedStrings();
		break;
	case catalanLang:
		JUCEDesignerApp::getApp().setLanguage("catalan");
		updateLocalisedStrings();
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

void MainLayout::toggleInnerPanel(InnerPanel* innerPanel, Globals::Position position, bool isBeingClosed)
{
	if (innerPanel != nullptr)
	{
		PanelContainer *panel = getPanelContainerOf(innerPanel, position);
		if (panel != nullptr)
		{
			DBG("[toggleInnerPanel] Found panel container! isBeingClosed = "+String(isBeingClosed));
			//check if needs to be saved before closing
			if (isBeingClosed)
			{
				innerPanel->shouldBeVisible = false;
				//int index = getDocumentIndex(innerPanel);
				//if (index >= 0 && codeEditorPanels[index]->getNeedsToBeSaved())
				OpenDocumentManager::Document* document = innerPanel->getDocument();
				if (document == nullptr)
					DBG("INNER PANEL DOCUMENT = nullptr");

				if (document != nullptr && document->needsSaving())
				{
					DBG("JOINS ALERT!");
					int result = AlertWindow::showYesNoCancelBox (AlertWindow::NoIcon, "Save changes to the following items?", document->getFile().getFileName(), "Yes", "No", "Cancel", nullptr, nullptr);
					switch (result)
					{
					case 1:
						//save
						if (!document->save())
						{
							AlertWindow::showMessageBox (AlertWindow::NoIcon, "Save error!", "File could not be written to disk!", "Ok");
							return;
						}
						fileBrowserPanel->refresh();
						break;
					case 2:
						//dont save
						break;
					case 0:
						//cancel closing
						return;
						break;
					};
				}
			}
			panel->removeInnerPanel(innerPanel);
			//unload document in case we are closing it (only removes document based inner panels)
			if (isBeingClosed)
				unloadDocument(innerPanel);
		}
		else
		{
			innerPanel->shouldBeVisible = true;

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
			else if (position == Globals::center)
			{
				getPanelContainer(Globals::center)->addInnerPanel(innerPanel, true);
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
	if (position == Globals::center)
		return panelContainers[4];

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
		if (guessPosition != Globals::center && getPanelContainer(Globals::center)->isInnerPanelVisible(innerPanel))
		{
			return getPanelContainer(Globals::center);
		}
	}

	return nullptr;
}

void MainLayout::loadDocument(File& file)
{

	OpenDocumentManager::Document *document = JUCEDesignerApp::getApp().openDocumentManager.openFile(JUCEDesignerApp::getApp().getProject(), file);

	if (document->loadedOk())
	{
		InnerPanel *innerPanel = getInnerPanelForDocument(document);
		PanelContainer *container = getPanelContainerOf(innerPanel, Globals::center);
		if (container != nullptr)
		{
			//its already inside a panel container, bring it to front
			container->showInnerPanel(innerPanel);
			JUCEDesignerApp::setActiveInnerPanel(innerPanel);
		}
		else
		{
			//not attached to any panel container, place it on center
			getPanelContainer(Globals::center)->addInnerPanel(innerPanel, false);
			getPanelContainer(Globals::center)->showInnerPanel(innerPanel);
			JUCEDesignerApp::setActiveInnerPanel(innerPanel);
		}
	}
}

void MainLayout::unloadDocument(InnerPanel* innerPanel)
{
	DBG("UNLOAD DOCUMENT "+innerPanel->getName());
	int index = getDocumentIndex(innerPanel);
	if (index >= 0)
		unloadDocumentAt(index);
}

void MainLayout::unloadDocumentAt(int /*index*/)
{
	//codeEditorPanels.remove(index, true);
}

int MainLayout::getDocumentIndex(InnerPanel* /*innerPanel*/)
{
	/*for (int i = 0; i < codeEditorPanels.size(); ++i)
		if (codeEditorPanels[i] == innerPanel)
			return i;
	*/
	return -1;
}

void MainLayout::setProject(Project* project)
{
	PanelContainer *leftPanelContainer = getPanelContainer(Globals::left);

	//ProjectExplorerPanel
	projectExplorerPanel = nullptr;
	leftPanelContainer->addInnerPanel(projectExplorerPanel = new ProjectExplorerPanel(*project), (int) 0);

}

void MainLayout::closeCurrentProject()
{
	//if (fileBrowserPanel != nullptr)
	//{
	//	//if (JUCEDesignerApp::getApp().navigatorTree.isValid())
	//	{
	//		JUCEDesignerApp::getApp().navigatorTree.removeListener(navigatorPanel);
	//		DBG("#### JUCEDesignerApp::getApp().navigatorTree.removeListener(navigatorPanel);");
	//	}

	//	for (int i = 0; i < panelContainers.size(); ++i)
	//		panelContainers[i]->removeAllInnerPanels();

	//	navigatorPanel = nullptr;
	//	fileBrowserPanel = nullptr;
	//	helpPanel = nullptr;
		projectExplorerPanel = nullptr;
		//codeEditorPanels.clear();
		editors.clear();	//TODO: close only editors for opened project files
	//}
}

void MainLayout::showOpenProjectDialog ()
{
	WildcardFileFilter wildcardFilter ("*.jucer", String::empty, "Open Project Filter");
	FileBrowserComponent browser (FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles,
	File::getSpecialLocation(File::userHomeDirectory),
	&wildcardFilter,
	nullptr);
	FileChooserDialogBox dialogBox ("Open Project", "Specify description", browser, true, Colours::darkorange);
	if (dialogBox.show())
	{
		File selectedFile = browser.getSelectedFile (0);
		DBG("showOpenProjectDialog() selectedFile = "+selectedFile.getFullPathName());
		if (!selectedFile.existsAsFile())
			return;

		if (selectedFile.existsAsFile() && selectedFile.hasWriteAccess())
		{
			JUCEDesignerApp::getApp().openProject(selectedFile);
			if (JUCEDesignerApp::getApp().getProject() != nullptr)	//if its a valid JUCE project
			{
				closeCurrentProject();
				setProject(JUCEDesignerApp::getApp().getProject());
				resized();
			}
		}
		else return;	//selected file cannot be written
	}
	else return;	//no file was selected
}

void MainLayout::updateLocalisedStrings ()
{
	helpPanel->updateLocalisedStrings();
	fileBrowserPanel->updateLocalisedStrings();
}

InnerPanel* MainLayout::getInnerPanelForDocument(OpenDocumentManager::Document* document)
{
	for (int i = editors.size(); --i >= 0;)
		if (editors[i]->document == document)
			return editors[i]->innerPanel;
	
	//Not found, create a new document <-> editor relation
	DocumentEditor *editor = new DocumentEditor;
	editor->document = document;
	editor->innerPanel = (InnerPanel *) document->createViewer();
	editors.add(editor);

	return editor->innerPanel;
}