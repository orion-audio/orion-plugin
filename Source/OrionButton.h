/*
  ==============================================================================

    OrionNavigator.h
    Created: 28 Jul 2019 10:32:05am
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include "PluginEditor.h"

class OrionButton    : public DrawableButton,
                       public FileDragAndDropTarget
{
    private:
    OrionaudioAudioProcessor& processor;
    //OrionaudioAudioProcessorEditor& editor;
    String name;
    int midi;
    public:
    int index;
   // using DrawableButton::DrawableButton;
    OrionButton (OrionaudioAudioProcessor& p, /*OrionaudioAudioProcessorEditor& e,*/ const String& buttonName,
                 ButtonStyle buttonStyle): DrawableButton(buttonName, buttonStyle), name(buttonName),processor(p)
    {
        if(buttonName == "KICK")
        {
            index = 0;
            midi = 36;
        }
        else if(buttonName == "SNARE")
        {
            index = 1;
            midi = 38;
        }
        else if (buttonName == "CLAP")
        {
            index = 2;
            midi = 39;
        }
        else if (buttonName == "PERC")
        {
            index = 3;
            midi = 41;
        }
        else if (buttonName == "HH-C")
        {
            index = 4;
            midi = 42;
        }
        else if(buttonName == "HH-O")
        {
            index = 5;
            midi = 43;
        }
        else if(buttonName == "CRASH")
        {
            index = 6;
            midi = 46;
        }
    };
    
    ~OrionButton() override{};
   
   bool isInterestedInFileDrag (const StringArray &files) override
    {
        return true;
    }
    
     void fileDragEnter (const StringArray &files, int x, int y) override
    {
        this->setState(Button::ButtonState::buttonOver);
    }
    
    
     void filesDropped (const StringArray &files, int x, int y) override
    {
        //this->setState(Button::ButtonState::buttonDown);
        
        /*
        std::cout<<"x: ,y: "<<x<<" "<<y<<"\n";
        if(abs(x)<5 and abs(y)<5)
        {
            
        }
         */
        
        //std::cout<<"what file "<<files[0]<<"\n";
      
        processor.synth.changeSamples(index,files[0],midi);
       
      
        index = 6;
       
        
        
    }
    


};
