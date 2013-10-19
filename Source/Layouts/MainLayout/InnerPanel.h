/*
  ==============================================================================

    InnerPanel.h
    Created: 18 Oct 2013 6:16:30pm
    Author:  admin

  ==============================================================================
*/

#ifndef __INNERPANEL_H_9AA31784__
#define __INNERPANEL_H_9AA31784__

class InnerPanel : public Component, public SettableTooltipClient
{
public:

	InnerPanel(bool showAsTab_ = true, Globals::Position _position = Globals::left);

	bool showAsTab;
	Globals::Position position;
private:
	
};



#endif  // __INNERPANEL_H_9AA31784__
