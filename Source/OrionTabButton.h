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
    
    Image envtab_sel = ImageCache::getFromMemory(BinaryData::env_on_png, BinaryData::env_on_pngSize);
    Image envtab_off = ImageCache::getFromMemory(BinaryData::env_off_png, BinaryData::env_off_pngSize);
    Image fxtab_sel = ImageCache::getFromMemory(BinaryData::fx_on_png, BinaryData::fx_on_pngSize);
    Image fxtab_off = ImageCache::getFromMemory(BinaryData::fx_off_png, BinaryData::fx_off_pngSize);
    Image eqtab_sel = ImageCache::getFromMemory(BinaryData::eq_on_png, BinaryData::eq_on_pngSize);
    Image eqtab_off = ImageCache::getFromMemory(BinaryData::eq_off_png, BinaryData::env_off_pngSize);
    Image cliptab_sel = ImageCache::getFromMemory(BinaryData::clip_on_png, BinaryData::clip_on_pngSize);
    Image cliptab_off = ImageCache::getFromMemory(BinaryData::clip_off_png, BinaryData::clip_off_pngSize);
    Image* theone;
    
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

        switch (button)
        {
            case envelope:
                if (isdown) theone = &envtab_sel;
                else theone = &envtab_off;
                break;
            case fx:
                if (isdown) theone = &fxtab_sel;
                else theone = &fxtab_off;
                break;
            case eq:
                if (isdown) theone = &eqtab_sel;
                else theone = &eqtab_off;
                break;
            case clip:
                if (isdown) theone = &cliptab_sel;
                else theone = &cliptab_off;
                break;
        }
        
        

    };


    void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override
    {
        
       
       
        g.drawImageWithin(*theone, 0,0, button.getActiveArea().getWidth(), button.getActiveArea().getHeight(), juce::RectanglePlacement::centred);
        

    };
    
   


   






};

