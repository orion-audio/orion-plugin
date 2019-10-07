/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "OrionGlobalVars.h"
using namespace std;
//==============================================================================


//OrionSamplerSound* aaa;

OrionaudioAudioProcessorEditor::OrionaudioAudioProcessorEditor (OrionaudioAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
,kickButton("KICK"),snareButton("SNARE"),clapButton("CLAP"), percButton("PERC"), HiHatButton("HH-C"), cymbalButton("HH-O"), snapButton("CRASH")/*,instrumentTriggers{kickButton("KICK"),TextButton("SNARE"),("CLAP"),("PERC"),("HI HAT"),("CYMBAL"),("SNAP")}*/
{
    setSize (OrionGlobalWidth, OrionGlobalHeight);
    
    kickButton.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ kickButtonClicked(); };
    kickButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    kickButton.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&kickButton);
    
    snareButton.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ snareButtonClicked(); };
    snareButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    snareButton.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&snareButton);
    
    clapButton.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ clapButtonClicked(); };
    clapButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    clapButton.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&clapButton);
    
    percButton.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ percButtonClicked(); };
    percButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    percButton.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&percButton);
    
    HiHatButton.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ HiHatButtonClicked(); };
    HiHatButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    HiHatButton.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&HiHatButton);
    
    cymbalButton.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ cymbalButtonClicked(); };
    cymbalButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    cymbalButton.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&cymbalButton);
    
    snapButton.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ snapButtonClicked(); };
    snapButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    snapButton.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&snapButton);
    
    formatManager.registerBasicFormats();
    
    for (int i=0;i<7;i++)
    {
        tabComponent[i] = new OrionTabComponent(processor,i);
        //tabComponent[i]->TabSerial = i;
        //tabComponent[i]->effectConfiguration->effectSerial = i;
        //tabComponent[i]->effectConfiguration->delayGui.effectDelaySerial = i;
        //tabComponent[i]->eqConfiguration
    }
    
    //tabComponent[0]->setBounds(0, (OrionGlobalHeight/3)*2, OrionGlobalWidth, OrionGlobalHeight/3);
    //addAndMakeVisible(tabComponent[0]);
    tabComponentChanged(0);
    
}



OrionaudioAudioProcessorEditor::~OrionaudioAudioProcessorEditor()
{
}
//==============================================================================
void OrionaudioAudioProcessorEditor::tabComponentChanged(int serial)
{
    tabComponent[serial]->setBounds(0, (OrionGlobalHeight/3)*2, OrionGlobalWidth, OrionGlobalHeight/3);
    addAndMakeVisible(tabComponent[serial]);
}
//==============================================================================

void OrionaudioAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    
}

void OrionaudioAudioProcessorEditor::resized()
{
    kickButton.setBounds(OrionGlobalWidth/2 - 200, OrionGlobalHeight/2 - 225, 100, 100);//draw the open button
    snareButton.setBounds(OrionGlobalWidth/2 - 50, OrionGlobalHeight/2 - 225, 100, 100);//draw the play button
    clapButton.setBounds(OrionGlobalWidth/2 + 100, OrionGlobalHeight/2 - 225, 100, 100);//draw the open button
    percButton.setBounds(OrionGlobalWidth/2 + 250, OrionGlobalHeight/2 - 225, 100, 100);//draw the play button
    
    
    HiHatButton.setBounds(OrionGlobalWidth/2 - 125, OrionGlobalHeight/2 - 100, 100, 100);//draw the stop button
    cymbalButton.setBounds(OrionGlobalWidth/2 + 25, OrionGlobalHeight/2 - 100, 100, 100);//draw the stop button
    snapButton.setBounds(OrionGlobalWidth/2 + 175, OrionGlobalHeight/2 - 100, 100, 100);//draw the stop button
    
    
}

void OrionaudioAudioProcessorEditor::kickButtonClicked()
{
    //OrionSamplerVoice().startNote(36, 127, aaa, 100) ;
    //auto* kick = dynamic_cast<OrionSamplerVoice*> (processor.synth.getVoice(0));
    //kick->startNote(36, 127, processor.synth.getSound(0).get(), 8191);
    
    if (kickButton.isDown())
    {
        processor.synth.noteOn(1, 36, 120);
        
        tabComponent[1]->setVisible(false);
        tabComponent[2]->setVisible(false);
        tabComponent[3]->setVisible(false);
        tabComponent[4]->setVisible(false);
        tabComponent[5]->setVisible(false);
        tabComponent[6]->setVisible(false);
        
        tabComponent[0]->setVisible(true);
        tabComponentChanged(0);
        
    }/*else{processor.synth.noteOn(1, 36, 0);}*/;
    

    
}

void OrionaudioAudioProcessorEditor::snareButtonClicked()
{
    //OrionSamplerVoice().startNote(38, 127, aaa, 100) ;
    //auto* snare = dynamic_cast<OrionSamplerVoice*> (processor.synth.getVoice(1));
    //snare->startNote(38, 127, processor.synth.getSound(1).get(), 8191);
    if (snareButton.isDown())
    {
        processor.synth.noteOn(1, 38, 120);
        tabComponent[0]->setVisible(false);
        tabComponent[2]->setVisible(false);
        tabComponent[3]->setVisible(false);
        tabComponent[4]->setVisible(false);
        tabComponent[5]->setVisible(false);
        tabComponent[6]->setVisible(false);
        
        tabComponent[1]->setVisible(true);
        tabComponentChanged(1);
       
    }//else{processor.synth.noteOff(1, 38, 0, false/*没有淡出*/);};
    
    
}

void OrionaudioAudioProcessorEditor::clapButtonClicked()
{
    //OrionSamplerVoice().startNote(38, 127, aaa, 100) ;
    //auto* snare = dynamic_cast<OrionSamplerVoice*> (processor.synth.getVoice(1));
    //snare->startNote(38, 127, processor.synth.getSound(1).get(), 8191);
    if (clapButton.isDown())
    {
        processor.synth.noteOn(1, 39, 120);
        tabComponent[0]->setVisible(false);
        tabComponent[1]->setVisible(false);
        tabComponent[3]->setVisible(false);
        tabComponent[4]->setVisible(false);
        tabComponent[5]->setVisible(false);
        tabComponent[6]->setVisible(false);
        
        tabComponent[2]->setVisible(true);
        tabComponentChanged(2);
       
        
    }//else{processor.synth.noteOff(1, 39, 0, false/*没有淡出*/);};
    
    
}

void OrionaudioAudioProcessorEditor::percButtonClicked()
{
    //OrionSamplerVoice().startNote(38, 127, aaa, 100) ;
    //auto* snare = dynamic_cast<OrionSamplerVoice*> (processor.synth.getVoice(1));
    //snare->startNote(38, 127, processor.synth.getSound(1).get(), 8191);
    if (percButton.isDown())
    {
        processor.synth.noteOn(1, 41, 120);
        tabComponent[0]->setVisible(false);
        tabComponent[1]->setVisible(false);
        tabComponent[2]->setVisible(false);
        tabComponent[4]->setVisible(false);
        tabComponent[5]->setVisible(false);
        tabComponent[6]->setVisible(false);
        
        tabComponent[3]->setVisible(true);
        tabComponentChanged(3);
        
    }//else{processor.synth.noteOff(1, 41, 0, false/*没有淡出*/);};
    
    
}


void OrionaudioAudioProcessorEditor::HiHatButtonClicked()
{
    //OrionSamplerVoice().startNote(42, 127, aaa, 100) ;
    if (HiHatButton.isDown())
    {
        processor.synth.noteOn(1, 42, 120);
        tabComponent[0]->setVisible(false);
        tabComponent[1]->setVisible(false);
        tabComponent[2]->setVisible(false);
        tabComponent[3]->setVisible(false);
        tabComponent[5]->setVisible(false);
        tabComponent[6]->setVisible(false);
        
        tabComponent[4]->setVisible(true);
        tabComponentChanged(4);
        
        
    }//else{processor.synth.noteOff(1, 42, 0, false);};
    
    
    
}

void OrionaudioAudioProcessorEditor::cymbalButtonClicked()
{
    //OrionSamplerVoice().startNote(42, 127, aaa, 100) ;
    if (cymbalButton.isDown())
    {
        processor.synth.noteOn(1, 43, 120);
        tabComponent[0]->setVisible(false);
        tabComponent[1]->setVisible(false);
        tabComponent[2]->setVisible(false);
        tabComponent[3]->setVisible(false);
        tabComponent[4]->setVisible(false);
        tabComponent[6]->setVisible(false);
        
        tabComponent[5]->setVisible(true);
        tabComponentChanged(5);
       
    }//else{processor.synth.noteOff(1, 43, 0, false);};
    
    
}

void OrionaudioAudioProcessorEditor::snapButtonClicked()
{
    //OrionSamplerVoice().startNote(42, 127, aaa, 100) ;
    if (snapButton.isDown())
    {
        processor.synth.noteOn(1, 46, 120);
        tabComponent[0]->setVisible(false);
        tabComponent[1]->setVisible(false);
        tabComponent[2]->setVisible(false);
        tabComponent[3]->setVisible(false);
        tabComponent[4]->setVisible(false);
        tabComponent[5]->setVisible(false);
        
        tabComponent[6]->setVisible(true);
        tabComponentChanged(6);
        
    }//else{processor.synth.noteOff(1, 46, 0, false);};
    
}





