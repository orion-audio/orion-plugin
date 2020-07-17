/*
  ==============================================================================

    DigitTransverter.h
    Created: 15 Jul 2020 1:57:34pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once


String DigitTransverter(double inputValue)
{
    double a = inputValue;
    float b = (int)(a * 100 + .5);
    float c =  (float)b / 100;
    String d = String(c);
    if(d == "0")
    {
        d = "0.00";
    }
    else if(d == "1")
    {
        d = "1.00";
    }

    return d;
}
