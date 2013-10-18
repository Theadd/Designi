/*
  ==============================================================================

    InnerPanels.h
    Created: 18 Oct 2013 3:56:16pm
    Author:  admin

  ==============================================================================
*/

#ifndef __INNERPANELS_H_B9C0D563__
#define __INNERPANELS_H_B9C0D563__


class InnerPanel : public Component, public SettableTooltipClient
{
public:

	InnerPanel(bool showAsTab_ = true);

	bool showAsTab;
private:
	
};


class NavigatorPanel : public InnerPanel
{
public:

	NavigatorPanel ();
	~NavigatorPanel ();

	void resized ();

private:
	ScopedPointer <XmlElement> treeXml;
    ScopedPointer <TreeViewItem> rootItem;
    ScopedPointer <TreeView> treeView;

	class TreeViewItemParser  : public TreeViewItem
	{
	public:
		TreeViewItemParser (XmlElement& xml_);

		int getItemWidth() const;
		String getUniqueName() const;
		bool mightContainSubItems();
		void paintItem (Graphics& g, int width, int height);
		void itemOpennessChanged (bool isNowOpen);
		var getDragSourceDescription();

	private:
		XmlElement& xml;
	};

};


class FileBrowserTab : public InnerPanel
{
public:

	FileBrowserTab ();
	~FileBrowserTab ();

	void resized ();
	void mouseUp (const MouseEvent &event);

private:
	ScopedPointer <FileTreeComponent> fileTreeCompA;
	ScopedPointer <FileTreeComponent> fileTreeCompB;
    ScopedPointer <DirectoryContentsList> directoryList;
	
    TimeSliceThread thread;

	//FileBrowserTabHeader:
	Component fileBrowserTabHeader;	//container for header (projectNameLabel + A&B buttons)
	Label projectNameLabel;
    TextButton selectFileTreeA;
	TextButton selectFileTreeB;

	class ProjectFileFilter : public FileFilter
	{
	public:

		ProjectFileFilter ();
		~ProjectFileFilter ();

		bool isFileSuitable(const File &file) const;
		bool isDirectorySuitable (const File &file) const;
	};

	ScopedPointer <ProjectFileFilter> projectFileFilter;
};


class HelpPanel : public InnerPanel, private Timer
{
public:

	HelpPanel();

	~HelpPanel();

	void resized();

	void show();
	void hide();
	bool isVisible();

	String getTipFor (Component* const c);

	void timerCallback();

private:
	Label helpPanelHeader;
	Label help;
	bool _isHidden;
	String defaultTooltip;
	
    Component* lastComponentUnderMouse;
    String tipShowing, lastTipUnderMouse;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelpPanel)
};



#endif  // __INNERPANELS_H_B9C0D563__
