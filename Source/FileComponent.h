/*
  ==============================================================================

    FileComponent.h
    Created: 8 Oct 2019 10:19:08am
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class FileComponentListener
{
public:
    virtual void directorySelected(File f)=0;
    virtual void fileClicked(int index)=0;

};

class FileComponent : public Button
{
public:
    FileComponent(File f, int i);
        
    void mouseUp(const MouseEvent &e) override;
    void mouseDown(const MouseEvent &e) override;

    void mouseDrag(const MouseEvent &e) override;
    
    void setImage(Image buttonImage);
    
    virtual void paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    void addListener(FileComponentListener* listener)
    {
        listeners.push_back(listener);
    }
    
    void removeListener(FileComponentListener* listener)
    {
        for (int i = 0; i < listeners.size(); i++){
            if (listeners[i] == listener)
                DBG("FOUND");
        }
    }
    
    void updateHighlighted()
    {
        for (int i = 0; i < listeners.size(); i++){
            listeners[i]->fileClicked(fileIndex);
        }

    }
    
    void notifyListeners(File newDirectory)
    {
        for (int i = 0; i < listeners.size(); i++){
            listeners[i]->directorySelected(newDirectory);
        }
    }

    std::vector<FileComponentListener*> listeners;
    File file;
    int fileIndex;
    bool isHighlighted = false;

private:
    Font font;
    Image fileImage;
    String name;
};
