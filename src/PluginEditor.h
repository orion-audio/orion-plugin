

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OrionTabComponent.h"
//#include "OrionBrowser.h"
#include "OrionButton.h"
#include "Orionlist.h"
#include "OrionFileBrowser.h"
#include "OrionFileTreeComponent.h"
#include "DraggableFileBrowserComponent.h"
#include "ThresholdMeter.h"
#include "CircularMeter.h"
#include <array>
#include "OrionResizableCornerComponent.h"
#include "ResizableContainer.h"
#include "TabComponentHolder.h"
#include "OrionMenuBar.h"
#include "PrimaryPaneComponent.h"
#include "SidePanelComponent.h"
#include "ArrangementWindowComponent.h"

//#include "TabComponentHolder.h"
#include "DropdownTable.h"

//==============================================================================
/**
 */

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class OrionaudioAudioProcessorEditor : public AudioProcessorEditor, public ResizableContainer
{
public:
    
    OrionaudioAudioProcessorEditor (OrionaudioAudioProcessor&);
    ~OrionaudioAudioProcessorEditor();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void tabComponentChanged(int serial);
    
    //void updateDropDownState(bool newState);
    
    void updateDropDownEQState(bool newState);
    void updateDropDownClipState(bool newState);
    void updateDropDownENVState(bool newState);
    void updateDropDownFXState(bool newState);
    
    void updateResizeViewState(bool newState);
    
    std::unique_ptr<AudioFormatReaderSource> playSource;
    
    void setDefaultSize();
    
    void drumButtonClicked(int midiNote, int tabIndex, bool isDown);

    void toggleArrangmentWindow(bool windowVisible);
    
    bool getDropdownVisible();
    
    ComponentBoundsConstrainer constrainer;
private:
    
    OrionaudioAudioProcessor& processor;
    
    std::unique_ptr<OrionResizableCornerComponent<OrionaudioAudioProcessorEditor> > cornerComponent;
    
    
    // Dropdown Tabs
    
    
    std::array<std::unique_ptr<ImageButton>, 4> dropDownTabs;
    
    std::unique_ptr<DrawablePath> dropDownBottonBar;
    std::unique_ptr<ImageButton> dropDownEQ;
    std::unique_ptr<ImageButton> dropDownClip;
    std::unique_ptr<ImageButton> dropDownENV;
    std::unique_ptr<ImageButton> dropDownFX;
    
    
    // SUB VIEWS
    std::unique_ptr<OrionMenuBar> menuBar; 
    std::unique_ptr<PrimaryPaneComponent> primaryPane; 
    std::unique_ptr<SidePanelComponent> sidePanel;
    std::unique_ptr<ArrangementWindowComponent> arrangementWindow;
    std::unique_ptr<DraggableFileBrowserComponent> fileBrowser;
    
    std::unique_ptr<ImageButton> backButton;
    std::unique_ptr<ImageButton> resizeButton;
   
    std::unique_ptr<CircularMeter> meterInput;
    
    
    //std::unique_ptr<TabComponentHolder> tabComponents;//--!!!!!!!!!!!!
    std::unique_ptr<DropdownTable> dropdownTable;//--!!!!!!!!!!!!
    
    
    //std::unique_ptr<ImageButton> dropDownButton;
    
    std::unique_ptr<DrawablePath> footerPath;
    

    FileBrowserComponent filebrowser;
    
    File resourcefolder,skinfolder;
    std::unique_ptr<ImageComponent> backgroundImage;
    File* clipbackground;
    File* envbackground;
    File* eqbackground;
    
    void addMessageToList (const MidiMessage& message);
    
    void dropDownButtonClicked();
    
    void appdirClicked();
    void deskdirClicked();
    void downdirClicked();
    void musicdirClicked();
    void docdirClicked();
    void homedirClicked();
    void upbutClicked();
    
    TextButton instrumentTriggers[6];
    
    Orionlist maindir;
    ListBox mainlist;
        
    //int indices[7];

    DrawableButton AppDir;
    DrawableButton DeskDir;
    DrawableButton DownDir;
    DrawableButton MusicDir;
    DrawableButton DocDir;
    DrawableButton HomDir;
    DrawableButton UpBut;
    int whichdir {0};
    int changed {0};
    AudioFormatManager formatManager;
    double startTime;
    
    bool dropDownVisible = false;
    bool resizeViewVisible = false;
    bool arrangementWindowVisible = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionaudioAudioProcessorEditor)
};
