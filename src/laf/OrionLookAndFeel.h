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
#include "SequencerComponent.h"

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

class OrionLookAndFeel : public LookAndFeel_V4, public SequencerComponent::LookAndFeelMethods
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
    
    void drawLinearSlider (Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider& slider) override;
    
    void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override;
    
    virtual Font getLabelFont (Label &) override;
    virtual void drawComboBox(Graphics &, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &) override;
    
    virtual void drawNoteBox(Graphics &g, SequencerComponent& s, Rectangle<float> bounds, bool isActive) override;
    
private:
    std::array<std::unique_ptr<ImagePair>, 4> tabButtonImages;
    
};
