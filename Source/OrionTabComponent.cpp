/*
  ==============================================================================

    OrionTabComponent.cpp
    Created: 11 Jun 2019 3:02:11pm
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionTabComponent.h"
#include "OrionGlobalVars.h"

//==============================================================================
OrionTabComponent::OrionTabComponent(OrionaudioAudioProcessor& p, int serial): processor(p)
{
         
    tabbedComponent.reset(new TabbedComponent(TabbedButtonBar::TabsAtTop));
    TabSerial       = serial;
    
    effectConfiguration = new OrionEffectsConfiguration(p,serial);
    eqConfiguration     = new OrionEQConfiguration(p,serial);
    envConfiguration    = new OrionEnvConfiguration(p,serial);
    clipConfiguration   = new OrionClipConfiguration(p);
      
    tabbedComponent->addTab(translate("ENV"), Colours::lightgrey, envConfiguration, true);
    tabbedComponent->addTab(translate("EQ"), Colours::lightgrey, eqConfiguration, true);
    tabbedComponent->addTab(translate("CLIP"), Colours::lightgrey, clipConfiguration, true);
    tabbedComponent->addTab(translate("FX"), Colours::lightgrey, effectConfiguration, true);
    
    tabbedComponent->setTabBarDepth(25);
    
    tabbedComponent->setCurrentTabIndex(OrionGlobalTabIndex);
    
    OrionGlobalTabIndex = tabbedComponent->getCurrentTabIndex();
    
//    tabbedComponent->setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
    

    for (int i=0;i < tabbedComponent->getNumTabs(); i++)
    {
        auto* tabButton = tabbedComponent->getTabbedButtonBar().getTabButton(i);
        tabButton->getProperties().set("tabButtonType", i);
        tabButton->setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());
        
    }
    
    addAndMakeVisible(tabbedComponent.get());

  
}

OrionTabComponent::~OrionTabComponent()
{
    
}

OrionTabButton::ButtonType OrionTabComponent::getType(String type)
{
    //String text = but.getButtonText();
    if(type =="ENV") return OrionTabButton::ButtonType::envelope;
    else if(type == "FX") return OrionTabButton::ButtonType::fx;
    else if(type == "EQ") return OrionTabButton::ButtonType::eq;
    else if(type == "CLIP") return OrionTabButton::ButtonType::clip;
    return OrionTabButton::ButtonType::envelope;
}

void OrionTabComponent::paint (Graphics& g)
{
    
    g.fillAll(Colours::black);
    g.setColour(Colours::red);
    g.fillRect(tabbedComponent->getTabbedButtonBar().getBounds());
    
}

void OrionTabComponent::resized()
{
    
    for (int i=0;i < tabbedComponent->getNumTabs(); i++)
    {
        tabbedComponent->getTabbedButtonBar().getTabButton(i)->setBounds(i * getWidth() / 4, 0, 30, 25);
    }
}
