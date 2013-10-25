/*
  ==============================================================================

    InnerPanels.cpp
    Created: 18 Oct 2013 3:56:16pm
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../Globals.h"

#include "InnerPanels.h"
#include "MainLayout.h"



CodeEditorPanel::CodeEditorPanel (String& filename, File* file)
{
	setName(filename);
	loadedFile = nullptr;
	filePath = String::empty;
	codeTokeniser = new CPlusPlusCodeTokeniser();
	codeDocument = new CodeDocument();
	codeEditorComponent = new CodeEditorComponent(*codeDocument, codeTokeniser);
	addAndMakeVisible(codeEditorComponent);
	if (file != nullptr)
	{
		loadedFile = new File(*file);
		filePath = loadedFile->getFullPathName();
		loadContent(loadedFile->loadFileAsString());
	}
	resized();
}

CodeEditorPanel::~CodeEditorPanel ()
{
	codeEditorComponent = nullptr;
	codeTokeniser = nullptr;
	codeDocument = nullptr;
	loadedFile = nullptr;
}

void CodeEditorPanel::resized ()
{
	codeEditorComponent->setBoundsInset (BorderSize<int> (0, 0, 0, 0));
}

void CodeEditorPanel::loadContent (const String &newContent)
{
	codeEditorComponent->loadContent(newContent);
}


////////////////////////////////////////////////////////////////////////////


NavigatorPanel::NavigatorPanel () : InnerPanel()
{
	setName("Navigator");
	{
        const String treeXmlString (BinaryData::treedemo_xml);
        XmlDocument parser (treeXmlString);
        treeXml = parser.getDocumentElement();
        jassert (treeXml != nullptr);
    }

    rootItem = new TreeViewItemParser (*treeXml);
    rootItem->setOpen (true);

	treeView = nullptr;

    addAndMakeVisible (treeView = new TreeView());
    treeView->setRootItem (rootItem);
    treeView->setMultiSelectEnabled (true);
	treeView->setName("Navigator");
	setTooltip("Direct access to your design components and its modifiers.");
}

NavigatorPanel::~NavigatorPanel ()
{
	treeView = nullptr;
	rootItem = nullptr;
	treeXml = nullptr;
}

void NavigatorPanel::resized ()
{
	if (treeView != nullptr)
		treeView->setBoundsInset(BorderSize<int> (0, 0, 0, 0));
}

NavigatorPanel::TreeViewItemParser::TreeViewItemParser (XmlElement& xml_)
    : xml (xml_)
{
}

int NavigatorPanel::TreeViewItemParser::getItemWidth() const
{
    return xml.getIntAttribute ("width", -1);
}

String NavigatorPanel::TreeViewItemParser::getUniqueName() const
{
    return xml.getTagName();
}

bool NavigatorPanel::TreeViewItemParser::mightContainSubItems()
{
    return xml.getFirstChildElement() != 0;
}

void NavigatorPanel::TreeViewItemParser::paintItem (Graphics& g, int width, int height)
{
    // if this item is selected, fill it with a background colour..
    if (isSelected())
        g.fillAll (Colours::blue.withAlpha (0.3f));

    // use a "colour" attribute in the xml tag for this node to set the text colour..
    g.setColour (Colour::fromString (xml.getStringAttribute ("colour", "ff000000")));

    g.setFont (height * 0.7f);

    // draw the xml element's tag name..
    g.drawText (xml.getTagName(),
                4, 0, width - 4, height,
                Justification::centredLeft, true);
}

void NavigatorPanel::TreeViewItemParser::itemOpennessChanged (bool isNowOpen)
{
    if (isNowOpen)
    {
        // if we've not already done so, we'll now add the tree's sub-items. You could
        // also choose to delete the existing ones and refresh them if that's more suitable
        // in your app.
        if (getNumSubItems() == 0)
        {
            // create and add sub-items to this node of the tree, corresponding to
            // each sub-element in the XML..

            forEachXmlChildElement (xml, child)
            {
                jassert (child != 0);
                addSubItem (new TreeViewItemParser (*child));
            }
        }
    }
    else
    {
        // in this case, we'll leave any sub-items in the tree when the node gets closed,
        // though you could choose to delete them if that's more appropriate for
        // your application.
    }
}

var NavigatorPanel::TreeViewItemParser::getDragSourceDescription()
{
    return "TreeView Items";
}


//////////////////////////////////////////////////////////////////////////


FileBrowserPanel::FileBrowserPanel() : thread ("FileTreeComponent thread"), InnerPanel()
{
	setName("File Browser");
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
	//Add listeners for double clicking files
	fileTreeCompA->addListener(this);
	fileTreeCompB->addListener(this);
	addAndMakeVisible (&fileBrowserPanelHeader);

	//From FileBrowserPanelHeader
	fileBrowserPanelHeader.setBounds(0, 0, 170, 25);
	fileBrowserPanelHeader.setName("FileBrowserPanelHeader");

	projectNameLabel.setBounds(5, 5, 115, 15);
	projectNameLabel.setText("Project Name", NotificationType());
	//projectNameLabel.setColour(Label::backgroundColourId, Colours::transparentBlack);
	projectNameLabel.setColour(Label::textColourId, Colour::fromString("70FFFFFF"));
	fileBrowserPanelHeader.addAndMakeVisible(&projectNameLabel);

	selectFileTreeA.setBounds(120, 5, 20, 20);
	selectFileTreeA.setName("selectFileTreeA");
	selectFileTreeA.setButtonText("A");
	selectFileTreeA.setConnectedEdges(Button::ConnectedOnRight);
	selectFileTreeA.setTooltip("File browser remembers two locations, A and B. Use these buttons to switch between them.");
	fileBrowserPanelHeader.addAndMakeVisible(&selectFileTreeA);

	selectFileTreeB.setBounds(140, 5, 20, 20);
	selectFileTreeB.setName("selectFileTreeB");
	selectFileTreeB.setButtonText("B");
	selectFileTreeB.setConnectedEdges(Button::ConnectedOnLeft);
	selectFileTreeB.setTooltip("File browser remembers two locations, A and B. Use these buttons to switch between them.");
	fileBrowserPanelHeader.addAndMakeVisible(&selectFileTreeB);

	//ADD this to the mouse listeners of "A" and "B" buttons.
	selectFileTreeA.addMouseListener(this, false);
	selectFileTreeB.addMouseListener(this, false);

}

FileBrowserPanel::~FileBrowserPanel() {
	fileTreeCompA = nullptr;
	fileTreeCompB = nullptr;
    directoryList = nullptr; // (need to make sure this is deleted before the TimeSliceThread)
	projectFileFilter = nullptr;
}

void FileBrowserPanel::resized() {
	if (fileTreeCompA != nullptr)
		fileTreeCompA->setBoundsInset (BorderSize<int> (30, 5, 5, 5));
	if (fileTreeCompB != nullptr)
		fileTreeCompB->setBoundsInset (BorderSize<int> (30, 5, 5, 5));

	fileBrowserPanelHeader.setBounds(0, 0, this->getWidth(), 30);
	projectNameLabel.setBoundsInset (BorderSize<int> (5, 5, 5, 50));
	selectFileTreeA.setBounds(projectNameLabel.getWidth() + 10, 5, 20, 20);
	selectFileTreeB.setBounds(projectNameLabel.getWidth() + 30, 5, 20, 20);
	//DBG("Resized FileBrowserPanel");
}

void FileBrowserPanel::mouseUp (const MouseEvent &event)
{
	if (event.mouseWasClicked()) {
		if (event.eventComponent == &selectFileTreeA) {
			fileTreeCompA->setVisible(true);
			fileTreeCompB->setVisible(false);
		} else if (event.eventComponent == &selectFileTreeB) {
			fileTreeCompA->setVisible(false);
			fileTreeCompB->setVisible(true);
		}
	}
}

void FileBrowserPanel::fileDoubleClicked (const File &file)
{
	if (file.isDirectory())
		return;

	MainLayout* mainLayout = findParentComponentOfClass <MainLayout>();
	File fileToOpen(file);
	mainLayout->loadDocument(fileToOpen);
}

FileBrowserPanel::ProjectFileFilter::ProjectFileFilter() : FileFilter("FileFilter for project directory trees.")
{

}

FileBrowserPanel::ProjectFileFilter::~ProjectFileFilter ()
{

}

bool FileBrowserPanel::ProjectFileFilter::isFileSuitable(const File &file) const
{
	return (file.getFileExtension().equalsIgnoreCase(".cpp") || file.getFileExtension().equalsIgnoreCase(".h"));
}

bool FileBrowserPanel::ProjectFileFilter::isDirectorySuitable (const File &file) const
{
	return file.isDirectory();
}


///////////////////////////////////////////////////////////////


HelpPanel::HelpPanel() : lastComponentUnderMouse (nullptr), InnerPanel(true)
{
	setName("Help");
	setBounds(0, 0, 150, 90);
	_isHidden = false;

	defaultTooltip = "Move your mouse over the interface element that you would like more info about.";
	help.setText(defaultTooltip, NotificationType());
	help.setJustificationType(Justification::topLeft);
	
	addAndMakeVisible(&help);

	//From juce_TooltipWindow
	if (Desktop::getInstance().getMainMouseSource().canHover())
		startTimer (123);
}

HelpPanel::~HelpPanel()
{
	
}

void HelpPanel::resized()
{
	help.setBoundsInset(BorderSize<int> (0, 0, 0, 0));
}

void HelpPanel::show() { _isHidden = false; }
void HelpPanel::hide() { _isHidden = true; }
bool HelpPanel::isVisible() { return !_isHidden; }

String HelpPanel::getTipFor (Component* const c)
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

void HelpPanel::timerCallback()
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
