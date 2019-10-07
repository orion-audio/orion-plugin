/*
  ==============================================================================

    OrionBrowser.h
    Created: 24 Jul 2019 5:30:15pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
class OrionBrowser    : public FileBrowserComponent::LookAndFeelMethods//LookAndFeel_V2
{
    private:
    
    public:
    OrionBrowser()
    {
        
    };
    //what goes inside the file browser window
    void drawFileBrowserRow (Graphics& g, int width, int height,
                             const File&, const String& filename, Image* icon,
                             const String& fileSizeDescription,
                             const String& fileTimeDescription,
                             bool isDirectory, bool isItemSelected,
                             int /*itemIndex*/, DirectoryContentsDisplayComponent& dcc) override //this is for drawing those browsers, should set to be their background image
    {
        
        auto fileListComp = dynamic_cast<Component*> (&dcc);
        /*
        if (isItemSelected)
            g.fillAll (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightColourId)
                       : findColour (DirectoryContentsDisplayComponent::highlightColourId));
        */
        const int x = 32;
        g.setColour (Colours::black);
        
        if (icon != nullptr && icon->isValid())
        {
            g.drawImageWithin (*icon, 2, 2, x - 4, height - 4,
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                               false);
        }
        else
        {
            if (auto* d = isDirectory ? getDefaultFolderImage()
                : getDefaultDocumentFileImage())
                d->drawWithin (g, Rectangle<float> (2.0f, 2.0f, x - 4.0f, height - 4.0f),
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
        }
        /*
        if (isItemSelected)
            g.setColour (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightedTextColourId)
                         : findColour (DirectoryContentsDisplayComponent::highlightedTextColourId));
        else
            g.setColour (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::textColourId)
                         : findColour (DirectoryContentsDisplayComponent::textColourId));
        */
        g.setFont (height * 0.7f);
        
        if (width > 450 && ! isDirectory)
        {
            auto sizeX = roundToInt (width * 0.7f);
            auto dateX = roundToInt (width * 0.8f);
            
            g.drawFittedText (filename,
                              x, 0, sizeX - x, height,
                              Justification::centredLeft, 1);
            
            g.setFont (height * 0.5f);
            g.setColour (Colours::darkgrey);
            
            if (! isDirectory)
            {
                g.drawFittedText (fileSizeDescription,
                                  sizeX, 0, dateX - sizeX - 8, height,
                                  Justification::centredRight, 1);
                
                g.drawFittedText (fileTimeDescription,
                                  dateX, 0, width - 8 - dateX, height,
                                  Justification::centredRight, 1);
            }
        }
        else
        {
            g.drawFittedText (filename,
                              x, 0, width - x, height,
                              Justification::centredLeft, 1);
            
        }
         
    };
    
    AttributedString createFileChooserHeaderText (const String& title,
                                                                  const String& instructions) override
    {
        /*
        AttributedString s;
        s.setJustification (Justification::centred);
        
        auto colour = findColour (FileChooserDialogBox::titleTextColourId);
        s.append (title + "\n\n", Font (17.0f, Font::bold), colour);
        s.append (instructions, Font (14.0f), colour);
        
        return s;
         */
        
    };

    
    Button* createFileBrowserGoUpButton() override
    {
        /*
        auto goUpButton = new DrawableButton ("up", DrawableButton::ImageOnButtonBackground);
        
        Path arrowPath;
        arrowPath.addArrow ({ 50.0f, 100.0f, 50.0f, 0.0f }, 40.0f, 100.0f, 50.0f);
        
        DrawablePath arrowImage;
        arrowImage.setFill (Colours::black.withAlpha (0.4f));
        arrowImage.setPath (arrowPath);
        
        goUpButton->setImages (&arrowImage);
        
        return goUpButton;
         */
        return nullptr;
    };

    
    void layoutFileBrowserComponent (FileBrowserComponent& browserComp,
                                     DirectoryContentsDisplayComponent* fileListComponent,
                                     FilePreviewComponent* previewComp,//lower box
                                     ComboBox* currentPathBox,//upper box
                                     TextEditor* filenameBox,
                                     Button* goUpButton) override
    {
        /*
        const int x = 0;
        auto w = browserComp.getWidth() - x - x;
        
        if (previewComp != nullptr)
        {
            auto previewWidth = w ;
            previewComp->setBounds (x + w - previewWidth, 0, previewWidth, 300);//browserComp.getHeight());
            
            w -= previewWidth + 4;
        }
        
        int y = 0;
        
        const int navHeight = 300;
        const int upButtonWidth = 50;
        auto bottomSectionHeight = navHeight + 8;
        
        currentPathBox->setBounds (x, y, w - upButtonWidth - 6, navHeight);//upper box
        // goUpButton->setBounds (x + w - upButtonWidth, y, upButtonWidth, controlsHeight);
        
        y += navHeight + 4;
        
        if (auto listAsComp = dynamic_cast<Component*> (fileListComponent))
        {
            listAsComp->setBounds (x, y, w, browserComp.getHeight() - y - bottomSectionHeight);
            y = listAsComp->getBottom() + 4;
        }
        
        //filenameBox->setBounds (x + 50, y, w - 50, navHeight);
         */
        currentPathBox->setBounds (0, 0, 250, 300);
        if (previewComp != nullptr)
        {
            previewComp->setBounds (350, 0, 250, 300);//browserComp.getHeight());
        }
    };
    

};
