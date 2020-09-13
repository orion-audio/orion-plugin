/*
  ==============================================================================

    BarButton.h
    Created: 23 Aug 2020 12:59:03pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BarButton : public Button
{
public:
    BarButton(int num) : Button(String("")), barNum(num)
    {
            
    }

    ~BarButton()
    {
    }

    virtual void paintButton (Graphics& g,
                              bool shouldDrawButtonAsHighlighted,
                              bool shouldDrawButtonAsDown) override
    {

        if (selected) {
            g.setColour(Colour(0xFF36FEE2));
            g.fillRoundedRectangle(getLocalBounds().toFloat(), 8.f);
            g.setColour(Colours::black);
            g.drawFittedText(String(barNum), getLocalBounds(), Justification::centred, 1);
        }
        else {
            g.setColour(Colour(0xFF313131));
            g.fillRoundedRectangle(getLocalBounds().toFloat(), 8.f);
            g.setColour(Colours::white);
            g.drawFittedText(String(barNum), getLocalBounds(), Justification::centred, 1);

        }

        g.setColour(Colours::white);
        if (active) g.drawRect(getLocalBounds(), 5.f);

    }
    
    virtual void clicked(const ModifierKeys &modifiers) override {
        Button::clicked(modifiers);
        if (modifiers.isCommandDown()) {
            active = !active;
            if (onActiveChange != nullptr) {
                onActiveChange(barNum);
            }
        }
        else {
            if (onSelection != nullptr) onSelection(barNum);
            
        }

    }

    int getBarNum() { return barNum; };
    
    bool getActive() { return active; };
    void setActive(bool a) {
        active = a;
        repaint();
    };
    
    bool getSelected() { return selected; };
    void setSelected(bool s) {
        selected = s;
        repaint();
    };
    
    std::function<void(int)> onSelection;
    std::function<void(int)> onActiveChange;
private:
    bool active = false;
    bool selected = false;
    int barNum;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BarButton)
};
