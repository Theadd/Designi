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

	Panel(const String& componentName = String::empty, DragAndDropContainer* _dragAndDropContainer = nullptr);
	~Panel();
	void resized();
	void paint (Graphics& g);

	/** Add a component to this panel. */
	bool addInnerPanel (InnerPanel *componentToAdd);

	//drag&drop
	void mouseDrag (const MouseEvent &event);
	bool isInterestedInDragSource (const SourceDetails &dragSourceDetails);
	void itemDropped (const SourceDetails &dragSourceDetails);

	/** Sets panel ResizableEdgeOrientation and repaints it. **/
	void setResizableEdgeOrientation(ResizableEdgeOrientation resizableEdgeOrientation_);

	ResizableEdgeOrientation resizableEdgeOrientation;
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

    PanelContainer(Position positionThatWillBePlaced);

	~PanelContainer();

    void mouseUp (const MouseEvent& event);
    void mouseDrag (const MouseEvent& event);
    void mouseDoubleClick (const MouseEvent& event);

	void resized();
	void paint (Graphics& g);

	void childBoundsChanged (Component *child);

	void componentChildrenChanged (Component & component);

	Position position;
	
private:
	ScopedPointer <ResizableEdgeComponent> resizableEdgeComponent;
	ScopedPointer <ComponentBoundsConstrainer> componentBoundsConstrainer;
};



#endif  // __RIGHTPANELCONTAINER_H_E7390F97__
