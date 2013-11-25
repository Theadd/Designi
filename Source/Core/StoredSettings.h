/*
  ==============================================================================

    StoredSettings.h
    Created: 6 Nov 2013 11:00:40pm
    Author:  admin

  ==============================================================================
*/

#ifndef __STOREDSETTINGS_H_479F710A__
#define __STOREDSETTINGS_H_479F710A__

#include "../Headers.h"

class StoredSettings
{
public:
	StoredSettings();
	~StoredSettings();

	String getValue(StringRef keyName, const String &defaultReturnValue=String::empty);
	void setValue (const String &keyName, const var &value);
	XmlElement* getXmlValue (StringRef keyName);
	void setValue (const String &keyName, const XmlElement *xml);

	static PropertiesFile::Options getPropertyFileOptionsFor (const String& filename);
	static PropertiesFile* createPropsFile (const String& filename);
	PropertiesFile& getProjectProperties (const String& projectUID);

private:
	ScopedPointer <PropertiesFile> propertiesFile;	//application properties file
	OwnedArray<PropertiesFile> propertyFiles;	//contains property files for opened projects
};


#endif  // __STOREDSETTINGS_H_479F710A__
