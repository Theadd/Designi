/*
  ==============================================================================

    RightPanelContainer.h
    Created: 15 Oct 2013 1:57:51pm
    Author:  admin

  ==============================================================================
*/

#ifndef __RIGHTPANELCONTAINER_H_E7390F97__
#define __RIGHTPANELCONTAINER_H_E7390F97__
#include "../../Globals.h"

class InnerPanel;
class MainLayout;
class ExtendedLookAndFeel;

class Panel :	public Component,
				public DragAndDropTarget
{
public:

	enum ColourIds
    {
        backgroundColourId     = 0x2900001 /**< The background colour to fill the panel with. */
    };

	Panel(const String& componentName = String::empty, DragAndDropContainer* _dragAndDropContainer = nullptr, int _id = 0);
	~Panel();
	void resized();
	void paint (Graphics& g);

	/** Add a component to this panel. */
	bool addInnerPanel (InnerPanel *componentToAdd);

	//drag&drop
	void mouseDrag (const MouseEvent &event);
	bool isInterestedInDragSource (const SourceDetails &dragSourceDetails);
	void itemDropped (const SourceDetails &dragSourceDetails);
	//void componentChildrenChanged (Component & component);
	void removeInnerPanelAt (int tabIndex);
	bool removeInnerPanel(InnerPanel *innerPanel);
	void showInnerPanel(InnerPanel *innerPanel);
	bool isInnerPanelVisible(InnerPanel* innerPanel);

	/** Sets panel ResizableEdgeOrientation and repaints it. **/
	void setResizableEdgeOrientation(Globals::Orientation resizableEdgeOrientation_);

	Globals::Orientation resizableEdgeOrientation;
	int id;
private:
	ScopedPointer <ResizableEdgeComponent> resizableEdgeComponent;
	ScopedPointer <ComponentBoundsConstrainer> componentBoundsConstrainer;
	
	DragAndDropContainer* dragAndDropContainer;

	Colour tempBackgroundColour;	//TODO: remove randomly painting panels

	class CustomTabbedComponent : public TabbedComponent
	{
	public:
		CustomTabbedComponent();
		CustomTabbedComponent(TabbedButtonBar::Orientation _orientation);
		void popupMenuClickOnTab (int tabIndex, const String &tabName);
		static void menuItemChosenCallback (int result, CustomTabbedComponent* component, int tabIndex);
		void menuItemChosenCallback (int result, InnerPanel* innerPanel);
	private:

	};

	ScopedPointer <CustomTabbedComponent> tabbedComponent;

};


class PanelContainer : public Component, public DragAndDropContainer, public ComponentListener
{
public:

	enum ColourIds
    {
        backgroundColourId     = 0x2901001 /**< The background colour to fill the panel container with. */
    };

    PanelContainer(Globals::Position positionThatWillBePlaced, DragAndDropContainer* _dragAndDropContainer = nullptr);

	~PanelContainer();

    void mouseUp (const MouseEvent& event);
    void mouseDrag (const MouseEvent& event);
    void mouseDoubleClick (const MouseEvent& event);

	void resized();
	void paint (Graphics& g);

	void childBoundsChanged (Component *child);

	void componentChildrenChanged (Component & component);

	bool addInnerPanel (InnerPanel *componentToAdd, bool asNewPanel = false);
	bool removeInnerPanel(InnerPanel *innerPanel);
	void showInnerPanel(InnerPanel *innerPanel);
	bool isInnerPanelVisible(InnerPanel* innerPanel);
	bool isEmpty();

	Globals::Position position;
	
private:
	ScopedPointer <ResizableEdgeComponent> resizableEdgeComponent;
	ScopedPointer <ComponentBoundsConstrainer> componentBoundsConstrainer;
	DragAndDropContainer* dragAndDropContainer;
	OwnedArray <Panel> panels;
};



#endif  // __RIGHTPANELCONTAINER_H_E7390F97__
