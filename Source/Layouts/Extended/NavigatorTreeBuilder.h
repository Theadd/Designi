/*
  ==============================================================================

    NavigatorTreeBuilder.h
    Created: 15 Nov 2013 3:10:48pm
    Author:  admin

  ==============================================================================
*/

#ifndef __NAVIGATORTREEBUILDER_H_4C4EFD86__
#define __NAVIGATORTREEBUILDER_H_4C4EFD86__

#include "DocumentEditorComponent.h"

class NavigatorTreeBuilder : private TimeSliceClient
{
public:
	NavigatorTreeBuilder ();
	~NavigatorTreeBuilder ();

	void setDocumentEditorComponent (DocumentEditorComponent* editor);
	int useTimeSlice ();

	ValueTree getNavigatorTree (String& code);
	void stripUnsafeCode (String& code);
	bool isValidSource (String& code);
	int getLineNumber(String& code, int startPosition, int currentPosition);
	void updateNavigatorTree (ValueTree& parentTree, String& code, int lineNumber = 0, bool isInsideClass = false);
	int getPosOfMatchingBracket(const String& code, const int startPosition, juce_wchar openBracket, juce_wchar closeBracket);
	ValueTree getValueTreeFor(String& classOrMethodRawString, bool isInsideClass = false, bool isClassDefinition = false, int lineNumber = 0);

	TimeSliceThread thread;
	DocumentEditorComponent* editor;
	ValueTree navigatorTree;
};



#endif  // __NAVIGATORTREEBUILDER_H_4C4EFD86__
