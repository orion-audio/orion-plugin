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
    tabbedComponent = new TabbedComponent(TabbedButtonBar::TabsAtTop);
    TabSerial = serial;
    
    effectConfiguration = new OrionEffectsConfiguration(p,serial);
    eqConfiguration = new OrionEQConfiguration(p);
    envConfiguration = new OrionEnvConfiguration(p);
    clipConfiguration = new OrionClipConfiguration(p);
  
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
    
    addAndMakeVisible(tabbedComponent);
    
    //effectConfiguration = new OrionEffectsConfiguration(p);
    
}

OrionTabComponent::~OrionTabComponent()
{
    
}

void OrionTabComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

//    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
//
//    g.setColour (Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//    g.setColour (Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("OrionTabComponent", getLocalBounds(),
//                Justification::centred, true);   // draw some placeholder text
    g.fillAll(Colour(0xff323e44));
}

void OrionTabComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tabIndex = tabbedComponent->getCurrentTabIndex();
    tabbedComponent->setCurrentTabIndex(tabIndex);
    
}
