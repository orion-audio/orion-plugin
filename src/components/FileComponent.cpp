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
    Image image;
    if (file.isDirectory())
        image = ImageCache::getFromMemory(BinaryData::folder_Off_png, BinaryData::folder_Off_pngSize);
    else
        image = ImageCache::getFromMemory(BinaryData::sound_file_png, BinaryData::sound_file_pngSize);

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
//    g.drawRect(getLocalBounds());// Draw Frame
      
    int h = getHeight() * .6;
    int w = getHeight() * .7;
    
    g.drawImageWithin(fileImage,
                      getWidth() * .2/* x */,
                      getWidth() * .1/* y */,
                      w * 1.0/* width */,
                      h * 1.0/* height */,
                      RectanglePlacement::stretchToFit);
    
    g.setColour(Colours::white);
    font.setHeight(getHeight() * .175);// also can adjust font size
    g.setFont(font);
    g.drawText(name,
               0/* x */,
               getHeight() * .75/* y */,
               getWidth()/* width */,
               getHeight() * .2/* height */,
               Justification::centred);
}

void FileComponent::mouseDown(const MouseEvent &e)
{
    Image image = ImageCache::getFromMemory(BinaryData::folder_On_png, BinaryData::folder_On_pngSize);
    setImage(image);
    //isHighlighted = true;
    updateHighlighted();
}

void FileComponent::mouseUp(const MouseEvent &e)
{
    if (e.getNumberOfClicks() >= 2)
    {
        if (file.isDirectory())
        {
            notifyListeners(file);
        }
            
    }
    else
    {
        Image image = ImageCache::getFromMemory(BinaryData::folder_Off_png, BinaryData::folder_Off_pngSize);
        setImage(image);
        //isHighlighted = true;
    }
        
    
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
