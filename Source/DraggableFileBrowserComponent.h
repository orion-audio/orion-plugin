/*
 ==============================================================================
 
 DraggableFileBrowserComponent.h
 Created: 7 Oct 2019 3:29:04pm
 Author:  Quin Scacheri
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileComponent.h"

class DraggableFileBrowserComponent : public Component, public ChangeListener, public FileComponentListener
{
public:
    
    // ************************Window********************************
    class DirectoryWindowComponent : public Component
    {
    public:
        const float sizeRatio = .1;
                
        void resized() override{
        }
        
        void paint(Graphics &g) override
        {
            g.fillAll();
            g.drawRect(getLocalBounds(), 1.f);
        }
        
        void setNewDirectory(DirectoryContentsList &newDir)
        {
            int numFiles = newDir.getNumFiles();
            fileComponents.clear();
            for (int i = 0; i < numFiles; i++)
            {
                fileComponents.push_back(std::make_unique<FileComponent>(newDir.getFile(i), i));
                addAndMakeVisible(fileComponents[i].get());
            }
            
            resizeToFitNewDirectory();
            
        }
        
        void resizeToFitNewDirectory()
        {
            
            int fileCounter = 0;
            int numCols;
            int numRows = 0;
            int numFiles = (int)fileComponents.size() - 1;
        
            int w = getWidth() * .25;
            
            int windowHeight = w * 1.2 * ceil((float)(numFiles + 1) / 4.f);
            if (windowHeight < getHeight())
                windowHeight = getHeight();
            
            setSize(getWidth(), windowHeight);
            Rectangle<int> area(0, 0, getWidth() / 4, getWidth() / 4);
            
            while(fileCounter <= numFiles)
            {
                if (fileCounter + 4 > fileComponents.size())
                    numCols = 1 + numFiles - fileCounter;
                else
                    numCols = 4;
                
                for (int cols = 0; cols < numCols; cols++)
                {
                    fileComponents[fileCounter]->setBounds(area.withSizeKeepingCentre(w * .8, w * .8));
                    area.translate(getWidth() / 4, 0);
                    fileCounter++;
                }
                
                numRows++;
                area.translate(0, area.getWidth());
                area.setX(0);

            }

            repaint();

        }
                
        std::vector<std::unique_ptr<FileComponent>> fileComponents;
    private:
        int numColoums;
        int numRows;
    };
    
        DraggableFileBrowserComponent();
    
    void resized() override;
    
    void scanDirectory(File directory);
    
    virtual void changeListenerCallback ( ChangeBroadcaster* source ) override;
    
    virtual void directorySelected(File f) override;
    
    virtual void fileClicked(int index) override;
    
private:
    int currentHighlighted = -1;
    
    DirectoryWindowComponent windowComponent;
    File previousDirectory;
    
    Viewport viewPort;
    TimeSliceThread scannerThread;
    WildcardFileFilter filter;
    DirectoryContentsList currentDirectory;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DraggableFileBrowserComponent)
};
