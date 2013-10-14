/*
  ==============================================================================

    MainWindow.cpp
    Created: 14 Oct 2013 8:32:04pm
    Author:  admin

  ==============================================================================
*/
#include "../../JuceLibraryCode/JuceHeader.h"

#include "MainWindow.h"


MainWindow::MainWindow()  : DocumentWindow ("JUCE GUI Designer",
                                        Colours::lightgrey,
                                        DocumentWindow::allButtons)
{
	//Look And Feel
    /*setLookAndFeel(lookAndFeel = new JUCEDesignerLookAndFeel());
	lookAndFeel->setColour(TextButton::buttonColourId, Colour(Colour((juce::uint8) 83, (juce::uint8) 94, (juce::uint8) 104, (juce::uint8) 255)));
	lookAndFeel->setColour(TextButton::textColourOffId, Colours::transparentWhite.withAlpha(0.9f));
	lookAndFeel->setColour(TextButton::textColourOnId, Colours::blue.withAlpha(0.9f));*/




    setBounds(55, 35, 490, 440);
    setColour(DocumentWindow::backgroundColourId, Colour::fromString("FF202A32"));
    setName("JUCE GUI Designer");
	DBG("dbg: MainWindow()");
    setTitleBarHeight(26);
    setTitleBarButtonsRequired(7, 0);
    setTitleBarTextCentred(0);
    setUsingNativeTitleBar(1);
    //setContentOwned (, true);

	mainLayout = new MainLayout(*this);

    commandManager.registerAllCommandsForTarget (mainLayout);
    commandManager.registerAllCommandsForTarget (JUCEApplication::getInstance());

    // this lets the command manager use keypresses that arrive in our window to send
    // out commands
    addKeyListener (commandManager.getKeyMappings());

    // sets the main content component for the window to be this tabbed
    // panel. This will be deleted when the window is deleted.
    setContentOwned (mainLayout, false);

    // this tells the DocumentWindow to automatically create and manage a MenuBarComponent
    // which uses our contentComp as its MenuBarModel
    setMenuBar (mainLayout);

    // tells our menu bar model that it should watch this command manager for
    // changes, and send change messages accordingly.
    mainLayout->setApplicationCommandManagerToWatch (&commandManager);

    setResizable(true, true);
    setVisible (true);
}

MainWindow::~MainWindow()
{
	// because we've set the content comp to be used as our menu bar model, we
	// have to switch this off before deleting the content comp..
	setMenuBar (nullptr);

	#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
	MenuBarModel::setMacMainMenu (nullptr);
	#endif

    // clearing the content component will delete the current one, and
    // that will in turn delete all its child components. You don't always
    // have to do this explicitly, because the base class's destructor will
    // also delete the content component, but in this case we need to
    // make sure our content comp has gone away before deleting our command
    // manager.
    //clearContentComponent();
	mainLayout = nullptr;
	DBG("END ~MainWindow()");
}

void MainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

void MainWindow::mouseUp (const MouseEvent& event)
{
    if (event.eventComponent == this)
        DocumentWindow::mouseUp(event);
}

void MainWindow::mouseDrag (const MouseEvent& event)
{
    if (event.eventComponent == this)
        DocumentWindow::mouseDrag(event);
}

void MainWindow::mouseDoubleClick (const MouseEvent& event)
{
    if (event.eventComponent == this)
        DocumentWindow::mouseDoubleClick(event);
}
