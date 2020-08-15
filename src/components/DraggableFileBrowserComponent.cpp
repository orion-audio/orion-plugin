/*
 ==============================================================================
 
 DraggableFileBrowserComponent.cpp
 Created: 7 Oct 2019 10:26:35pm
 Author:  Quin Scacheri
 
 ==============================================================================
 */

#include "DraggableFileBrowserComponent.h"

DraggableFileBrowserComponent::DraggableFileBrowserComponent() : scannerThread("scanner"),
    viewPort("view"),
    filter("*.wav; *.mp3; *.aiff", "*", ""),
    currentDirectory(nullptr, scannerThread)
{
    
    //Back Button
    //backButton.reset(new ImageButton());
    //backButton->setAlwaysOnTop(true);
    //Image backImageOff = ImageCache::getFromMemory(BinaryData::dirBackOff_png, BinaryData::dirBackOff_pngSize);
    //Image backImageOn = ImageCache::getFromMemory(BinaryData::dirBackOn_png, BinaryData::dirBackOn_pngSize);
    //backButton->setImages(false, true, true, backImageOff, 1.f, Colours::transparentBlack, backImageOff, 1.f, Colours::transparentBlack, backImageOn, 1.f, Colours::transparentBlack);
    //addAndMakeVisible(backButton.get());
    //backButton->onClick = [this] {
        //scanDirectory(currentDirectory.getDirectory().getParentDirectory());
    //};
    
    
    

    //Window Component
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
    //backButton->setBounds(0, getHeight()*0.975, getWidth(), getWidth() * 0.1);
    
}

void DraggableFileBrowserComponent::scanDirectory(File directory)
{
    scannerThread.startThread();
    currentDirectory.setDirectory(directory, true, true);
    DBG("3");
}

void DraggableFileBrowserComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    scannerThread.stopThread(-1);
    
    windowComponent.setBounds(getLocalBounds());
    //windowComponent.setBounds(0, 0, getWidth(), getHeight() - backButton->getHeight());
    
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

bool DraggableFileBrowserComponent::isInterestedInFileDrag (const StringArray &files)
{
    return true;
}

void DraggableFileBrowserComponent::filesDropped (const StringArray &files, int x, int y)
{
    File file(files[0]);
    if (!file.isDirectory())
        file = file.getParentDirectory();        
        
    directorySelected(file);
}
