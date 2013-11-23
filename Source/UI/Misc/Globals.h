/*
  ==============================================================================

    Globals.h
    Created: 13 Oct 2013 2:59:53am
    Author:  admin

  ==============================================================================
*/

#ifndef __GLOBALS_H_D2823AC0__
#define __GLOBALS_H_D2823AC0__



#define RESIZABLEEDGESIZE 5
#define TOOLBARSIZE 32
#define MINIMUMPANELSIZE 90
#define MENUBARHEIGHT 24

const char* const projectItemDragType   = "Project Items";
const char* const drawableItemDragType  = "Drawable Items";
const char* const componentItemDragType = "Components";

namespace Globals
{
    enum Position
	{
		top,
		right,
		bottom,
		left,
		center
	};

	enum Orientation
	{
		none,
		vertical,
		horizontal
	};
}

enum ColourIds
{
    mainBackgroundColourId          = 0x2340000,
    treeviewHighlightColourId       = 0x2340002,
};

namespace Ids
{
    #define DECLARE_ID(name)      const Identifier name (#name)

    DECLARE_ID (name);
    DECLARE_ID (file);
    DECLARE_ID (path);
    DECLARE_ID (text);
    DECLARE_ID (version);
    DECLARE_ID (license);
    DECLARE_ID (include);
    DECLARE_ID (info);
    DECLARE_ID (description);
    DECLARE_ID (companyName);
    DECLARE_ID (position);
    DECLARE_ID (source);
    DECLARE_ID (width);
    DECLARE_ID (height);
    DECLARE_ID (background);
    DECLARE_ID (initialState);
    DECLARE_ID (targetFolder);
    DECLARE_ID (intermediatesPath);
    DECLARE_ID (vstFolder);
    DECLARE_ID (vst3Folder);
    DECLARE_ID (rtasFolder);
    DECLARE_ID (auFolder);
    DECLARE_ID (flags);
    DECLARE_ID (line);
    DECLARE_ID (index);
    DECLARE_ID (type);
    DECLARE_ID (time);
    DECLARE_ID (extraCompilerFlags);
    DECLARE_ID (extraLinkerFlags);
    DECLARE_ID (externalLibraries);
    DECLARE_ID (extraDefs);
    DECLARE_ID (projectType);
    DECLARE_ID (isDebug);
    DECLARE_ID (alwaysGenerateDebugSymbols);
    DECLARE_ID (targetName);
    DECLARE_ID (binaryPath);
    DECLARE_ID (optimisation);
    DECLARE_ID (defines);
    DECLARE_ID (headerPath);
    DECLARE_ID (systemHeaderPath);
    DECLARE_ID (libraryPath);
    DECLARE_ID (customXcodeFlags);
    DECLARE_ID (cppLibType);
    DECLARE_ID (osxSDK);
    DECLARE_ID (osxCompatibility);
    DECLARE_ID (osxArchitecture);
    DECLARE_ID (iosCompatibility);
    DECLARE_ID (extraFrameworks);
    DECLARE_ID (extraDLLs);
    DECLARE_ID (winArchitecture);
    DECLARE_ID (winWarningLevel);
    DECLARE_ID (linuxArchitecture);
    DECLARE_ID (toolset);
    DECLARE_ID (msvcModuleDefinitionFile);
    DECLARE_ID (bigIcon);
    DECLARE_ID (smallIcon);
    DECLARE_ID (jucerVersion);
    DECLARE_ID (prebuildCommand);
    DECLARE_ID (postbuildCommand);
    DECLARE_ID (generateManifest);
    DECLARE_ID (useRuntimeLibDLL);
    DECLARE_ID (wholeProgramOptimisation);
    DECLARE_ID (juceLinkage);
    DECLARE_ID (buildVST);
    DECLARE_ID (bundleIdentifier);
    DECLARE_ID (aaxIdentifier);
    DECLARE_ID (aaxCategory);
    DECLARE_ID (aaxFolder);
    DECLARE_ID (compile);
    DECLARE_ID (noWarnings);
    DECLARE_ID (resource);
    DECLARE_ID (className);
    DECLARE_ID (classDesc);
    DECLARE_ID (controlPoint);
    DECLARE_ID (createCallback);
    DECLARE_ID (parentClasses);
    DECLARE_ID (constructorParams);
    DECLARE_ID (objectConstructionArgs);
    DECLARE_ID (memberInitialisers);
    DECLARE_ID (canBeAggregated);
    DECLARE_ID (rootItemVisible);
    DECLARE_ID (openByDefault);
    DECLARE_ID (locked);
    DECLARE_ID (tooltip);
    DECLARE_ID (memberName);
    DECLARE_ID (markerName);
    DECLARE_ID (focusOrder);
    DECLARE_ID (hidden);
    DECLARE_ID (useStdCall);
    DECLARE_ID (showAllCode);
    DECLARE_ID (useLocalCopy);
    DECLARE_ID (androidActivityClass);
    DECLARE_ID (androidSDKPath);
    DECLARE_ID (androidNDKPath);
    DECLARE_ID (androidInternetNeeded);
    DECLARE_ID (androidArchitectures);
    DECLARE_ID (androidCpp11);
    DECLARE_ID (androidMicNeeded);
    DECLARE_ID (androidMinimumSDK);
    DECLARE_ID (androidOtherPermissions);
    DECLARE_ID (androidKeyStore);
    DECLARE_ID (androidKeyStorePass);
    DECLARE_ID (androidKeyAlias);
    DECLARE_ID (androidKeyAliasPass);
    DECLARE_ID (font);
    DECLARE_ID (colour);
    DECLARE_ID (userNotes);
    DECLARE_ID (maxBinaryFileSize);
    DECLARE_ID (includeBinaryInAppConfig);
    DECLARE_ID (characterSet);
    DECLARE_ID (JUCERPROJECT);
    DECLARE_ID (MAINGROUP);
    DECLARE_ID (EXPORTFORMATS);
    DECLARE_ID (GROUP);
    DECLARE_ID (FILE);
    DECLARE_ID (MODULES);
    DECLARE_ID (MODULE);
    DECLARE_ID (JUCEOPTIONS);
    DECLARE_ID (CONFIGURATIONS);
    DECLARE_ID (CONFIGURATION);
    DECLARE_ID (MODULEPATHS);
    DECLARE_ID (MODULEPATH);

    const Identifier ID ("id");
    const Identifier class_ ("class");

    #undef DECLARE_ID
}

//String createAlphaNumericUID();
//void setValueIfVoid (Value value, const var& defaultValue);

String T (const String& text);
String T (const char* text);
String T (CharPointer_UTF8 text);




/*WIP ~= RIP
class Literal
{
public:

	struct Reference
	{
		Value value;	//its localised value (translated)
		String text;	//string keyword to translate from
	};

	OwnedArray<Reference> references;

	Value& getValueFor (String& text);

};*/


/*
const char* T_UTF8 (const String& text);
const char* T_UTF8 (const char* text);

const char* T_UTF8 (CharPointer_UTF8 text);
*/





/*
namespace LayoutColourIds
{
	const Identifier headerBackgroundColour		("headerBackgroundColour");
	const Identifier headerTextColour	("headerTextColour");
}

namespace Layout
{
	inline Colour getColourFor (Identifier c)
	{
		if (c == LayoutColourIds::headerBackgroundColour)
			return Colour(Colour((juce::uint8) 83, (juce::uint8) 94, (juce::uint8) 104, (juce::uint8) 255));

		else if (c == LayoutColourIds::headerBackgroundColour)
			return Colour(Colour((juce::uint8) 83, (juce::uint8) 94, (juce::uint8) 104, (juce::uint8) 255));

		else
			return Colours::transparentBlack;
	}
}
*/

#endif  // __GLOBALS_H_D2823AC0__
