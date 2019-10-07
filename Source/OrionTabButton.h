/*
  ==============================================================================

    OrionTabButton.h
    Created: 21 Jul 2019 11:25:48am
    Author:  Lily H

  ==============================================================================
*/

#pragma once
class OrionTabButton    : public LookAndFeel_V2
{
private:
    File skinfolder;
    String ENVon = "env_selected.png";
    String FXon = "fx_selected.png";
    String EQon = "EQ_on.png";
    String CLIPon = "clip_selected.png";
    String ENV = "env_off.png";
    String FX = "fx_off.png";
    String EQ = "eq_off.png";
    String CLIP = "clip_off.png";
    String filename;
    File* file;
    
public:
    enum ButtonType
    {
        envelope=0,
        fx,
        eq,
        clip
    };
    int state = 0;
    OrionTabButton(ButtonType button, bool isdown)
    {
        skinfolder = File::getSpecialLocation(File::globalApplicationsDirectory).getChildFile("Orion").getChildFile("OrionSampler").getChildFile("OrionSampler").getChildFile("Contents").getChildFile("Resources").getChildFile("skin").getChildFile("pictures");
        
        //file = new File("/Users/lilyh/Downloads/TBOff.png");
        switch (button)
        {
            case envelope:
                if (isdown) filename = ENVon;
                else filename = ENV;
                break;
            case fx:
                if (isdown) filename = FXon;
                else filename = FX;
                break;
            case eq:
                if (isdown) filename = EQon;
                else filename = EQ;
                break;
            case clip:
                if (isdown) filename = CLIPon;
                else filename = CLIP;
                break;
        }
        
        
        file = new File(skinfolder.getChildFile(filename));
    };


    void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override
    {
        
        g.drawImageWithin(ImageCache::getFromFile(*file), button.getActiveArea().getX(),button.getActiveArea().getY(), button.getActiveArea().getWidth(), button.getActiveArea().getHeight(), juce::RectanglePlacement::centred);

    };
    
   


   






};

