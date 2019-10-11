/*
  ==============================================================================

    FileComponent.cpp
    Created: 8 Oct 2019 10:19:08am
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileComponent.h"

//==============================================================================
FileComponent::FileComponent(File f, int i) : Button("")
{
    file = f;
    name = f.getFileName();
    
    fileIndex = i;
    
    Image image = ImageCache::getFromMemory(BinaryData::file_png, BinaryData::file_pngSize);
    setImage(image);
}

void FileComponent::setImage(Image buttonImage)
{
    fileImage = buttonImage;
}

void FileComponent::paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    if (isHighlighted)
    {
        g.fillAll(Colours::aqua.withAlpha(.3f));
    }
    g.drawRect(getLocalBounds());
    int h = getHeight() * .6;
    int w = h;
    g.drawImageWithin(fileImage, getWidth() * .2, getWidth() * .1, w, h, RectanglePlacement::stretchToFit);
    g.setColour(Colours::white);
    font.setHeight(getHeight() * .2);
    g.setFont(font);
    g.drawText(name, 0, getHeight() * .75, getWidth(), getHeight() * .2, Justification::centred);
}

void FileComponent::mouseDown(const MouseEvent &e)
{
    
    isHighlighted = true;
    updateHighlighted();
}

void FileComponent::mouseUp(const MouseEvent &e)
{
    if (e.getNumberOfClicks() >= 2)
    {
        if (file.isDirectory())
            notifyListeners(file);
    }
    else
        isHighlighted = true;
    
    repaint();
}

void FileComponent::mouseDrag(const MouseEvent &e)
{
    Button::mouseDrag(e);
    if (!e.mouseWasDraggedSinceMouseDown())
        return;
    
    StringArray files;
    files.add(file.getFullPathName());
    DragAndDropContainer::performExternalDragDropOfFiles(files, false);
}
