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
OrionTabComponent::OrionTabComponent(OrionaudioAudioProcessor& p, int serial): processor(p), TabbedComponent(TabbedButtonBar::Orientation::TabsAtBottom)
{
         
    TabSerial = serial;
    
    //setOrientation(TabbedButtonBar::TabsAtBottom);
    //TabbedButtonBar->setVisible(false);
    
    effectConfiguration.reset(new OrionEffectsConfiguration(p,serial));
    eqConfiguration.reset(new OrionEQConfiguration(p,serial));
    envConfiguration.reset(new OrionEnvConfiguration(p,serial));
    clipConfiguration.reset(new OrionClipConfiguration(p));
    
    addTab(translate("EQ"),   Colours::lightgrey, eqConfiguration.get(), false);
    addTab(translate("CLIP"), Colours::lightgrey, clipConfiguration.get(), false);
    addTab(translate("ENV"),  Colours::lightgrey, envConfiguration.get(), false);
    addTab(translate("FX"),   Colours::lightgrey, effectConfiguration.get(), false);
    
    setTabBarDepth(30);
    setOutline(1);
    setCurrentTabIndex(OrionGlobalTabIndex);
    OrionGlobalTabIndex = getCurrentTabIndex();
    
    for (int i=0;i < getNumTabs(); i++)
    {
        auto* tabButton = getTabbedButtonBar().getTabButton(i);
        tabButton->getProperties().set("tabButtonType", i);
        tabButton->setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());
    }
    
  
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
    g.setColour (Colours::darkgrey);
    //g.drawHorizontalLine(0, 0, getWidth());
    g.drawLine(0.0f, 0.0f,getWidth(), 0.0f, 0.5f);
    //g.drawRect(0, 0, getWidth(), getHeight());


}

void OrionTabComponent::resized()
{
    
    TabbedComponent::resized();
    
    float TabBarDepth = getHeight() * .15;
    setTabBarDepth(TabBarDepth);
    getTabbedButtonBar().setBounds(0, getHeight() - TabBarDepth, getWidth(), TabBarDepth);
    
    double uniteW = getWidth()/30;
    
    for (int i = 0; i < getNumTabs(); i++)
    {
        getTabbedButtonBar().getTabButton(i)->setBounds( 6 * uniteW + i * 5 * uniteW, 0, 2 * uniteW, TabBarDepth);
    }
    

}
