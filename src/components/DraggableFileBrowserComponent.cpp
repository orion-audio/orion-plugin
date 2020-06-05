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
    
    backButton.reset(new ImageButton());
    backButton->setAlwaysOnTop(true);
    Image backImage = ImageCache::getFromMemory(BinaryData::back_arrow_png, BinaryData::back_arrow_pngSize);
    backButton->setImages(false, true, true, backImage, 1.f, Colours::transparentBlack, backImage, 1.f, Colours::transparentBlack, backImage, 1.f, Colours::transparentBlack);
    backButton->onClick = [this] {
        scanDirectory(currentDirectory.getDirectory().getParentDirectory());
    };
    addAndMakeVisible(backButton.get());
    
    addAndMakeVisible(windowComponent);
    currentDirectory.addChangeListener(this);
    scanDirectory(File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory));
    addAndMakeVisible(viewPort);
    viewPort.setViewedComponent(&windowComponent, false);
    viewPort.setScrollBarsShown(true, false);
}

void DraggableFileBrowserComponent::resized()
{
    windowComponent.setBounds(getLocalBounds());
    viewPort.setBounds(getLocalBounds());
    backButton->setBounds(0, 0, getWidth() * .125, getWidth() * .125);

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
