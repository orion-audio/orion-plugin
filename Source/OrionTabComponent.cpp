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
  
    //std::cout<<"tabs "<<TabSerial<<"\n";//!!!!!!!!!!
   
    //effectConfiguration->effectSerial=TabSerial;
    
    tabbedComponent->addTab(translate("EQ"), Colours::lightgrey, eqConfiguration, true);
    tabbedComponent->addTab(translate("CLIP"), Colours::lightgrey, clipConfiguration, true);
    tabbedComponent->addTab(translate("ENV"), Colours::lightgrey, envConfiguration, true);
    tabbedComponent->addTab(translate("FX"), Colours::lightgrey, effectConfiguration, true);
    
    tabbedComponent->setTabBarDepth(25);
    
    tabbedComponent->setCurrentTabIndex(OrionGlobalTabIndex);
    
    OrionGlobalTabIndex = tabbedComponent->getCurrentTabIndex();
    
    tabbedComponent->setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
    

    for (int i=0;i < tabbedComponent->getNumTabs(); i++)
    {
        tabbedComponent->getTabbedButtonBar().getTabButton(i)->setBounds(OrionGlobalWidth/4*i, 0, 30, 25);
    }
    

    addAndMakeVisible(tabbedComponent.get());
    
  
}

OrionTabComponent::~OrionTabComponent()
{
    
}

OrionTabButton::ButtonType OrionTabComponent::gettype(String type)
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
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    

    for (int i=0; i < tabbedComponent->getNumTabs(); i++)
    {
        auto* temp = tabbedComponent->getTabbedButtonBar().getTabButton(i);
        temp->setBounds(OrionGlobalWidth/4*i, 0, 100, 25);
       
        auto* but = tabbedComponent->getTabbedButtonBar().getTabButton(i);
        
        OrionTabButton* custablook = new OrionTabButton(gettype(but->getButtonText()), tabbedComponent->getTabbedButtonBar().getTabButton(i)->isFrontTab());
        
        but->setLookAndFeel(custablook);
        
    

    }
  
    addAndMakeVisible(tabbedComponent.get());
    
    g.fillAll(Colours::black);
    
}

void OrionTabComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    tabIndex = tabbedComponent->getCurrentTabIndex();
    tabbedComponent->setCurrentTabIndex(tabIndex);
    for (int i=0;i < tabbedComponent->getNumTabs(); i++)
    {
        tabbedComponent->getTabbedButtonBar().getTabButton(i)->setBounds(OrionGlobalWidth/4*i, 0, 30, 25);
    }
 
    
}
