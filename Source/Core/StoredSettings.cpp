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
	options.applicationName     = "designi";
	options.filenameSuffix      = "settings";
	options.osxLibrarySubFolder = "Application Support";
	#if JUCE_LINUX
		options.folderName          = "~/.config/Designi";
	#else
		options.folderName          = "Designi";
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

PropertiesFile::Options StoredSettings::getPropertyFileOptionsFor (const String& filename)
{
    PropertiesFile::Options options;
    options.applicationName     = filename;
    options.filenameSuffix      = "settings";
    options.osxLibrarySubFolder = "Application Support";
    #if JUCE_LINUX
    options.folderName          = "~/.config/Designi";
    #else
    options.folderName          = "Designi";
    #endif

    return options;
}

PropertiesFile* StoredSettings::createPropsFile (const String& filename)
{
    return new PropertiesFile (getPropertyFileOptionsFor (filename));
}

PropertiesFile& StoredSettings::getProjectProperties (const String& projectUID)
{
    const String filename ("Introjucer_Project_" + projectUID);

    for (int i = propertyFiles.size(); --i >= 0;)
    {
        PropertiesFile* const props = propertyFiles.getUnchecked(i);
        if (props->getFile().getFileNameWithoutExtension() == filename)
            return *props;
    }

    PropertiesFile* p = createPropsFile (filename);
    propertyFiles.add (p);
    return *p;
}