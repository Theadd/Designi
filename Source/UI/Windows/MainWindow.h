/*
  ==============================================================================

    MainWindow.h
    Created: 14 Oct 2013 8:32:04pm
    Author:  admin

  ==============================================================================
*/

#ifndef __MAINWINDOW_H_F0B8E400__
#define __MAINWINDOW_H_F0B8E400__

#include "MainWindow/MainLayout.h"
#include "../Styles/BaseOnly/BaseOnly.h"
#include "../Styles/DuskMap/DuskMap.h"

class MainWindow    : public DocumentWindow
{
public:
    MainWindow();
	~MainWindow();
	
	void loadLayout ();

    void closeButtonPressed();

    void mouseUp (const MouseEvent& event);

    void mouseDrag (const MouseEvent& event);

    void mouseDoubleClick (const MouseEvent& event);

	StringArray getRenderingEngines() const;
    int getActiveRenderingEngine() const;
    void setRenderingEngine (int index);

	ApplicationCommandManager commandManager;

	DuskMapLookAndFeel duskMapLookAndFeel;
	BaseOnlyLookAndFeel baseOnlyLookAndFeel;

private:
	//ScopedPointer <DuskMapLookAndFeel> duskMapLookAndFeel;
    ScopedPointer <MainLayout> mainLayout;

	#if JUCE_OPENGL
     OpenGLContext openGLContext;
	#endif

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};




#endif  // __MAINWINDOW_H_F0B8E400__
