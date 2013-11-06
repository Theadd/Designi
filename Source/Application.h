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
		PropertiesFile::Options options;
		options.applicationName     = "JUCE Designer";
		options.filenameSuffix      = "settings";
		options.osxLibrarySubFolder = "Application Support";
		#if JUCE_LINUX
			options.folderName          = "~/.config/JUCE Designer";
		#else
			options.folderName          = "JUCE Designer";
		#endif

		propertiesFile = new PropertiesFile(options);
		if (!propertiesFile->getFile().existsAsFile())
		{
			propertiesFile->getFile().create();
		}
		DBG("PROPERTIES FILE: " + propertiesFile->getFile().getFullPathName());
		project = nullptr;

		//openProject(File("C:/Users/admin/JUCE Sample Project/JUCE Sample Project.jucer"));

        mainWindow = new MainWindow();
    }

    void shutdown()
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
		propertiesFile = nullptr;
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

	static JUCEDesignerApp& getApp()
    {
        JUCEDesignerApp* const app = dynamic_cast<JUCEDesignerApp*> (JUCEApplication::getInstance());
        jassert (app != nullptr);
        return *app;
    }

	Project* getProject()
	{
		return project;
	}

	void openProject(File& file)
	{
		project = new Project(file);
	}

private:
	ScopedPointer <Project> project;
    ScopedPointer <MainWindow> mainWindow;
	ScopedPointer <PropertiesFile> propertiesFile;
};


#endif  // __APPLICATION_H_5F9C8BE0__
