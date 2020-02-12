/*
  ==============================================================================

    OrionRotarySlider.h
    Created: 24 Jul 2019 5:40:34pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once
class OrionRotarySlider : public LookAndFeel_V4
{
    //    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
    //                                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    //    {
    //        const float radius = jmin (width / 2, height / 2) - 2.0f;
    //        const float centreX = x + width * 0.5f;
    //        const float centreY = y + height * 0.5f;
    //        const float rx = centreX - radius;
    //        const float ry = centreY - radius;
    //        const float rw = radius * 2.0f;
    //        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    //        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
    //        if (radius > 12.0f)
    //        {
    //            if (slider.isEnabled())
    //                g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
    //            else
    //                g.setColour (Colour (0x80808080));
    //            const float thickness = 0.7f;
    //            {
    //                Path filledArc;
    //                filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
    //                g.fillPath (filledArc);
    //            }
    //            {
    //                const float innerRadius = radius * 0.2f;
    //                Path p;
    //                p.addTriangle (-innerRadius, 0.0f,
    //                               0.0f, -radius * thickness * 1.1f,
    //                               innerRadius, 0.0f);
    //                p.addEllipse (-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);
    //                g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
    //            }
    //            if (slider.isEnabled())
    //                g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
    //            else
    //                g.setColour (Colour (0x80808080));
    //            Path outlineArc;
    //            outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
    //            outlineArc.closeSubPath();
    //            g.strokePath (outlineArc, PathStrokeType (slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));
    //        }
    //        else
    //        {
    //            if (slider.isEnabled())
    //                g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
    //            else
    //                g.setColour (Colour (0x80808080));
    //            Path p;
    //            p.addEllipse (-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
    //            PathStrokeType (rw * 0.1f).createStrokedPath (p, p);
    //            p.addLineSegment (Line<float> (0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);
    //            g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
    //        }
    //    }
    
    
    
    
    
    
    
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
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
    
};
