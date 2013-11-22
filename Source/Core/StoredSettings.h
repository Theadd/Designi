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

private:
	ScopedPointer <PropertiesFile> propertiesFile;
};


#endif  // __STOREDSETTINGS_H_479F710A__
