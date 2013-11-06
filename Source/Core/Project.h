/*
  ==============================================================================

    Project.h
    Created: 6 Nov 2013 7:50:02pm
    Author:  admin

  ==============================================================================
*/

#ifndef __PROJECT_H_DC19A8E0__
#define __PROJECT_H_DC19A8E0__

class Project : public FileBasedDocument
{
public:

	struct Information
	{
		String name;
		File path;
		String id;
		String type;
		String version;
	};

	Project(File& jucerFile);
	~Project();

	// FileBasedDocument stuff..
    String getDocumentTitle() override;
    Result loadDocument (const File& file) override;
    Result saveDocument (const File& file) override;
    //Result saveProject (const File& file, bool isCommandLineApp);
    //Result saveResourcesOnly (const File& file);
    File getLastDocumentOpened() override;
    void setLastDocumentOpened (const File& file) override;

	static Information getProjectInformation(const File& file);

	Information info;

private:
	
};


#endif  // __PROJECT_H_DC19A8E0__
