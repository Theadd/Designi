/*
  ==============================================================================

    MainLayout.cpp
    Created: 11 Oct 2013 9:21:11pm
    Author:  admin

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
//#include "../Styles/Default.h"

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
		DBG("Resized FileBrowserTabHeader");
		DBG(this->getBounds().toString());
		DBG(projectNameLabel.getBounds().toString());
	}

	void paint (Graphics& g)
	{
		g.fillAll (Colour((uint8) 49, (uint8) 124, (uint8) 205));
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
		DBG("two");

        directoryList = new DirectoryContentsList(projectFileFilter, thread);
        directoryList->setDirectory (folder, true, true);
        thread.startThread (3);
		DBG("three");
        fileTreeComp = nullptr;

        addAndMakeVisible (fileTreeComp = new FileTreeComponent (*directoryList));
		addAndMakeVisible (&fileBrowserTabHeader);
	}

	~FileBrowserTab() {
		fileTreeComp = nullptr;
        directoryList = nullptr; // (need to make sure this is deleted before the TimeSliceThread)
		projectFileFilter = nullptr;
	}

	void resized() {
		if (fileTreeComp != nullptr)
			fileTreeComp->setBoundsInset (BorderSize<int> (30, 5, 5, 5));

		fileBrowserTabHeader.setBounds(0, 0, this->getWidth(), 30);
		DBG("Resized FileBrowserTab");
	}


private:
	ScopedPointer <FileTreeComponent> fileTreeComp;
    ScopedPointer <DirectoryContentsList> directoryList;
	ScopedPointer <ProjectFileFilter> projectFileFilter;
    TimeSliceThread thread;
	FileBrowserTabHeader fileBrowserTabHeader;

};

class HelpPanel : public Component//, private Timer
{
public:
	
	HelpPanel()
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
		helpPanelHeader.setColour(Label::backgroundColourId, Colours::red);
        helpPanelHeader.setColour(Label::textColourId, Colour::fromString("70FFFFFF"));
		//set colours for help Label
		help.setColour(Label::backgroundColourId, Colours::darkblue);
        help.setColour(Label::textColourId, Colour::fromString("70FFFFFF"));

		helpPanelHeader.setText("Help", NotificationType());
		help.setText("Move your mouse over the interface element that you would like more info about.", NotificationType());
		help.setJustificationType(Justification::topLeft);
		

		addAndMakeVisible(&helpPanelHeader);
		addAndMakeVisible(&help);

		tooltipWindow = new TooltipWindow(&help, 0);

		
	}

	~HelpPanel()
	{
		resizableEdgeComponent = nullptr;
		componentBoundsConstrainer = nullptr;
		tooltipWindow = nullptr;
	}

	void resized()
	{

		Rectangle<int> r = this->getLocalBounds();

		if (resizableEdgeComponent != nullptr)
			resizableEdgeComponent->setBounds(0, 0,  r.getWidth(), 5);

		helpPanelHeader.setBounds(0, 5, r.getWidth(), 30);
		help.setBoundsInset(BorderSize<int> (35, 0, 0, 0));

		DBG("Resized HelpPanel");
	}

	void paint (Graphics& g)
	{
		g.fillAll (Colour((uint8) 49, (uint8) 124, (uint8) 205));
	}

	void show() { _isHidden = false; }
	void hide() { _isHidden = true; }
	bool isVisible() { return !_isHidden; }

	/*void mouseEnter (const MouseEvent &event)
	{
		String tooltip;
		TooltipWindow a;

		try {
			tooltip = (static_cast<SettableTooltipClient> (event.originalComponent))->getTooltip();
		} catch (...) {
			tooltip = "";
		}
		
		DBG("TOOLTIP!");
		DBG(tooltip);

		if (tooltip.isNotEmpty())
			help.setText(tooltip, NotificationType());
		else
			help.setText("Move your mouse over the interface element that you would like more info about.", NotificationType());

	}*/

private:
	ScopedPointer <ResizableEdgeComponent> resizableEdgeComponent;
	ScopedPointer <ComponentBoundsConstrainer> componentBoundsConstrainer;
	ScopedPointer <TooltipWindow> tooltipWindow;
	Label helpPanelHeader;
	Label help;
	bool _isHidden;
	
	//From juce_TooltipWindow

};

class LeftPanelContainer : public Component, public DragAndDropContainer
{
public:

    LeftPanelContainer() : Component()
    {
        setBounds(4, 23, 260, 340);
        setName("LeftPanelContainer");
		DBG("one");
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


		DBG("four");
        resized();
		DBG("five");

    }

	~LeftPanelContainer()
    {
        
		resizableEdgeComponent = nullptr;
		componentBoundsConstrainer = nullptr;
		DBG("deleting tabbedComponent");
		tabbedComponent = nullptr;
		DBG("deleting fileBrowserTab");
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
				DBG("HelpPanel Bounds:");
				DBG(helpPanel->getBounds().toString());
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


class MainLayout : public Component
{
public:

    MainLayout() : Component()
    {
		DBG("dbg: MainLayout()");
        setBounds(0, 0, 490, 414);
        setName("MainLayout");
        addAndMakeVisible(&leftpanelcontainer);

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

private:
    LeftPanelContainer leftpanelcontainer;
};






