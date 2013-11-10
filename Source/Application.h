/*
  ==============================================================================

    Application.h
    Created: 6 Nov 2013 9:44:57pm
    Author:  admin

  ==============================================================================
*/

#ifndef __APPLICATION_H_5F9C8BE0__
#define __APPLICATION_H_5F9C8BE0__


#include "../JuceLibraryCode/JuceHeader.h"
#include "Core/Project.h"
#include "Layouts/MainWindow.h"
#include "StoredSettings.h"
#include "Core/DocumentManager.h"


//==============================================================================
class JUCEDesignerApp  : public JUCEApplication
{
public:
    //==============================================================================
    JUCEDesignerApp() {}

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

        mainWindow = new MainWindow();
    }

    void shutdown()
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
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
		if (project->info.name.isEmpty())
			project = nullptr;
		else
			settings->setValue("lastOpenProject", file.getFullPathName());
	}

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

	static ApplicationCommandManager& getCommandManager()
    {
        ApplicationCommandManager* cm = JUCEDesignerApp::getApp().getApplicationCommandManager();
        jassert (cm != nullptr);
        return *cm;
    }

	ApplicationCommandManager* getApplicationCommandManager()
    {
        if (mainWindow != nullptr)
			return &mainWindow->commandManager;
		else
			return nullptr;
    }

	ScopedPointer <StoredSettings> settings;
	OpenDocumentManager openDocumentManager;

private:
	ScopedPointer <Project> project;
    ScopedPointer <MainWindow> mainWindow;
	String languageString;
};


#endif  // __APPLICATION_H_5F9C8BE0__
