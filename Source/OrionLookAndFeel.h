/*
  ==============================================================================

    OrionLookAndFeel.h
    Created: 29 Oct 2019 12:52:09pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <array>

struct ImagePair
{
    ImagePair(Image on, Image off)
    {
        onImage = on;
        offImage = off;
    }
    
    Image onImage;
    Image offImage;
};

class OrionLookAndFeel : public LookAndFeel_V4
{
public:
//    static String tabButtonProperty {"tabButtonType"};
    
    enum TabButtonType
    {
        eq=0,
        clip,
        envelope,
        fx
    };
    
    OrionLookAndFeel();

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
    
    void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override;
    
private:
    std::array<std::unique_ptr<ImagePair>, 4> tabButtonImages;
    
};
