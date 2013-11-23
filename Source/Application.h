/*
  ==============================================================================

    Application.h
    Created: 6 Nov 2013 9:44:57pm
    Author:  admin

  ==============================================================================
*/

#ifndef __APPLICATION_H_5F9C8BE0__
#define __APPLICATION_H_5F9C8BE0__


#include "Headers.h"
#include "Core/Project.h"
#include "UI/Windows/MainWindow.h"
#include "Core/StoredSettings.h"
#include "Core/DocumentManager.h"
#include "UI/Components/Basics/InnerPanel.h"
#include "UI/Workers/NavigatorTreeBuilder.h"
#include "UI/Windows/MainWindow/MainLayout.h"
#include "UI/Components/Panels/InnerPanels.h"


//==============================================================================
class JUCEDesignerApp  : public JUCEApplication
{
public:
    //==============================================================================
    JUCEDesignerApp() : navigatorTreeBuilder (), shouldBeComponentInspectorActive (var(false)), isRunningCommandLine (false) {}

    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed()       { return true; }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        // This method is where you should put your application's initialisation code..
		DBG("INIT commandLine: " + commandLine);
		
		settings = new StoredSettings();

		project = nullptr;

		//Open project
		if (commandLine.isNotEmpty())
		{
			File argFile(commandLine);
			if (argFile.existsAsFile())
				openProject(argFile);
		}
		else
		{
			String lastOpenProject = settings->getValue("lastOpenProject");
			if (lastOpenProject.isNotEmpty())
			{
				File lastProjectFile(lastOpenProject);
				openProject(lastProjectFile);
			}
		}
		//set gui language
		setLanguage(settings->getValue("guiLanguage"));
		/*if (guiLanguage.isNotEmpty())
		{
			if (guiLanguage.equalsIgnoreCase("spanish"))
			{
				LocalisedStrings::setCurrentMappings(new LocalisedStrings(File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "translations" + File::separatorString + "spanish.txt"), true));
			}
		}
		else
		{
			//Load English as default language
			LocalisedStrings::setCurrentMappings(0);
			//settings->setValue("guiLanguage", "");
		}*/

		//openProject(File("C:/Users/admin/JUCE Sample Project/JUCE Sample Project.jucer"));

        mainWindow = new MainWindow ();
		mainWindow->loadLayout ();
    }

    void shutdown()
    {
        // Add your application's shutdown code here..
		#if JUCE_MAC
         MenuBarModel::setMacMainMenu (nullptr);
		#endif

        mainWindow = nullptr; // (deletes our window)
        openDocumentManager.clear();
        //commandManager = nullptr;
        settings = nullptr;

        LookAndFeel::setDefaultLookAndFeel (nullptr);
        
		project = nullptr;
		
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
		DBG("INIT anotherInstanceStarted commandLine: " + commandLine);
    }

	static JUCEDesignerApp& getApp ()
    {
        JUCEDesignerApp* const app = dynamic_cast<JUCEDesignerApp*> (JUCEApplication::getInstance());
        jassert (app != nullptr);
        return *app;
    }

	Project* getProject()
	{
		return project;
	}

	void openProject (File& file)
	{
		project = new Project(file);
		if (project->getTitle().isEmpty())
			project = nullptr;
		else
			settings->setValue("lastOpenProject", file.getFullPathName());
	}

	virtual void updateNewlyOpenedProject (Project&) {}

	void setLanguage (String language)
	{
		if (language.isNotEmpty())
			LocalisedStrings::setCurrentMappings(new LocalisedStrings(File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "translations" + File::separatorString + language + ".txt"), true));
		else
			LocalisedStrings::setCurrentMappings(0);

		languageString = language;
		settings->setValue("guiLanguage", language);
	}

	String getLanguage ()
	{
		return languageString;
	}

	void setSettingsValue (const String &keyName, const var &value)
	{
		settings->setValue(keyName, value);
	}

	String getSettingsValue(StringRef keyName, String defaultReturnValue = String::empty)
	{
		return settings->getValue(keyName, defaultReturnValue); 
	}

	static ApplicationCommandManager& getCommandManager ()
    {
        ApplicationCommandManager* cm = JUCEDesignerApp::getApp().getApplicationCommandManager();
        jassert (cm != nullptr);
        return *cm;
    }

	ApplicationCommandManager* getApplicationCommandManager ()
    {
        if (mainWindow != nullptr)
			return &mainWindow->commandManager;
		else
			return nullptr;
    }

	static OpenDocumentManager::Document* getActiveDocument ()
	{
		return JUCEDesignerApp::getApp().activeDocument;
	}

	static void setActiveDocument (OpenDocumentManager::Document* document)
	{
		JUCEDesignerApp::getApp().activeDocument = document;
	}

	static InnerPanel* getActiveInnerPanel ()
	{
		return JUCEDesignerApp::getApp().activeInnerPanel;
	}

	static void setActiveInnerPanel (InnerPanel* innerPanel)
	{
		JUCEDesignerApp::getApp().activeInnerPanel = innerPanel;
		if (innerPanel->getNavigatorTree() != ValueTree::invalid)
		{
			JUCEDesignerApp::getApp().navigatorTree = ((DocumentEditorComponent *) innerPanel)->navigatorTree;
			JUCEDesignerApp::getApp().navigatorTreeBuilder.setDocumentEditorComponent((DocumentEditorComponent *) innerPanel);
			MainLayout* mainLayout = JUCEDesignerApp::getApp().mainLayout;
			if (mainLayout->navigatorPanel != nullptr && mainLayout->navigatorPanel->shouldBeVisible && !mainLayout->isInnerPanelVisible(mainLayout->navigatorPanel))
				mainLayout->toggleInnerPanel(mainLayout->navigatorPanel, mainLayout->navigatorPanel->position);
		}
		else
		{
			MainLayout* mainLayout = JUCEDesignerApp::getApp().mainLayout;
			if (mainLayout->navigatorPanel != nullptr && mainLayout->isInnerPanelVisible(mainLayout->navigatorPanel))
				mainLayout->toggleInnerPanel(mainLayout->navigatorPanel, mainLayout->navigatorPanel->position);
		}
	}

	void toggleComponentInspector ()
	{
		shouldBeComponentInspectorActive.setValue (var (! (bool) shouldBeComponentInspectorActive.getValue ()));
		mainLayout->floatingComponentOverlay->setVisible (isComponentInspectorActive());
	}

	bool isComponentInspectorActive ()
	{
		bool isActive = (bool) shouldBeComponentInspectorActive.getValue ();
		return isActive;
	}

	ScopedPointer <StoredSettings> settings;
	OpenDocumentManager openDocumentManager;
	OpenDocumentManager::Document* activeDocument;
	InnerPanel* activeInnerPanel;
	ValueTree navigatorTree;
	NavigatorTreeBuilder navigatorTreeBuilder;
	MainLayout* mainLayout;
	Value shouldBeComponentInspectorActive;
	bool isRunningCommandLine;

private:
	ScopedPointer <Project> project;
    ScopedPointer <MainWindow> mainWindow;
	String languageString;
};


#endif  // __APPLICATION_H_5F9C8BE0__
