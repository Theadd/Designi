/*
  ==============================================================================

    MainWindow.h
    Created: 14 Oct 2013 8:32:04pm
    Author:  admin

  ==============================================================================
*/

#ifndef __MAINWINDOW_H_F0B8E400__
#define __MAINWINDOW_H_F0B8E400__

#include "MainLayout/MainLayout.h"

class MainWindow    : public DocumentWindow
{
public:
    MainWindow();
	~MainWindow();

    void closeButtonPressed();

    void mouseUp (const MouseEvent& event);

    void mouseDrag (const MouseEvent& event);

    void mouseDoubleClick (const MouseEvent& event);

	ApplicationCommandManager commandManager;

private:
    ScopedPointer <MainLayout> mainLayout;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};




#endif  // __MAINWINDOW_H_F0B8E400__
