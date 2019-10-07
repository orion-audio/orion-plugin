/*
  ==============================================================================

    OrionFileFilter.h
    Created: 9 Aug 2019 4:46:20pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
class Orionlist    : public ListBoxModel
{
    private:
    int numrows=6;
    public:
    
    bool activity[5];
    Orionlist()
    {
        for (int i = 0; i<numrows;i++)
        {
            activity[i]=false;
        }
    };
    
    ~Orionlist() override {};
    
    int getNumRows () override
    {
        return numrows;
    };
    
    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override
    {
        std::cout<<"what row "<<rowNumber<<"\n";
        int y =  75 + rowNumber * height;
        String text;
        Rectangle<int> rect (0, y, width, height);
        g.drawRect(rect,1);
       // g.drawRect(0,y,width,height,1);
        switch (rowNumber)
        {
            case 0:
                text = "Applications";
                break;
            case 1:
                text = "Desktop";
                break;
            case 2:
                text = "Downloads";
                break;
            case 3:
                text = "Music";
                break;
            case 4:
                text = "Documents";
                break;
            case 5:
                text = "Home";
                break;
         
        }
        g.setColour(Colours::white);
        g.setOpacity(0.6);
        if(rowIsSelected)
        {
            g.setOpacity(0.3);
        }
        g.drawFittedText(text, rect, Justification(33), 1, 0.0f);
        
        
    };
    
    /*
    Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override
    {
        std::cout<<"is it refreshing \n";
        if(existingComponentToUpdate != nullptr)
        {
            std::cout<<"so? \n";
        }
        return nullptr;
    };
    
    */
    void listBoxItemClicked (int row, const MouseEvent &) override
    {
        for(int i = 0; i < numrows; i++)
        {
            activity[i] = false;
        }
        activity[row] = true;
    };
    
    

};
