/*
  ==============================================================================

    OrionLookAndFeel.cpp
    Created: 29 Oct 2019 12:52:09pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "OrionLookAndFeel.h"

OrionLookAndFeel::OrionLookAndFeel()
{
    
    Image on = ImageCache::getFromMemory(BinaryData::env_on_png, BinaryData::env_on_pngSize);
    Image off = ImageCache::getFromMemory(BinaryData::env_off_png, BinaryData::env_off_pngSize);
    tabButtonImages[TabButtonType::envelope].reset(new ImagePair(on, off));

    on = ImageCache::getFromMemory(BinaryData::fx_on_png, BinaryData::fx_on_pngSize);
    off = ImageCache::getFromMemory(BinaryData::fx_off_png, BinaryData::fx_off_pngSize);
    tabButtonImages[TabButtonType::fx].reset(new ImagePair(on, off));

    on = ImageCache::getFromMemory(BinaryData::eq_on_png, BinaryData::eq_on_pngSize);
    off = ImageCache::getFromMemory(BinaryData::eq_off_png, BinaryData::env_off_pngSize);
    tabButtonImages[TabButtonType::eq].reset(new ImagePair(on, off));
    

    on = ImageCache::getFromMemory(BinaryData::clip_on_png, BinaryData::clip_on_pngSize);
    off = ImageCache::getFromMemory(BinaryData::clip_off_png, BinaryData::clip_off_pngSize);
    tabButtonImages[TabButtonType::clip].reset(new ImagePair(on, off));

}

void OrionLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    float diameter = jmin(width,height);//compare two values, get min value
    float radius = diameter/2;
    float centreX = x + width/2;// get extact centre x
    float centreY =  y + height/2;// get extact centre y
    float rx = centreX - radius;
    float ry = centreY - radius;
    float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
    float pointerThickness = 4.0;
    
    //std::cout << rotaryStartAngle << " " << rotaryEndAngle << std::endl;
    Rectangle<float> dialArea (rx, ry, diameter, diameter);
    
    
    /* Draw Background */
    g.setColour(Colours::darkgrey);
    g.fillEllipse(dialArea);
    
    
    /* Draw Center */
    //g.setColour(Colours::black);
    //g.fillEllipse(centreX - (pointerThickness/1.5), centreY - (pointerThickness/1.5), pointerThickness*1.5,pointerThickness*1.5);
    
    

    /* */
    Path dialTick;
    dialTick.addRoundedRectangle(-rx - (pointerThickness/2), -radius, pointerThickness, radius, radius/9);
    
    g.setColour(Colours::black);
    g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centreX, centreY));
    
    
    /* Draw Outline*/
    g.setColour(Colours::slategrey);
    g.setOpacity(0.6);
    g.drawEllipse(rx, ry, diameter, diameter, 2.0f/*Pixl*/);

}

void OrionLookAndFeel::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
    NamedValueSet properties = button.getProperties();
    if (properties.contains("tabButtonType"))
    {
        int type = properties["tabButtonType"];
        if (isMouseDown)
              g.drawImageWithin(tabButtonImages[type]->onImage, 0,0, button.getActiveArea().getWidth(), button.getActiveArea().getHeight(), juce::RectanglePlacement::centred);
        else
            g.drawImageWithin(tabButtonImages[type]->offImage, 0,0, button.getActiveArea().getWidth(), button.getActiveArea().getHeight(), juce::RectanglePlacement::centred);
    }
    else
        jassertfalse;

};

