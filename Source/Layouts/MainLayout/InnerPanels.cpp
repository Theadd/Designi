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
#include "../Extended/ExtendedFileTreeComponent.h"
#include "../../Application.h"
#include "../Extended/SourceCodeEditor.h"


/*
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

bool CodeEditorPanel::getNeedsToBeSaved ()
{
	if (codeDocument != nullptr)
		if (codeDocument->hasChangedSinceSavePoint ())
			return true;

	return InnerPanel::getNeedsToBeSaved();
}

bool CodeEditorPanel::save (File initialDirectory)
{
	DBG("bool CodeEditorPanel::save ()");
	if (codeDocument != nullptr)
	{
		if (loadedFile != nullptr && loadedFile->existsAsFile())
		{
			DBG("bool CodeEditorPanel::save () file exists");
			if (!loadedFile->hasWriteAccess())
				return false;	//file could not be written

			//write to disk
			loadedFile->replaceWithText(codeDocument->getAllContent());
		}
		else
		{
			DBG("bool CodeEditorPanel::save () save as dialog box");
			//Show save as dialog box!
			WildcardFileFilter wildcardFilter ("*.*", String::empty, "Save As Filters");
			FileBrowserComponent browser (FileBrowserComponent::saveMode | FileBrowserComponent::canSelectFiles,
			initialDirectory,
			&wildcardFilter,
			nullptr);
			FileChooserDialogBox dialogBox ("Save As...", "Specify description", browser, true, Colours::lightgrey);
			if (dialogBox.show())
			{
				File selectedFile = browser.getSelectedFile (0);
				DBG("bool CodeEditorPanel::save () selectedFile = "+selectedFile.getFullPathName());
				if (!selectedFile.existsAsFile())
					selectedFile.create();

				if (selectedFile.existsAsFile() && selectedFile.hasWriteAccess())
				{
					loadedFile = new File(selectedFile);
					filePath = loadedFile->getFullPathName();
					//write to disk
					loadedFile->replaceWithText(codeDocument->getAllContent());
				}
				else return false;	//selected file could  not be written
			}
			else return true;	//no file was selected so we return success but we don't setSavePoint
		}
		codeDocument->setSavePoint();
	}
	return true;
}
*/

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
	treeView->setRootItemVisible (false);
	treeView->setDefaultOpenness (true);
	treeView->setName ("Navigator");
	setTooltip ("Direct access to your design components and its modifiers.");
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

void NavigatorPanel::refresh()
{
    const String treeXmlString (JUCEDesignerApp::getApp().navigatorTree.toXmlString());
    XmlDocument parser (treeXmlString);
	treeXml = nullptr;
    treeXml = parser.getDocumentElement();
    jassert (treeXml != nullptr);
	treeView->setRootItem (nullptr);
	rootItem = nullptr;
    rootItem = new TreeViewItemParser (*treeXml);
    treeView->setRootItem (rootItem);

}

void NavigatorPanel::valueTreePropertyChanged (ValueTree&, const Identifier&)   { refresh(); }
void NavigatorPanel::valueTreeChildAdded (ValueTree&, ValueTree&)               { refresh(); }
void NavigatorPanel::valueTreeChildRemoved (ValueTree&, ValueTree&)             { refresh(); }
void NavigatorPanel::valueTreeChildOrderChanged (ValueTree&)                    { refresh(); }
void NavigatorPanel::valueTreeParentChanged (ValueTree&)                        { refresh(); }
void NavigatorPanel::valueTreeRedirected (ValueTree&)                           { refresh(); }

NavigatorPanel::TreeViewItemParser::TreeViewItemParser (XmlElement& xml_)
    : xml (xml_), icon (nullptr)
{
}

NavigatorPanel::TreeViewItemParser::~TreeViewItemParser ()
{
	icon = nullptr;
}

int NavigatorPanel::TreeViewItemParser::getItemWidth() const
{
    return -1;	//xml.getIntAttribute ("width", -1);
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
	float padding = 0.7f;	//space reduced from icon
    // if this item is selected, fill it with a background colour..
    if (isSelected())
        g.fillAll (Colours::blue.withAlpha (0.3f));

    // use a "colour" attribute in the xml tag for this node to set the text colour..
    //g.setColour (Colour::fromString (xml.getStringAttribute ("colour", "ffffffff")));

    //g.setFont (height * 0.6f);

    // draw the xml element's tag name..
	bool isClassDefinition = xml.getBoolAttribute("isClassDefinition", false);
	
	g.setColour ((isClassDefinition) ? Colours::lightgrey : Colours::white);

	int horizontalTextShift = 8 + (int) ((float) height * padding);
    g.drawText (xml.getStringAttribute ("name", "unknown"),
                horizontalTextShift, 0, width - horizontalTextShift, height,
                Justification::centredLeft, true);
	
	//draw icon
	if (icon == nullptr)
	{
		String iconName;
		if (xml.getTagName().compare("class") == 0)
		{
			iconName = "box-open.svg";
		}
		else if (xml.getTagName().compare("method") == 0)
		{
			iconName = "fire.svg";
		}
		else
		{
			iconName = "leaf.svg";
		}
		icon = getDrawableFromZipFile(iconName);
	}
	icon->drawWithin (g, Rectangle<float> (4.0f, padding, (float) height * padding, (float) height - (2.0f * padding)), RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
		
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

void NavigatorPanel::TreeViewItemParser::itemDoubleClicked (const MouseEvent &e)
{
	int numLine = xml.getIntAttribute("line", -1);
	if (numLine != -1)
	{
		SourceCodeEditor* editor = (SourceCodeEditor *) JUCEDesignerApp::getActiveInnerPanel();
		if (editor != nullptr)
		{
			editor->scrollToLine(numLine, false);
		}
	}
}

var NavigatorPanel::TreeViewItemParser::getDragSourceDescription()
{
    return "TreeView Items";
}


//////////////////////////////////////////////////////////////////////////


FileBrowserPanel::FileBrowserPanel() : thread ("FileTreeComponent thread"), InnerPanel()
{
	setLocalisedName("File Browser", "Your project directory tree");
	File folder (File::getSpecialLocation (File::userHomeDirectory));
    //while (folder.getParentDirectory() != folder)
    //    folder = folder.getParentDirectory();
	//projectFileFilter = new ProjectFileFilter();
	fileFilter = new WildcardFileFilter("*.cpp;*.h;*.design;*.png;*.svg;*.zip;*.gz;*.bz2", "*", "C++ JUCE Files");
	//DBG("two");

    directoryList = new DirectoryContentsList(fileFilter, thread);
    directoryList->setDirectory (folder, true, true);
    thread.startThread (3);
	//DBG("three");
    fileTreeCompA = nullptr;
	fileTreeCompB = nullptr;

    addAndMakeVisible (fileTreeCompA = new ExtendedFileTreeComponent (*directoryList));
	addAndMakeVisible (fileTreeCompB = new ExtendedFileTreeComponent (*directoryList));
	fileTreeCompB->setVisible(false);
	//Add listeners for double clicking files
	fileTreeCompA->addListener(this);
	fileTreeCompB->addListener(this);

	projectName = "Project Name";

	selectFileTreeA.setBounds(120, 5, 20, 20);
	selectFileTreeA.setName("selectFileTreeA");
	selectFileTreeA.setButtonText("A");
	selectFileTreeA.setConnectedEdges(Button::ConnectedOnRight);
	selectFileTreeA.setTooltip("File browser remembers two locations, A and B. Use these buttons to switch between them.");
	addAndMakeVisible(&selectFileTreeA);

	selectFileTreeB.setBounds(140, 5, 20, 20);
	selectFileTreeB.setName("selectFileTreeB");
	selectFileTreeB.setButtonText("B");
	selectFileTreeB.setConnectedEdges(Button::ConnectedOnLeft);
	selectFileTreeB.setTooltip("File browser remembers two locations, A and B. Use these buttons to switch between them.");
	addAndMakeVisible(&selectFileTreeB);

	//ADD this to the mouse listeners of "A" and "B" buttons.
	selectFileTreeA.addMouseListener(this, false);
	selectFileTreeB.addMouseListener(this, false);

}

FileBrowserPanel::~FileBrowserPanel()
{
	JUCEDesignerApp::getApp().setSettingsValue("lastProjectTreePath", directoryList->getDirectory().getFullPathName());
	stateA = fileTreeCompA->getOpennessState(true);
	stateB = fileTreeCompB->getOpennessState(true);
	JUCEDesignerApp::getApp().setSettingsValue("fileTreeCompAOpennessState", stateA->createDocument("", true, true, "UTF-8", 9999999));
	JUCEDesignerApp::getApp().setSettingsValue("fileTreeCompBOpennessState", stateB->createDocument("", true, true, "UTF-8", 9999999));

	fileTreeCompA = nullptr;
	fileTreeCompB = nullptr;
    directoryList = nullptr; // (need to make sure this is deleted before the TimeSliceThread)
	fileFilter = nullptr;
	delete stateA;
	delete stateB;
}

void FileBrowserPanel::resized() {
	if (fileTreeCompA != nullptr)
		fileTreeCompA->setBoundsInset (BorderSize<int> (31, 0, 0, 0));
	if (fileTreeCompB != nullptr)
		fileTreeCompB->setBoundsInset (BorderSize<int> (31, 0, 0, 0));

	selectFileTreeA.setBounds(getWidth() - 45, 5, 20, 20);
	selectFileTreeB.setBounds(getWidth() - 25, 5, 20, 20);
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

void FileBrowserPanel::setBrowserRoot (const File &file)
{
	directoryList->setDirectory (file, true, true);

	if (JUCEDesignerApp::getApp().getSettingsValue("lastProjectTreePath").equalsIgnoreCase(file.getFullPathName()))
	{
		stateA = (XmlDocument::parse (JUCEDesignerApp::getApp().getSettingsValue("fileTreeCompAOpennessState")));
		stateB = (XmlDocument::parse (JUCEDesignerApp::getApp().getSettingsValue("fileTreeCompBOpennessState")));

		refreshTimeCount = 10;
		startTimer(100);
	}
}

void FileBrowserPanel::setProjectName (const String &name)
{
	projectName = String(name);
	setHeader(true, projectName, 30, 5, 45, 0);
}

void FileBrowserPanel::refresh()
{
	if (directoryList != nullptr && fileTreeCompA != nullptr && fileTreeCompB != nullptr)
	{
		DBG("void FileBrowserPanel::refresh()");

		stateA = fileTreeCompA->getOpennessState(true);
		stateB = fileTreeCompB->getOpennessState(true);
		
		directoryList->refresh();

		refreshTimeCount = 10;
		startTimer(100);
	}
}

void FileBrowserPanel::timerCallback()
{
	if (stateA != 0)
		fileTreeCompA->restoreOpennessState(*stateA, true);

	if (stateB != 0)
		fileTreeCompB->restoreOpennessState(*stateB, true);

	--refreshTimeCount;
	
	if (refreshTimeCount <= 0)
	{
		delete stateA;
		delete stateB;
		stopTimer();
	}
}



//////////////////////

/*
FileBrowserPanel::ProjectFileFilter::ProjectFileFilter() : FileFilter("FileFilter for project directory trees.")
{

}

FileBrowserPanel::ProjectFileFilter::~ProjectFileFilter ()
{

}

bool FileBrowserPanel::ProjectFileFilter::isFileSuitable(const File &file) const
{
	return true;
	return (file.getFileExtension().equalsIgnoreCase(".cpp") || file.getFileExtension().equalsIgnoreCase(".h") || file.getFileExtension().equalsIgnoreCase(".design") || file.getFileExtension().equalsIgnoreCase(".txt"));
}

bool FileBrowserPanel::ProjectFileFilter::isDirectorySuitable (const File &file) const
{
	return file.isDirectory();
}
*/

///////////////////////////////////////////////////////////////


HelpPanel::HelpPanel() : lastComponentUnderMouse (nullptr), InnerPanel(true)
{
	setLocalisedName("Help");
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
