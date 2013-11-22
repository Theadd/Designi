/*
  ==============================================================================

    Project.cpp
    Created: 6 Nov 2013 7:50:02pm
    Author:  admin

  ==============================================================================
*/
#include "../Headers.h"
#include "Project.h"


Project::Project(File& jucerFile) : FileBasedDocument(".jucer", "*.jucer", "Open", "Save")
{
	loadDocument(jucerFile);

}

Project::~Project()
{
}

String Project::getDocumentTitle()
{
    return info.name;
}

Result Project::loadDocument (const File& file)
{
	//return Result::ok();
    ScopedPointer <XmlElement> xml (XmlDocument::parse (file));

    if (xml == nullptr || ! xml->hasTagName ("JUCERPROJECT"))
        return Result::fail ("Not a valid Jucer project!");

    ValueTree newTree (ValueTree::fromXml (*xml));

    if (! newTree.hasType ("JUCERPROJECT"))
        return Result::fail ("The document contains errors and couldn't be parsed!");

	info = getProjectInformation(file);

    setChangedFlag (false);

    return Result::ok();
}

Result Project::saveDocument (const File& /*file*/)
{
	return Result::ok();
    //return saveProject (file, false);
}

/*Result Project::saveProject (const File& file, bool isCommandLineApp)
{
    updateProjectSettings();
    sanitiseConfigFlags();

    if (! isCommandLineApp)
        registerRecentFile (file);

    ProjectSaver saver (*this, file);
    return saver.save (! isCommandLineApp);
}

Result Project::saveResourcesOnly (const File& file)
{
    ProjectSaver saver (*this, file);
    return saver.saveResourcesOnly();
}*/

static File lastDocumentOpened;

File Project::getLastDocumentOpened()                   { return lastDocumentOpened; }
void Project::setLastDocumentOpened (const File& file)  { lastDocumentOpened = file; }


//void Project::loadProjectInformation()
Project::Information Project::getProjectInformation(const File& file)
{
	Project::Information info;
	ScopedPointer <XmlElement> xml (XmlDocument::parse (file));

	if (xml == nullptr || ! xml->hasTagName ("JUCERPROJECT"))
        return info;

    ValueTree newTree (ValueTree::fromXml (*xml));

    if (! newTree.hasType ("JUCERPROJECT"))
        return info;

	info.name = newTree.getProperty("name");
	info.id = newTree.getProperty("id");
	info.type = newTree.getProperty("projectType");
	info.version = newTree.getProperty("version");
	info.path = file.getParentDirectory();

	return info;
	//XmlElement *xml = XmlDocument::parse(file);//->getFirstChildElement();

	//projectName = xml->getStringAttribute("name");
	//DBG("[PROJECT] projectName: "+projectName);

	//while (xml != nullptr)
	/*forEachXmlChildElement (*xml, xmlnode)
	{
		_Enumerations *e = new _Enumerations;
		e->name = xmlnode->getStringAttribute("name");
		e->enumerations = new Array< Enumeration* >;

		//XmlElement *child = xmlnode->getFirstChildElement();

		//(while (child != nullptr)
		forEachXmlChildElement (*xmlnode, child)
		{
			Enumeration *t = new Enumeration;
			t->name = child->getStringAttribute("name");
			t->display = child->getStringAttribute("display");
			t->value = child->getIntAttribute("value");
			e->enumerations->add(t);
			//child = child->getNextElement();
		}
		_enumerations.add(*e);
		//child = nullptr;
		//xml = xml->getNextElement();
	}*/

	//delete xml;
}