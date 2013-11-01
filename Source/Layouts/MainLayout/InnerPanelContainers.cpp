/*
  ==============================================================================

    RightPanelContainer.cpp
    Created: 15 Oct 2013 1:57:51pm
    Author:  admin

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"


#include "InnerPanelContainers.h"
#include "InnerPanel.h"
#include "MainLayout.h"
#include "../ExtendedLookAndFeel.h"



//////////////////////////////////////////////////////////////////////


Panel::Panel(const String& name, DragAndDropContainer* _dragAndDropContainer, int _id) : Component (name), dragAndDropContainer(_dragAndDropContainer), id(_id)
{
	resizableEdgeComponent = nullptr;
	componentBoundsConstrainer = nullptr;
	componentBoundsConstrainer = new ComponentBoundsConstrainer();
	componentBoundsConstrainer->setMinimumSize(50, 60);
	//componentBoundsConstrainer->setMaximumHeight(200);
	addAndMakeVisible(resizableEdgeComponent = new ResizableEdgeComponent(this, componentBoundsConstrainer, ResizableEdgeComponent::topEdge));
	tabbedComponent = nullptr;
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
		if (resizableEdgeOrientation == Globals::vertical)
			resizableEdgeComponent->setBounds(0, 0, r.getWidth(), RESIZABLEEDGESIZE);

		if (resizableEdgeOrientation == Globals::horizontal)
			resizableEdgeComponent->setBounds(0, 0, RESIZABLEEDGESIZE, r.getHeight());

		if (resizableEdgeOrientation == Globals::none)
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
			if (resizableEdgeOrientation == Globals::vertical)
				componentToBeResized->setBounds(0, RESIZABLEEDGESIZE, r.getWidth(), r.getHeight() - RESIZABLEEDGESIZE);

			if (resizableEdgeOrientation == Globals::horizontal)
				componentToBeResized->setBounds(RESIZABLEEDGESIZE, 0, r.getWidth() - RESIZABLEEDGESIZE, r.getHeight());

			if (resizableEdgeOrientation == Globals::none)
				componentToBeResized->setBounds(0, 0, r.getWidth(), r.getHeight());
		}
	}
}

void Panel::paint (Graphics& g)
{
	((ExtendedLookAndFeel*) &getLookAndFeel())->drawPanel (g, *this);
}

bool Panel::addInnerPanel (InnerPanel *componentToAdd)
{
	Colour tabsColour((juce::uint8) 22, (juce::uint8) 25, (juce::uint8) 27, (juce::uint8) 255);
	DBG("TABS COLOUR: "+tabsColour.toDisplayString(false));
	int numChilds = getNumChildComponents() - 1;
	bool asTab = componentToAdd->showAsTab;

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
			tabbedComponent->addChildComponent(componentToAdd);	//we add as child so we can get this tabbed component looking for inner component's parent
			tabbedComponent->addTab(componentToAdd->getName(), tabsColour, componentToAdd, false);
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
				addAndMakeVisible(tabbedComponent = new CustomTabbedComponent(TabbedButtonBar::TabsAtTop));
				tabbedComponent->setName(getName() + " TabbedComponent");
			}

			//add this component in a new tab
			tabbedComponent->addChildComponent(componentToAdd);	//set as child so we can find parent components from child
			tabbedComponent->addTab(componentToAdd->getName(), tabsColour, componentToAdd, false);
		}
		else
		{
			//Add component without a tabbedComponent
			addAndMakeVisible(componentToAdd);
		}
	}

	//drag&drop of tab buttons
	if  (tabbedComponent != nullptr && dragAndDropContainer != nullptr)
	{
		TabbedButtonBar& buttonBar = tabbedComponent->getTabbedButtonBar();
		TabBarButton* lastTabButton	= buttonBar.getTabButton (buttonBar.getNumTabs() - 1);
		lastTabButton->addMouseListener(this, false);
		lastTabButton = nullptr;
	}


	resized();

	return true;
}

void Panel::mouseDrag (const MouseEvent &event)
{
	if (dragAndDropContainer != nullptr)
	{
		if (!dragAndDropContainer->isDragAndDropActive())
		{
			//GET InnerPanel corresponding to the dragged tab button
			TabbedButtonBar& buttonBar = tabbedComponent->getTabbedButtonBar();
			int tabIndex = buttonBar.indexOfTabButton((TabBarButton *)event.eventComponent);
			Component *innerPanelBeingDragged = tabbedComponent->getTabContentComponent(tabIndex);
			//GET TAB BUTTON SNAPSHOT (IMAGE)
			Image dragImage = event.eventComponent->createComponentSnapshot (event.eventComponent->getLocalBounds()).convertedToFormat (Image::ARGB);
            dragImage.multiplyAllAlphas (0.6f);

			dragAndDropContainer->startDragging("InnerPanel#"+String(tabIndex), innerPanelBeingDragged, dragImage);
		}
	}
}

bool Panel::isInterestedInDragSource (const SourceDetails &dragSourceDetails)
{
	String description(dragSourceDetails.description);
	return (description.upToFirstOccurrenceOf("#", false, false).equalsIgnoreCase("InnerPanel"));
}

void Panel::itemDropped (const SourceDetails &dragSourceDetails)
{
	String description(dragSourceDetails.description);
	if  (description.upToFirstOccurrenceOf("#", false, false).equalsIgnoreCase("InnerPanel"))
	{
		int tabIndex = description.fromFirstOccurrenceOf("#", false, false).getIntValue();
		InnerPanel *innerPanel = (InnerPanel *)dragSourceDetails.sourceComponent.get();
		//remove this panel from its current TabbedComponent
		//DBG("innerPanel parentComponent name: " + innerPanel->getParentComponent()->getName());
		//TabbedComponent *currentTabbedComponent = (TabbedComponent *)innerPanel->getParentComponent();

		/*TabbedComponent *currentTabbedComponent = innerPanel->findParentComponentOfClass <TabbedComponent>();
		if (currentTabbedComponent == 0)
		{
			DBG("parentComponent of class TabbedComponent NOT FOUND!");
			return;
		}
		 
		
		DBG("removeTab call, index: "+String(tabIndex)+", numTabs: "+String(currentTabbedComponent->getNumTabs()));
		currentTabbedComponent->removeTab(tabIndex);
		DBG("addInnerTab call");
		addInnerPanel(innerPanel);*/

		Panel *currentPanel = innerPanel->findParentComponentOfClass <Panel>();
		if (currentPanel == 0)
		{
			DBG("Parent Panel of InnerPanel being dropped was not found!");
			return;
			
		}
		
		addInnerPanel(innerPanel);
		currentPanel->removeInnerPanelAt(tabIndex);

		MainLayout *mainLayout = findParentComponentOfClass <MainLayout>();
		if (mainLayout != 0)
			mainLayout->resized();
	}
}

void Panel::removeInnerPanelAt (int tabIndex)
{
	bool swapPanel = (tabbedComponent->getCurrentTabIndex() == tabIndex) ? true : false;
	tabbedComponent->removeTab(tabIndex);
	//hide panel if there are no other tabs
	if (tabbedComponent->getNumTabs() == 0)
	{
		getParentComponent()->removeChildComponent(this);
		//delete this;
	}
	else if (swapPanel)
	{
		tabbedComponent->setCurrentTabIndex(0);
	}
}

bool Panel::removeInnerPanel(InnerPanel *innerPanel)
{
	if (tabbedComponent != nullptr)
	{
		for (int i = 0; i < tabbedComponent->getNumTabs(); ++i)
		{
			if (innerPanel == tabbedComponent->getTabContentComponent(i))
			{
				removeInnerPanelAt(i);
				return true;
			}
		}
	}
	return false;
}

void Panel::showInnerPanel(InnerPanel *innerPanel)
{
	if (tabbedComponent != nullptr)
	{
		for (int i = 0; i < tabbedComponent->getNumTabs(); ++i)
		{
			if (innerPanel == tabbedComponent->getTabContentComponent(i))
			{
				tabbedComponent->setCurrentTabIndex(i);
				return;
			}
		}
	}
}

bool Panel::isInnerPanelVisible(InnerPanel* innerPanel)
{
	if (tabbedComponent != nullptr)
		for (int i = 0; i < tabbedComponent->getNumTabs(); ++i)
			if (innerPanel == tabbedComponent->getTabContentComponent(i))
				return true;

	return false;
}

void Panel::setResizableEdgeOrientation(Globals::Orientation resizableEdgeOrientation_)
{
	resizableEdgeOrientation = resizableEdgeOrientation_;
	resized();
}


Panel::CustomTabbedComponent::CustomTabbedComponent() : TabbedComponent(TabbedButtonBar::TabsAtTop)
{
	setTabBarDepth(27);
}

Panel::CustomTabbedComponent::CustomTabbedComponent(TabbedButtonBar::Orientation _orientation) : TabbedComponent(_orientation)
{
	setTabBarDepth(27);
}

void Panel::CustomTabbedComponent::addTab (const String& tabName,
                              Colour tabBackgroundColour,
                              Component* const contentComponent,
                              const bool deleteComponentWhenNotNeeded,
                              const int insertIndex)
{
	//DBG("\t\t\t!!!! TAB BAR DEPTH: "+String(getTabBarDepth()));
	TabbedComponent::addTab(tabName, tabBackgroundColour, contentComponent, deleteComponentWhenNotNeeded, insertIndex);
    
	//ADD CLOSE TAB BUTTON
	TabbedButtonBar& buttonBar = getTabbedButtonBar();
	TabBarButton *button;

	if (insertIndex == -1)
		button = buttonBar.getTabButton(buttonBar.getNumTabs() - 1);
	else
		button = buttonBar.getTabButton(insertIndex);

	CloseTabButton *close = new CloseTabButton();
	close->setSize(20, 10);
	close->addMouseListener(this, false);
	button->setExtraComponent(close, TabBarButton::afterText);
}

void Panel::CustomTabbedComponent::CloseTabButton::paint (Graphics& g)
{
	Rectangle<int> r = getLocalBounds();
	g.setColour(getLookAndFeel().findColour(Label::textColourId).withAlpha(0.5f));
	float size = 6.0f;
	float hSwitch = -3.0f;
	float indent = (((float) r.getHeight()) - size) / 2.0f;
	if (indent > 0.0f)
	{
		g.drawLine(indent + hSwitch, indent, indent + size + hSwitch, indent + size, 1.5f);
		g.drawLine(indent + hSwitch, indent + size, indent + size + hSwitch, indent, 1.5f);
	}
}

void Panel::CustomTabbedComponent::popupMenuClickOnTab (int tabIndex, const String &tabName)
{
	DBG("popupMenuClickOnTab: " + tabName);
	//check if its on leftPanelContainer or rightPanelContainer so we disable moving to the same panel
	bool isOnLeftPanel = true;
	bool isOnRightPanel = true;
	bool isOnTopPanel = true;
	bool isOnBottomPanel = true;
	bool isOnCenterPanel = true;
	PanelContainer *panelContainer = findParentComponentOfClass <PanelContainer>();
	if (panelContainer != 0)
	{
		isOnLeftPanel = (panelContainer->position == Globals::left);
		isOnRightPanel = (panelContainer->position == Globals::right);
		isOnTopPanel = (panelContainer->position == Globals::top);
		isOnBottomPanel = (panelContainer->position == Globals::bottom);
		isOnCenterPanel = (panelContainer->position == Globals::center);
	}

	PopupMenu m;
    m.addItem (1, "Close");
	m.addSeparator();

				PopupMenu moveToSubMenu;
            
			moveToSubMenu.addItem (5, "Top Panel", !isOnTopPanel, isOnTopPanel);
			moveToSubMenu.addItem (3, "Right Panel", !isOnRightPanel, isOnRightPanel);
			moveToSubMenu.addItem (6, "Bottom Panel", !isOnBottomPanel, isOnBottomPanel);
			moveToSubMenu.addItem (2, "Left Panel", !isOnLeftPanel, isOnLeftPanel);
			moveToSubMenu.addSeparator();
			moveToSubMenu.addItem (7, "Center Panel", !isOnCenterPanel, isOnCenterPanel);


			m.addSubMenu ("Move To", moveToSubMenu);

    //m.addItem (2, "Move To Left Panel", !isOnLeftPanel, isOnLeftPanel);
	//m.addItem (3, "Move To Right Panel", !isOnRightPanel, isOnRightPanel);
    //m.addSeparator();
    m.addItem (4, "Move Away", true);

	TabbedButtonBar& buttonBar = getTabbedButtonBar();
	TabBarButton *button = buttonBar.getTabButton(tabIndex);

    m.showMenuAsync (PopupMenu::Options().withTargetComponent (button),
                        ModalCallbackFunction::forComponent (menuItemChosenCallback, this, tabIndex));

}

void Panel::CustomTabbedComponent::menuItemChosenCallback (int result, CustomTabbedComponent* component, int tabIndex)
{
	DBG("static menuItemChosenCallback");
    if (component != nullptr)
	{
        component->menuItemChosenCallback (result, (InnerPanel *) component->getTabContentComponent(tabIndex));
	}
}

void Panel::CustomTabbedComponent::menuItemChosenCallback (int result, InnerPanel* innerPanel)
{
    DBG("menuItemChosenCallback");
	MainLayout *mainLayout = findParentComponentOfClass <MainLayout>();
	PanelContainer *panelContainer = innerPanel->findParentComponentOfClass <PanelContainer>();
	if (mainLayout == 0 || panelContainer == 0)
		return;

	switch (result)
	{
	case 1:
		mainLayout->toggleInnerPanel(innerPanel, innerPanel->position, true);	//close
		break;
	case 2:
		mainLayout->toggleInnerPanel(innerPanel, innerPanel->position);
		mainLayout->toggleInnerPanel(innerPanel, Globals::left);
		break;
	case 3:
		mainLayout->toggleInnerPanel(innerPanel, innerPanel->position);
		mainLayout->toggleInnerPanel(innerPanel, Globals::right);
		break;
	case 4:
		mainLayout->toggleInnerPanel(innerPanel);
		panelContainer->addInnerPanel(innerPanel, true);
		break;
	case 5:
		mainLayout->toggleInnerPanel(innerPanel, innerPanel->position);
		mainLayout->toggleInnerPanel(innerPanel, Globals::top);
		break;
	case 6:
		mainLayout->toggleInnerPanel(innerPanel, innerPanel->position);
		mainLayout->toggleInnerPanel(innerPanel, Globals::bottom);
		break;
	case 7:	//Move To -> Center Panel
		mainLayout->toggleInnerPanel(innerPanel, innerPanel->position);
		mainLayout->toggleInnerPanel(innerPanel, Globals::center);
		break;
	default:
		break;
	}
}

void Panel::CustomTabbedComponent::mouseUp (const MouseEvent& event)
{
	MainLayout *mainLayout = findParentComponentOfClass <MainLayout>();
	//close tab button
	if (mainLayout != 0 && event.mouseWasClicked())
	{
		TabbedButtonBar& buttonBar = getTabbedButtonBar();
		for (int i = 0; i < buttonBar.getNumTabs(); ++i)
		{
			TabBarButton *button = buttonBar.getTabButton(i);
			if (button->getExtraComponent() == event.eventComponent)
			{
				InnerPanel* innerPanel = (InnerPanel *) getTabContentComponent(i);
				mainLayout->toggleInnerPanel(innerPanel, innerPanel->position, true);
				break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////


PanelContainer::PanelContainer(Globals::Position positionThatWillBePlaced, DragAndDropContainer* _dragAndDropContainer) : Component(), position(positionThatWillBePlaced), dragAndDropContainer(_dragAndDropContainer)
{
    setBounds(0, 32, 260, 340);
	setName("PanelContainer");
	//DBG("one");
	resizableEdgeComponent = nullptr;
	componentBoundsConstrainer = nullptr;
	componentBoundsConstrainer = new ComponentBoundsConstrainer();
	componentBoundsConstrainer->setMinimumSize(200, 150);
	ResizableEdgeComponent::Edge resizableEdge = ResizableEdgeComponent::leftEdge;

	switch (position)
	{
	case Globals::top:
		resizableEdge = ResizableEdgeComponent::bottomEdge;
		break;
	case Globals::right:
		resizableEdge = ResizableEdgeComponent::leftEdge;
		break;
	case Globals::bottom:
		resizableEdge = ResizableEdgeComponent::topEdge;
		break;
	case Globals::left:
		resizableEdge = ResizableEdgeComponent::rightEdge;
		break;
	case Globals::center:
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
	removeComponentListener(this);
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
		if (position==Globals::top)
			resizableEdgeComponent->setBounds(0, r.getHeight() - RESIZABLEEDGESIZE,  r.getWidth(), RESIZABLEEDGESIZE);

		if (position==Globals::right)
			resizableEdgeComponent->setBounds(0, 0,  RESIZABLEEDGESIZE, r.getHeight());

		if (position==Globals::bottom)
			resizableEdgeComponent->setBounds(0, 0,  r.getWidth(), RESIZABLEEDGESIZE);

		if (position==Globals::left)
			resizableEdgeComponent->setBounds(r.getWidth() - RESIZABLEEDGESIZE, 0,  RESIZABLEEDGESIZE, r.getHeight());

		if (position==Globals::center)
			resizableEdgeComponent->setBounds(0, 0, 0, 0);
	}

	//DBG("PanelContainer resized()");
	//int numChilds = getNumChildComponents() - 1;
	int lastSize = 0;
	//Get lastSize in pixels
	for (int i = 0; i < getNumChildComponents(); ++i)
	{
		Component *c = getChildComponent(i);
		if (c->getName().equalsIgnoreCase("Resizable Edge Component"))
			continue;

		//DBG("--Size of Panel "+String(i)+": "+String(c->getHeight()));
		lastSize += (position == Globals::right || position == Globals::left) ? c->getHeight(): c->getWidth();
	}
	
	//DBG("lastSize: "+String(lastSize));
	//DBG("Current size: "+String(getHeight()));
	int lastSizeDifference = ((position == Globals::right || position == Globals::left) ? getHeight(): getWidth()) - lastSize;
	//DBG("lastSizeDifference: "+String(lastSizeDifference));
	int nextPanelPosition = 0;
	if (getHeight() >= MINIMUMPANELSIZE)
	{
		//Reduce/enlarge each panel size down to MINIMUMPANELSIZE to fit new bounds and update bounds for panels
		for (int i = 0; i < getNumChildComponents(); ++i)
		{
			Component *c = getChildComponent(i);
			if (c->getName().equalsIgnoreCase("Resizable Edge Component"))
				continue;

			if (position == Globals::right || position == Globals::left)
			{
				int newSize = c->getHeight() + lastSizeDifference;
				//DBG("\tPANEL Current size: "+String(c->getHeight()));
				if (newSize < MINIMUMPANELSIZE)
				{
					lastSizeDifference = newSize - MINIMUMPANELSIZE;
					newSize = MINIMUMPANELSIZE;
				}
				else
				{
					lastSizeDifference = 0;
				}
				//DBG("\tPANEL newSize: "+String(newSize));
				//DBG("\tlastSizeDifference: "+String(lastSizeDifference));
				//DBG("---------------------------------");
				c->setBounds(c->getX(), nextPanelPosition, getWidth() - RESIZABLEEDGESIZE, newSize);
				nextPanelPosition += newSize;
			}
			else if (position == Globals::center)
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
				c->setBounds(nextPanelPosition, c->getY(), newSize, getHeight());
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
	//g.fillAll (Colour((uint8) 49, (uint8) 124, (uint8) 205));
	((ExtendedLookAndFeel*) &getLookAndFeel())->drawPanelContainer (g, *this);
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

			if (position == Globals::right || position == Globals::left)
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
	DBG("Component name: "+component.getName()+", getNumChildComponents(): "+String(getNumChildComponents()));

	if (component.getParentComponent() != this)
	{
		//child component was removed, delete it from panels OwnedArray
		DBG("child component was removed, delete it from panels OwnedArray");
		panels.remove(((Panel *) &component)->id, true);
	}

	if (getNumChildComponents() - 1 == 0)
	{
		//This PanelContainer is empty, so we hide it!
		DBG("This PanelContainer is empty, so we hide it! panels.size(): " + panels.size());
		setVisible(false);

		return;
	}

	int panelSize = (position==Globals::right || position==Globals::left) ? this->getHeight() / (getNumChildComponents() - 1) : this->getWidth() / (getNumChildComponents() - 1);
	int drawCount = 0;	//counter to know how many panels have been drawn at each iteration
	int remainingSize = (position==Globals::right || position==Globals::left) ? this->getHeight() : this->getWidth();
	for (int i = 0; i < getNumChildComponents(); ++i)
	{
		Component *c = getChildComponent(i);
		if (!c->getName().equalsIgnoreCase("Panel"))
			continue;

		DBG("for (int i = "+String(i)+"; i < getNumChildComponents(); ++i), c->getName(): "+c->getName());

		//if this will be the last panel drawn, set panel size to the remaining pixels
		if (i == getNumChildComponents() - 1) panelSize = remainingSize;

		if (position==Globals::top)
		{
			c->setBounds(drawCount * panelSize, 0, panelSize, getHeight() - RESIZABLEEDGESIZE);
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Globals::horizontal);
		}

		if (position==Globals::right)
		{
			c->setBounds(RESIZABLEEDGESIZE, drawCount * panelSize, getWidth() - RESIZABLEEDGESIZE, panelSize);
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Globals::vertical);
		}

		if (position==Globals::bottom)
		{
			c->setBounds(drawCount * panelSize, RESIZABLEEDGESIZE, panelSize, getHeight() - RESIZABLEEDGESIZE);
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Globals::horizontal);
		}

		if (position==Globals::left)
		{
			c->setBounds(0, drawCount * panelSize, getWidth() - RESIZABLEEDGESIZE, panelSize);
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Globals::vertical);
		}

		if (position==Globals::center)
		{
			c->setBounds(drawCount * panelSize, 0, panelSize, getHeight());
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Globals::horizontal);
		}

		//If it's the first panel, do not draw its ResizableEdgeComponent
		if (drawCount == 0)
			(dynamic_cast <Panel *> (c))->setResizableEdgeOrientation(Globals::none);

		++drawCount;
		remainingSize -= panelSize;
	}

		


	resized();
}


bool PanelContainer::addInnerPanel (InnerPanel *componentToAdd, bool asNewPanel)
{
	setVisible(true);
	componentToAdd->position = position;

	DBG("\t[PanelContainer::addInnerPanel] panels.size(): "+String(panels.size()));
	if (panels.size() == 0)	//if there was no old panel created, create a new panel
		asNewPanel = true;

	if (asNewPanel)
	{
		panels.add(new Panel("Panel", dragAndDropContainer));
		panels.getLast()->id = panels.indexOf(panels.getLast());
		addAndMakeVisible(panels.getLast());
		return panels.getLast()->addInnerPanel(componentToAdd);
	}
	else
	{
		return panels.getFirst()->addInnerPanel(componentToAdd);
	}

}

bool PanelContainer::isEmpty()
{
	return (panels.size() == 0);
}

bool PanelContainer::removeInnerPanel(InnerPanel *innerPanel)
{
	for (int i = 0; i < panels.size(); ++i)
		if (panels[i]->removeInnerPanel(innerPanel))
			return true;

	return false;
}

void PanelContainer::showInnerPanel(InnerPanel *innerPanel)
{
	for (int i = 0; i < panels.size(); ++i)
	{
		if (panels[i]->isInnerPanelVisible(innerPanel))
		{
			panels[i]->showInnerPanel(innerPanel);
			return;
		}
	}
}

bool PanelContainer::isInnerPanelVisible(InnerPanel* innerPanel)
{
	for (int i = 0; i < panels.size(); ++i)
		if (panels[i]->isInnerPanelVisible(innerPanel))
			return true;

	return false;
}