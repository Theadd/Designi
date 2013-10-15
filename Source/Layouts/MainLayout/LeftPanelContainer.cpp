/*
  ==============================================================================

    MainLayout.cpp
    Created: 11 Oct 2013 9:21:11pm
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
//#include "../Globals.h"

class ProjectFileFilter : public FileFilter
{
public:

	ProjectFileFilter() : FileFilter("FileFilter for project directory trees.")
	{

	}

	~ProjectFileFilter ()
	{

	}

	bool isFileSuitable(const File &file) const
	{
		return (file.getFileExtension().equalsIgnoreCase(".cpp") || file.getFileExtension().equalsIgnoreCase(".h"));
	}

	bool isDirectorySuitable (const File &file) const
	{
		return true;
	}

private:

};

class FileBrowserTabHeader : public Component
{
public:

    FileBrowserTabHeader() : Component()
    {
        setBounds(0, 0, 170, 25);
        setName("FileBrowserTabHeader");

        projectNameLabel.setBounds(5, 5, 115, 15);
        projectNameLabel.setText("Project Name", NotificationType());
        //projectNameLabel.setColour(Label::backgroundColourId, Colours::transparentBlack);
        projectNameLabel.setColour(Label::textColourId, Colour::fromString("70FFFFFF"));
        addAndMakeVisible(&projectNameLabel);

        selectFileTreeA.setBounds(120, 5, 20, 20);
        selectFileTreeA.setName("selectFileTreeA");
        selectFileTreeA.setButtonText("A");
		selectFileTreeA.setTooltip("File browser remembers two locations, A and B. Use these buttons to switch between them.");
        addAndMakeVisible(&selectFileTreeA);

		selectFileTreeB.setBounds(140, 5, 20, 20);
        selectFileTreeB.setName("selectFileTreeB");
        selectFileTreeB.setButtonText("B");
		selectFileTreeB.setTooltip("File browser remembers two locations, A and B. Use these buttons to switch between them.");
        addAndMakeVisible(&selectFileTreeB);

		resized();

    }

	void resized()
	{
		projectNameLabel.setBoundsInset (BorderSize<int> (5, 5, 5, 50));
		selectFileTreeA.setBounds(projectNameLabel.getWidth() + 10, 5, 20, 20);
		selectFileTreeB.setBounds(projectNameLabel.getWidth() + 30, 5, 20, 20);
		//DBG("Resized FileBrowserTabHeader");
		//DBG(this->getBounds().toString());
		//DBG(projectNameLabel.getBounds().toString());
	}

	void paint (Graphics& g)
	{
		g.fillAll (Colour((uint8) 49, (uint8) 124, (uint8) 205));
	}

	void setBrowserMouseListener(MouseListener *listener)
	{
		selectFileTreeA.addMouseListener(listener, false);
		selectFileTreeB.addMouseListener(listener, false);
	}

private:
    Label projectNameLabel;
    TextButton selectFileTreeA;
	TextButton selectFileTreeB;

};

class FileBrowserTab : public Component
{
public:
	FileBrowserTab() : thread ("FileTreeComponent thread")
	{
		File folder (File::getSpecialLocation (File::userHomeDirectory));
        //while (folder.getParentDirectory() != folder)
        //    folder = folder.getParentDirectory();
		projectFileFilter = new ProjectFileFilter();
		//DBG("two");

        directoryList = new DirectoryContentsList(projectFileFilter, thread);
        directoryList->setDirectory (folder, true, true);
        thread.startThread (3);
		//DBG("three");
        fileTreeCompA = nullptr;
		fileTreeCompB = nullptr;

        addAndMakeVisible (fileTreeCompA = new FileTreeComponent (*directoryList));
		addAndMakeVisible (fileTreeCompB = new FileTreeComponent (*directoryList));
		fileTreeCompB->setVisible(false);
		addAndMakeVisible (&fileBrowserTabHeader);
		//ADD this to the mouse listeners of "A" and "B" buttons.
		fileBrowserTabHeader.setBrowserMouseListener(this);

	}

	~FileBrowserTab() {
		fileTreeCompA = nullptr;
		fileTreeCompB = nullptr;
        directoryList = nullptr; // (need to make sure this is deleted before the TimeSliceThread)
		projectFileFilter = nullptr;
	}

	void resized() {
		if (fileTreeCompA != nullptr)
			fileTreeCompA->setBoundsInset (BorderSize<int> (30, 5, 5, 5));
		if (fileTreeCompB != nullptr)
			fileTreeCompB->setBoundsInset (BorderSize<int> (30, 5, 5, 5));

		fileBrowserTabHeader.setBounds(0, 0, this->getWidth(), 30);
		//DBG("Resized FileBrowserTab");
	}

	void mouseUp (const MouseEvent &event)
	{
		if (event.mouseWasClicked()) {
			if (event.eventComponent->getName().equalsIgnoreCase("selectFileTreeA")) {
				fileTreeCompA->setVisible(true);
				fileTreeCompB->setVisible(false);
			} else if (event.eventComponent->getName().equalsIgnoreCase("selectFileTreeB")) {
				fileTreeCompA->setVisible(false);
				fileTreeCompB->setVisible(true);
			}
		}
	}


private:
	ScopedPointer <FileTreeComponent> fileTreeCompA;
	ScopedPointer <FileTreeComponent> fileTreeCompB;
    ScopedPointer <DirectoryContentsList> directoryList;
	ScopedPointer <ProjectFileFilter> projectFileFilter;
    TimeSliceThread thread;
	FileBrowserTabHeader fileBrowserTabHeader;

};

class HelpPanel : public Component, private Timer
{
public:

	HelpPanel() : lastComponentUnderMouse (nullptr)
	{
		setName("HelpPanel");
		setBounds(0, 0, 150, 90);
		_isHidden = false;
		resizableEdgeComponent = nullptr;
		componentBoundsConstrainer = nullptr;
		componentBoundsConstrainer = new ComponentBoundsConstrainer();
		componentBoundsConstrainer->setMinimumSize(50, 60);
		componentBoundsConstrainer->setMaximumHeight(200);
		addAndMakeVisible(resizableEdgeComponent = new ResizableEdgeComponent(this, componentBoundsConstrainer, ResizableEdgeComponent::topEdge));
		//set colours for HelpPanelHeader
		//helpPanelHeader.setColour(Label::backgroundColourId, Layout::getColourFor(LayoutColourIds::headerBackgroundColour));
        //helpPanelHeader.setColour(Label::textColourId, Layout::getColourFor(LayoutColourIds::headerTextColour));
		//set colours for help Label
		//help.setColour(Label::backgroundColourId, Colours::darkblue);
        //help.setColour(Label::textColourId, Colour::fromString("70FFFFFF"));

		defaultTooltip = "Move your mouse over the interface element that you would like more info about.";
		helpPanelHeader.setText("Help", NotificationType());
		help.setText(defaultTooltip, NotificationType());
		help.setJustificationType(Justification::topLeft);
		

		addAndMakeVisible(&helpPanelHeader);
		addAndMakeVisible(&help);

		//From juce_TooltipWindow
		if (Desktop::getInstance().getMainMouseSource().canHover())
			startTimer (123);
	}

	~HelpPanel()
	{
		resizableEdgeComponent = nullptr;
		componentBoundsConstrainer = nullptr;
	}

	void resized()
	{

		Rectangle<int> r = this->getLocalBounds();

		if (resizableEdgeComponent != nullptr)
			resizableEdgeComponent->setBounds(0, 0,  r.getWidth(), 5);

		helpPanelHeader.setBounds(0, 5, r.getWidth(), 30);
		help.setBoundsInset(BorderSize<int> (35, 0, 0, 0));
	}

	/*void paint (Graphics& g)
	{
		g.fillAll (Colour((uint8) 49, (uint8) 124, (uint8) 205));
	}*/

	void show() { _isHidden = false; }
	void hide() { _isHidden = true; }
	bool isVisible() { return !_isHidden; }

	String getTipFor (Component* const c)
	{
		if (c != nullptr
			 && Process::isForegroundProcess()
			 && ! ModifierKeys::getCurrentModifiers().isAnyMouseButtonDown())
		{
			if (TooltipClient* const ttc = dynamic_cast <TooltipClient*> (c))
				if (! c->isCurrentlyBlockedByAnotherModalComponent())
					return ttc->getTooltip();
		}

		return String::empty;
	}

	void timerCallback()
	{
		Desktop& desktop = Desktop::getInstance();
		const MouseInputSource mouseSource (desktop.getMainMouseSource());

		Component* const newComp = mouseSource.isMouse() ? mouseSource.getComponentUnderMouse() : nullptr;
		const String newTip (getTipFor (newComp));
		const bool tipChanged = (newTip != lastTipUnderMouse || newComp != lastComponentUnderMouse);
		lastComponentUnderMouse = newComp;
		lastTipUnderMouse = newTip;

		if (newComp == nullptr || newTip.isEmpty())
		{
			help.setText(defaultTooltip, NotificationType());
		}
		else if (tipChanged)
		{
			help.setText(newTip, NotificationType());
		}

		if (newTip.isNotEmpty() && newTip != tipShowing)
			help.setText(newTip, NotificationType());
	}

private:
	ScopedPointer <ResizableEdgeComponent> resizableEdgeComponent;
	ScopedPointer <ComponentBoundsConstrainer> componentBoundsConstrainer;
	Label helpPanelHeader;
	Label help;
	bool _isHidden;
	String defaultTooltip;
	
    Component* lastComponentUnderMouse;
    String tipShowing, lastTipUnderMouse;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelpPanel)
};

class LeftPanelContainer : public Component, public DragAndDropContainer
{
public:

    LeftPanelContainer() : Component()
    {
        setBounds(0, 32, 260, 340);
        setName("LeftPanelContainer");
		//DBG("one");
		resizableEdgeComponent = nullptr;
		componentBoundsConstrainer = nullptr;
		componentBoundsConstrainer = new ComponentBoundsConstrainer();
		componentBoundsConstrainer->setMinimumSize(200, 150);
		addAndMakeVisible(resizableEdgeComponent = new ResizableEdgeComponent(this, componentBoundsConstrainer, ResizableEdgeComponent::rightEdge));

		tabbedComponent = nullptr;
		addAndMakeVisible(tabbedComponent = new TabbedComponent(TabbedButtonBar::TabsAtTop));
		//Add FileBrowser TAB
		fileBrowserTab = new FileBrowserTab();
		tabbedComponent->addTab("Project Explorer", Colours::transparentBlack, fileBrowserTab, false);

		helpPanel = nullptr;
		addAndMakeVisible(helpPanel = new HelpPanel());
		//getTopLevelComponent()->addMouseListener(helpPanel, true);


		//DBG("four");
        resized();
		//DBG("five");

    }

	~LeftPanelContainer()
    {
        DBG("~LeftPanelContainer()");
		resizableEdgeComponent = nullptr;
		componentBoundsConstrainer = nullptr;
		//DBG("deleting tabbedComponent");
		tabbedComponent = nullptr;
		//DBG("deleting fileBrowserTab");
		fileBrowserTab = nullptr;
		helpPanel = nullptr;

    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseUp(event);
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseDoubleClick(event);
    }

	void resized() {

		Rectangle<int> r = this->getLocalBounds();
		bool helpPanelVisible = false;

		if (helpPanel != nullptr) {
			if (helpPanel->isVisible()) {
				helpPanelVisible = true;
				helpPanel->setBounds(0, r.getHeight() - helpPanel->getHeight(), r.getWidth() - 5, helpPanel->getHeight());
				//DBG("HelpPanel Bounds:");
				//DBG(helpPanel->getBounds().toString());
			}
		}

		if (resizableEdgeComponent != nullptr)
			resizableEdgeComponent->setBounds(r.getWidth() - 5, 0,  5, r.getHeight());

		if (tabbedComponent != nullptr) {
			if (helpPanelVisible)
				tabbedComponent->setBoundsInset (BorderSize<int> (0, 0, helpPanel->getHeight(), 5));
			else
				tabbedComponent->setBoundsInset (BorderSize<int> (0, 0, 0, 5));
		}

    }

	void childBoundsChanged (Component *child)
	{
		if (child == helpPanel)
			resized();
	}

private:
	ScopedPointer <TabbedComponent> tabbedComponent;
	ScopedPointer <FileBrowserTab> fileBrowserTab;
	ScopedPointer <ResizableEdgeComponent> resizableEdgeComponent;
	ScopedPointer <ComponentBoundsConstrainer> componentBoundsConstrainer;
	ScopedPointer <HelpPanel> helpPanel;

};








