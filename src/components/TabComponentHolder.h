/*
  ==============================================================================

    TabComponentHolder.h
    Created: 30 Oct 2019 12:37:57am
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <array>
#include "OrionTabComponent.h"
#include "PluginProcessor.h"

class TabComponentHolder : public Component
{
public:
    const int numTabs = 8;
    
    TabComponentHolder(OrionaudioAudioProcessor &p)
    {
        for (int i = 0; i < numTabs; i++)
        {
            tabComponents[i].reset(new OrionTabComponent(p, i));
            addAndMakeVisible(tabComponents[i].get());
        }
        
        setCurrentTab(0);
    }
    
    void setCurrentTab(int which)
    {
        currentTab = which;
        for (int i = 0; i < numTabs; i++)
        {
            
            if (i == currentTab)
            {
                tabComponents[i]->setVisible(true);
            }
            else
            {
                tabComponents[i]->setVisible(false);
            }
        }
        
        DBG(currentTab);
    }
    
    int getCurrentTab()
    {
        return currentTab;
    }
    
    void resized() override
    {
        for (int i = 0; i < numTabs; i++)
        {
            tabComponents[i]->setBounds(getLocalBounds());
        }
    }
    std::array<std::unique_ptr<OrionTabComponent>, 8> tabComponents;
private:
    int currentTab = 0;
    
};
