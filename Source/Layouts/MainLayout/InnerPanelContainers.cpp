/*
  ==============================================================================

    RightPanelContainer.cpp
    Created: 15 Oct 2013 1:57:51pm
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../Globals.h"
#include "InnerPanelContainers.h"



//////////////////////////////////////////////////////////////////////


Panel::Panel(const String& name) : Component (name)
{
	resizableEdgeComponent = nullptr;
	componentBoundsConstrainer = nullptr;
	componentBoundsConstrainer = new ComponentBoundsConstrainer();
	componentBoundsConstrainer->setMinimumSize(50, 60);
	//componentBoundsConstrainer->setMaximumHeight(200);
	addAndMakeVisible(resizableEdgeComponent = new ResizableEdgeComponent(this, componentBoundsConstrainer, ResizableEdgeComponent::topEdge));
	tabbedComponent = nullptr;

	tempBackgroundColour = Colour((uint8) Random::getSystemRandom().nextInt(255), (uint8) Random::getSystemRandom().nextInt(255), (uint8) Random::getSystemRandom().nextInt(255));

}

Panel::~Panel()
{
	resizableEdgeComponent = nullptr;
	componentBoundsConstrainer = nullptr;
	tabbedComponent = nullptr;
}

void Panel::resized()
{
	Rectangle<int> r = this->getLocalBounds();

	if (resizableEdgeComponent != nullptr)
	{
		if (resizableEdgeOrientation == vertical)
			resizableEdgeComponent->setBounds(0, 0, r.getWidth(), RESIZABLEEDGESIZE);

		if (resizableEdgeOrientation == horizontal)
			resizableEdgeComponent->setBounds(0, 0, RESIZABLEEDGESIZE, r.getHeight());

		if (resizableEdgeOrientation == none)
			resizableEdgeComponent->setBounds(0, 0, 0, 0);
	}

	//TODO: set bounds of child component
	int numChilds = getNumChildComponents() - 1;
	
	if (numChilds > 0) {
		//This panel is not empty, proceed to resize its content
		Component *componentToBeResized;

		if (tabbedComponent == nullptr)
		{
			//there is only one component inside without a tabbedComponent
			componentToBeResized = getChildComponent(1);	//TODO: find correct child component in case we get the resizable edge component
		}
		else
		{
			componentToBeResized = tabbedComponent;
		}

		if (componentToBeResized != nullptr)
		{
			if (resizableEdgeOrientation == vertical)
				componentToBeResized->setBounds(0, RESIZABLEEDGESIZE, r.getWidth(), r.getHeight() - RESIZABLEEDGESIZE);

			if (resizableEdgeOrientation == horizontal)
				componentToBeResized->setBounds(RESIZABLEEDGESIZE, 0, r.getWidth() - RESIZABLEEDGESIZE, r.getHeight());

			if (resizableEdgeOrientation == none)
				componentToBeResized->setBounds(0, 0, r.getWidth(), r.getHeight());
		}
	}
}

void Panel::paint (Graphics& g)
{
	g.fillAll (tempBackgroundColour);
}

bool Panel::addContent (Component *componentToAdd, bool asTab)
{
	int numChilds = getNumChildComponents() - 1;

	if (numChilds > 0) {
		//there was another component inside
		if (tabbedComponent == nullptr)
		{
			//BUT IT WAS NOT INSIDE A TABBED COMPONENT! FALLBACK!
			return false;
		}
		else
		{
			//add this component in another tab
			tabbedComponent->addTab(componentToAdd->getName(), Colours::transparentBlack, componentToAdd, false);
		}
	}
	else
	{
		if (asTab)
		{
			//This is the first component child of this panel
			if (tabbedComponent == nullptr)
			{
				//There is no tabbedComponent created, let's create it
				addAndMakeVisible(tabbedComponent = new TabbedComponent(TabbedButtonBar::TabsAtTop));
			}

			//add this component in a new tab
			tabbedComponent->addTab(componentToAdd->getName(), Colours::transparentBlack, componentToAdd, false);
		}
		else
		{
			//Add component without a tabbedComponent
			addAndMakeVisible(componentToAdd);
		}
	}

	resized();
	return true;
}

void Panel::setResizableEdgeOrientation(ResizableEdgeOrientation resizableEdgeOrientation_)
{
	resizableEdgeOrientation = resizableEdgeOrientation_;
	resized();
}

PanelContainer::PanelContainer(Position positionThatWillBePlaced) : Component(), position(positionThatWillBePlaced)
{
    setBounds(0, 32, 260, 340);
	//DBG("one");
	resizableEdgeComponent = nullptr;
	componentBoundsConstrainer = nullptr;
	componentBoundsConstrainer = new ComponentBoundsConstrainer();
	componentBoundsConstrainer->setMinimumSize(200, 150);
	ResizableEdgeComponent::Edge resizableEdge = ResizableEdgeComponent::leftEdge;
	switch (position)
	{
	case top:
		resizableEdge = ResizableEdgeComponent::bottomEdge;
		break;
	case right:
		resizableEdge = ResizableEdgeComponent::leftEdge;
		break;
	case bottom:
		resizableEdge = ResizableEdgeComponent::topEdge;
		break;
	case left:
		resizableEdge = ResizableEdgeComponent::rightEdge;
		break;
	}
	addAndMakeVisible(resizableEdgeComponent = new ResizableEdgeComponent(this, componentBoundsConstrainer, resizableEdge));
	resizableEdgeComponent->setName("Resizable Edge Component");
	addComponentListener(this);
    resized();
}

PanelContainer::~PanelContainer()
{
    DBG("~RightPanelContainer()");
	resizableEdgeComponent = nullptr;
	componentBoundsConstrainer = nullptr;
	//DBG("deleting tabbedComponent");
	//DBG("deleting fileBrowserTab");
	//fileBrowserTab = nullptr;
	//helpPanel = nullptr;

}

void PanelContainer::mouseUp (const MouseEvent& event)
{
    if (event.eventComponent == this)
        Component::mouseUp(event);
}

void PanelContainer::mouseDrag (const MouseEvent& event)
{
    if (event.eventComponent == this)
        Component::mouseDrag(event);
}

void PanelContainer::mouseDoubleClick (const MouseEvent& event)
{
    if (event.eventComponent == this)
        Component::mouseDoubleClick(event);
}

void PanelContainer::resized()
{
	Rectangle<int> r = this->getLocalBounds();

	if (resizableEdgeComponent != nullptr)
	{
		if (position==top)
			resizableEdgeComponent->setBounds(0, r.getHeight() - RESIZABLEEDGESIZE,  r.getWidth(), RESIZABLEEDGESIZE);

		if (position==right)
			resizableEdgeComponent->setBounds(0, 0,  RESIZABLEEDGESIZE, r.getHeight());

		if (position==bottom)
			resizableEdgeComponent->setBounds(0, 0,  r.getWidth(), RESIZABLEEDGESIZE);

		if (position==left)
			resizableEdgeComponent->setBounds(r.getWidth() - RESIZABLEEDGESIZE, 0,  RESIZABLEEDGESIZE, r.getHeight());
	}

	DBG("PanelContainer resize()");
	//int numChilds = getNumChildComponents() - 1;
	int lastSize = 0;
	//Get lastSize in pixels
	for (int i = 0; i < getNumChildComponents(); ++i)
	{
		Component *c = getChildComponent(i);
		if (c->getName().equalsIgnoreCase("Resizable Edge Component"))
			continue;

		DBG("--Size of Panel "+String(i)+": "+String(c->getHeight()));
		lastSize += (position == right || position == left) ? c->getHeight(): c->getWidth();
	}
	
	DBG("lastSize: "+String(lastSize));
	DBG("Current size: "+String(getHeight()));
	int lastSizeDifference = ((position == right || position == left) ? getHeight(): getWidth()) - lastSize;
	DBG("lastSizeDifference: "+String(lastSizeDifference));
	int nextPanelPosition = 0;
	if (getHeight() >= MINIMUMPANELSIZE)
	{
		//Reduce/enlarge each panel size down to MINIMUMPANELSIZE to fit new bounds and update bounds for panels
		for (int i = 0; i < getNumChildComponents(); ++i)
		{
			Component *c = getChildComponent(i);
			if (c->getName().equalsIgnoreCase("Resizable Edge Component"))
				continue;

			if (position == right || position == left)
			{
				int newSize = c->getHeight() + lastSizeDifference;
				DBG("\tPANEL Current size: "+String(c->getHeight()));
				if (newSize < MINIMUMPANELSIZE)
				{
					lastSizeDifference = newSize - MINIMUMPANELSIZE;
					newSize = MINIMUMPANELSIZE;
				}
				else
				{
					lastSizeDifference = 0;
				}
				DBG("\tPANEL newSize: "+String(newSize));
				DBG("\tlastSizeDifference: "+String(lastSizeDifference));
				DBG("---------------------------------");
				c->setBounds(c->getX(), nextPanelPosition, getWidth() - RESIZABLEEDGESIZE, newSize);
				nextPanelPosition += newSize;
			}
			else
			{
				int newSize = c->getWidth() + lastSizeDifference;
				if (newSize < MINIMUMPANELSIZE)
				{
					lastSizeDifference = newSize - MINIMUMPANELSIZE;
					newSize = MINIMUMPANELSIZE;
				}
				else
				{
					lastSizeDifference = 0;
				}
				c->setBounds(nextPanelPosition, c->getY(), newSize, getHeight() - RESIZABLEEDGESIZE);
				nextPanelPosition += newSize;
			}
		}
	}


}

void PanelContainer::paint (Graphics& g)
{
	g.fillAll (Colour((uint8) 49, (uint8) 124, (uint8) 205));
}

void PanelContainer::childBoundsChanged (Component *child)
{
	bool childIsPanel = false;
	int childIndex = 0;
	//check if child was a panel which is being resized
	for (int i = 0; i < getNumChildComponents(); ++i)
	{
		Component *c = getChildComponent(i);
		if (c->getName().equalsIgnoreCase("Resizable Edge Component"))
			continue;

		if (c == child)
		{
			childIsPanel = true;
			childIndex = i;
			break;
		}
	}

	if (childIsPanel && childIndex >= 2)
	{
		//for (int i = 0; i < getNumChildComponents(); ++i)
		//{
			Component *c1 = getChildComponent(childIndex - 1);
			Component *c2 = getChildComponent(childIndex);

			if (position == right || position == left)
			{
				if (c1->getHeight() + c1->getY() != c2->getY())
				{
					c1->setSize(c1->getWidth(), c2->getY() - c1->getY());
				}
			}
			else
			{
				if (c1->getWidth() + c1->getX() != c2->getX())
				{
					c1->setSize(c2->getX() - c1->getX(), c1->getHeight());
				}
			}
		//}

		resized();
	}
}

void PanelContainer::componentChildrenChanged (Component & component)
{
	//TODO: check if component changed is a panel
	if (&component == resizableEdgeComponent)
		return;

	DBG("PanelContainer::componentChildrenChanged (Component & component)");
	int panelSize = (position==right || position==left) ? this->getHeight() / (getNumChildComponents() - 1) : this->getWidth() / (getNumChildComponents() - 1);
	int drawCount = 0;	//counter to know how many panels have been drawn at each iteration
	int remainingSize = (position==right || position==left) ? this->getHeight() : this->getWidth();
	for (int i = 0; i < getNumChildComponents(); ++i)
	{
		Component *c = getChildComponent(i);
		if (c->getName().equalsIgnoreCase("Resizable Edge Component"))
			continue;

		//if this will be the last panel drawn, set panel size to the remaining pixels
		if (i == getNumChildComponents() - 1) panelSize = remainingSize;

		if (position==top)
		{
			c->setBounds(drawCount * panelSize, 0, panelSize, getHeight() - RESIZABLEEDGESIZE);
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Panel::horizontal);
		}

		if (position==right)
		{
			c->setBounds(RESIZABLEEDGESIZE, drawCount * panelSize, getWidth() - RESIZABLEEDGESIZE, panelSize);
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Panel::vertical);
		}

		if (position==bottom)
		{
			c->setBounds(drawCount * panelSize, RESIZABLEEDGESIZE, panelSize, getHeight() - RESIZABLEEDGESIZE);
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Panel::horizontal);
		}

		if (position==left)
		{
			c->setBounds(0, drawCount * panelSize, getWidth() - RESIZABLEEDGESIZE, panelSize);
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Panel::vertical);
		}

		//If it's the first panel, do not draw its ResizableEdgeComponent
		if (drawCount == 0)
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Panel::none);

		++drawCount;
		remainingSize -= panelSize;
	}

	resized();
}

