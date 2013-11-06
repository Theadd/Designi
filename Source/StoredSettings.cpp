/*
  ==============================================================================

    StoredSettings.cpp
    Created: 6 Nov 2013 11:00:40pm
    Author:  admin

  ==============================================================================
*/

#include "StoredSettings.h"


StoredSettings::StoredSettings()
{
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
}

StoredSettings::~StoredSettings()
{
	propertiesFile = nullptr;
}

String StoredSettings::getValue(StringRef keyName, const String &defaultReturnValue)
{
	return propertiesFile->getValue(keyName, defaultReturnValue); 
}

void StoredSettings::setValue (const String &keyName, const var &value)
{
	propertiesFile->setValue(keyName, value);
	propertiesFile->save();
}