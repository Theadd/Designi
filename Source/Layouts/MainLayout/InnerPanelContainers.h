/*
  ==============================================================================

    RightPanelContainer.h
    Created: 15 Oct 2013 1:57:51pm
    Author:  admin

  ==============================================================================
*/

#ifndef __RIGHTPANELCONTAINER_H_E7390F97__
#define __RIGHTPANELCONTAINER_H_E7390F97__

#include "InnerPanel.h"

class Panel :	public Component,
				public DragAndDropTarget
{
public:

	enum ResizableEdgeOrientation
	{
		none,	/*Do not draw it's ResizableEdgeComponent.*/
		vertical,
		horizontal
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

	/** Sets panel ResizableEdgeOrientation and repaints it. **/
	void setResizableEdgeOrientation(ResizableEdgeOrientation resizableEdgeOrientation_);

	ResizableEdgeOrientation resizableEdgeOrientation;
	int id;
private:
	ScopedPointer <ResizableEdgeComponent> resizableEdgeComponent;
	ScopedPointer <ComponentBoundsConstrainer> componentBoundsConstrainer;
	ScopedPointer <TabbedComponent> tabbedComponent;
	DragAndDropContainer* dragAndDropContainer;

	Colour tempBackgroundColour;	//TODO: remove randomly painting panels
};


class PanelContainer : public Component, public DragAndDropContainer, public ComponentListener
{
public:

	enum Position
    {
        top,
        right,
        bottom,
        left
    };

    PanelContainer(Position positionThatWillBePlaced, DragAndDropContainer* _dragAndDropContainer = nullptr);

	~PanelContainer();

    void mouseUp (const MouseEvent& event);
    void mouseDrag (const MouseEvent& event);
    void mouseDoubleClick (const MouseEvent& event);

	void resized();
	void paint (Graphics& g);

	void childBoundsChanged (Component *child);

	void componentChildrenChanged (Component & component);

	bool addInnerPanel (InnerPanel *componentToAdd, bool asNewPanel = false);

	Position position;
	
private:
	ScopedPointer <ResizableEdgeComponent> resizableEdgeComponent;
	ScopedPointer <ComponentBoundsConstrainer> componentBoundsConstrainer;
	DragAndDropContainer* dragAndDropContainer;
	OwnedArray <Panel> panels;
};



#endif  // __RIGHTPANELCONTAINER_H_E7390F97__
