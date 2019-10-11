/*
 ==============================================================================
 
 DraggableFileBrowserComponent.cpp
 Created: 7 Oct 2019 10:26:35pm
 Author:  Quin Scacheri
 
 ==============================================================================
 */

#include "DraggableFileBrowserComponent.h"

DraggableFileBrowserComponent::DraggableFileBrowserComponent() : scannerThread("scanner"),
    filter("", "", ""),
    viewPort("view"),
    currentDirectory(nullptr, scannerThread)
{
    addAndMakeVisible(windowComponent);
    currentDirectory.addChangeListener(this);
    scanDirectory(File("~/Documents"));
    addAndMakeVisible(viewPort);
    viewPort.setViewedComponent(&windowComponent, false);
    viewPort.setScrollBarsShown(true, false);
}

void DraggableFileBrowserComponent::resized()
{
    windowComponent.setBounds(getLocalBounds());
    viewPort.setBounds(getLocalBounds());
}

void DraggableFileBrowserComponent::scanDirectory(File directory)
{
    scannerThread.startThread();
    currentDirectory.setDirectory(directory, true, true);
}

void DraggableFileBrowserComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    scannerThread.stopThread(-1);
    windowComponent.setBounds(getLocalBounds());
    windowComponent.setNewDirectory(currentDirectory);
    for (int i = 0; i < windowComponent.fileComponents.size(); i++){
        windowComponent.fileComponents[i]->addListener(this);
    }
}

void DraggableFileBrowserComponent::directorySelected(File f)
{
    scanDirectory(f);
    currentHighlighted = -1;
}

void DraggableFileBrowserComponent::fileClicked(int index)
{
    if (currentHighlighted >= 0)
        windowComponent.fileComponents[currentHighlighted]->isHighlighted = false;
    
    currentHighlighted = index;
    repaint();
}
