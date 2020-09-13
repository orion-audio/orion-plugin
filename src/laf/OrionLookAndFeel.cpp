/*
  ==============================================================================

    OrionLookAndFeel.cpp
    Created: 29 Oct 2019 12:52:09pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "OrionLookAndFeel.h"
#include "AutoLabel.h"

OrionLookAndFeel::OrionLookAndFeel()
{
    //Image on = ImageCache::getFromMemory(BinaryData::ENVButtonOn_png, BinaryData::ENVButtonOn_pngSize);
    //Image off = ImageCache::getFromMemory(BinaryData::ENVButtonOff_png, BinaryData::ENVButtonOff_pngSize);
    Image on = ImageCache::getFromMemory(BinaryData::InvisibleButtonBackground_png, BinaryData::InvisibleButtonBackground_pngSize);
    Image off = ImageCache::getFromMemory(BinaryData::InvisibleButtonBackground_png, BinaryData::InvisibleButtonBackground_pngSize);
    tabButtonImages[TabButtonType::envelope].reset(new ImagePair(on, off));

    //on = ImageCache::getFromMemory(BinaryData::FXButtonOn_png, BinaryData::FXButtonOn_pngSize);
    //off = ImageCache::getFromMemory(BinaryData::FXButtonOff_png, BinaryData::FXButtonOff_pngSize);
    tabButtonImages[TabButtonType::fx].reset(new ImagePair(on, off));

    //on = ImageCache::getFromMemory(BinaryData::EQButtonOn_png, BinaryData::EQButtonOn_pngSize);
    //off = ImageCache::getFromMemory(BinaryData::EQButtonOff_png, BinaryData::EQButtonOff_pngSize);
    tabButtonImages[TabButtonType::eq].reset(new ImagePair(on, off));
    

    //on = ImageCache::getFromMemory(BinaryData::ClipButtonOn_png, BinaryData::ClipButtonOn_pngSize);
    //off = ImageCache::getFromMemory(BinaryData::ClipButtonOff_png, BinaryData::ClipButtonOff_pngSize);
    tabButtonImages[TabButtonType::clip].reset(new ImagePair(on, off));

}

void OrionLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto radius = jmin (width / 2, height / 2) - 4.0f;
    auto centreX = x + width  * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    // fill
    g.setColour (Colours::darkgrey);
    g.setOpacity(0.7);
    g.fillEllipse (rx, ry, rw, rw);
    // outline
    g.setColour (Colours::black);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);

    Path p;
    auto pointerLength = radius;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));

    // pointer
    g.setColour (Colours::black);
    g.fillPath (p);
}


void OrionLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                       float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
                                       const Slider::SliderStyle style, Slider& slider)
{
    if (slider.isBar())
    {
        g.setColour (slider.findColour (Slider::trackColourId));
        g.fillRect (slider.isHorizontal() ? Rectangle<float> (static_cast<float> (x), y + 0.5f, sliderPos - x, height - 1.0f)
                                          : Rectangle<float> (x + 0.5f, sliderPos, width - 1.0f, y + (height - sliderPos)));
    }
    else
    {
        auto isTwoVal   = (style == Slider::SliderStyle::TwoValueVertical   || style == Slider::SliderStyle::TwoValueHorizontal);
        auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

        //std::cout<<(style)<<std::endl;
        
        auto trackWidth = jmin (6.0f, slider.isHorizontal() ? height * 0.05f/* Horizontal track height. init value: 0.25 */ : width * 0.05f/* Vertial track width. init value: 0.25 */);

        Point<float> startPoint (slider.isHorizontal() ? x : x + width * 0.5f,
                                 slider.isHorizontal() ? y + height * 0.5f : height + y);

        Point<float> endPoint (slider.isHorizontal() ? width + x : startPoint.x,
                               slider.isHorizontal() ? startPoint.y : y);

        Path backgroundTrack;
        backgroundTrack.startNewSubPath (startPoint);
        backgroundTrack.lineTo (endPoint);
        g.setColour (slider.findColour (Slider::backgroundColourId));
        g.strokePath (backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        Path valueTrack;
        Point<float> minPoint, maxPoint, thumbPoint;

        if (isTwoVal || isThreeVal)
        {
            minPoint = { slider.isHorizontal() ? minSliderPos : width * 0.5f,
                         slider.isHorizontal() ? height * 0.5f : minSliderPos };

            if (isThreeVal)
                thumbPoint = { slider.isHorizontal() ? sliderPos : width * 0.5f,
                               slider.isHorizontal() ? height * 0.5f : sliderPos };

            maxPoint = { slider.isHorizontal() ? maxSliderPos : width * 0.5f,
                         slider.isHorizontal() ? height * 0.5f : maxSliderPos };
        }
        else
        {
            auto kx = slider.isHorizontal() ? sliderPos : (x + width * 0.5f);
            auto ky = slider.isHorizontal() ? (y + height * 0.5f) : sliderPos;

            minPoint = startPoint;
            maxPoint = { kx, ky };
        }

        auto thumbWidth = getSliderThumbRadius (slider);

        valueTrack.startNewSubPath (minPoint);
        valueTrack.lineTo (isThreeVal ? thumbPoint : maxPoint);
        g.setColour (slider.findColour (Slider::trackColourId));
        g.strokePath (valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        if (! isTwoVal)
        {
            g.setColour (slider.findColour (Slider::thumbColourId));
            g.fillEllipse (Rectangle<float> (static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre (isThreeVal ? thumbPoint : maxPoint));
        }

        if (isTwoVal || isThreeVal)
        {
            auto sr = jmin (trackWidth, (slider.isHorizontal() ? height : width) * 0.4f);
            auto pointerColour = slider.findColour (Slider::thumbColourId);

            if (slider.isHorizontal())
            {
                drawPointer (g, minSliderPos - sr,
                             jmax (0.0f, y + height * 0.5f - trackWidth * 2.0f),
                             trackWidth * 2.0f, pointerColour, 2);

                drawPointer (g, maxSliderPos - trackWidth,
                             jmin (y + height - trackWidth * 2.0f, y + height * 0.5f),
                             trackWidth * 2.0f, pointerColour, 4);
            }
            else
            {
                drawPointer (g, jmax (0.0f, x + width * 0.5f - trackWidth * 2.0f),
                             minSliderPos - trackWidth,
                             trackWidth * 2.0f, pointerColour, 1);

                drawPointer (g, jmin (x + width - trackWidth * 2.0f, x + width * 0.5f), maxSliderPos - sr,
                             trackWidth * 2.0f, pointerColour, 3);
            }
        }
    }
}




void OrionLookAndFeel::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
    NamedValueSet properties = button.getProperties();
    if (properties.contains("tabButtonType"))
    {
        int type = properties["tabButtonType"];
        if (button.isDown() || button.getToggleState())
              g.drawImage(tabButtonImages[type]->onImage, button.getLocalBounds().toFloat(), juce::RectanglePlacement::centred);
        else
            g.drawImage(tabButtonImages[type]->offImage, button.getLocalBounds().toFloat(), juce::RectanglePlacement::centred);
    }
    else
        jassertfalse;

};

Font OrionLookAndFeel::getLabelFont (Label &l)
{
    if (l.getProperties().contains(AutoLabel::propertyName))
        return Font();
    
    Font f;
    f.setHeight(l.getHeight() * .5);
    return f;
}

void OrionLookAndFeel::drawComboBox(juce::Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox &combo) {
    
    if (combo.getProperties().contains("CHANNEL_COMBO") || combo.getProperties().contains("SUBDIVISION_COMBO")) {
        g.setColour(Colour(0xFF313131));
        g.fillRoundedRectangle(combo.getLocalBounds().toFloat(), 8.f);
        return;
    }
    g.setColour(Colour(ThemeColors::backgroundColor));
    g.fillRoundedRectangle(combo.getLocalBounds().toFloat(), 2.f);
   
    // DRAW ARROW
    Path arrow;
    Rectangle<float> arrowBounds(combo.getRight() - combo.getHeight() * 1.25, 0, combo.getHeight() / 2, combo.getHeight() / 4);
    arrowBounds.translate(0, arrowBounds.getHeight() * 1.5);
    g.setColour(Colours::white);
    arrow.startNewSubPath(arrowBounds.getX(), arrowBounds.getY());
    arrow.lineTo(arrowBounds.getCentreX(), arrowBounds.getBottom());
    arrow.lineTo(arrowBounds.getRight(), arrowBounds.getY());
    g.strokePath(arrow, PathStrokeType(1.f));
}

void OrionLookAndFeel::drawNoteBox(juce::Graphics &g, SequencerComponent &s, Rectangle<float> bounds, bool isActive, bool isPlaying) { 
    float radius = std::min(bounds.getWidth(), bounds.getHeight());
    auto newBounds = bounds;
    newBounds = newBounds.withSizeKeepingCentre(radius, radius);
    g.setColour(Colours::white);
    if (isActive)
        g.fillEllipse(newBounds);
    else
        g.drawEllipse(newBounds.withSizeKeepingCentre(radius - 5, radius - 5), 5.f);
    
}

void OrionLookAndFeel::positionComboBoxText(ComboBox &combo,Label &label) {
    label.setBounds(combo.getLocalBounds());
    if (combo.getProperties().contains("CHANNEL_COMBO") || combo.getProperties().contains("SUBDIVISION_COMBO")) {
        label.setJustificationType(Justification::centred);
    }
}

