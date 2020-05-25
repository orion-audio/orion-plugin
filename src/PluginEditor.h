

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OrionTabComponent.h"
#include "OrionBrowser.h"
#include "OrionButton.h"
#include "Orionlist.h"
#include "OrionFileBrowser.h"
#include "OrionFileTreeComponent.h"
#include "DraggableFileBrowserComponent.h"
#include "WaveWiggle.h"
#include "CircularMeter.h"
#include <array>
#include "OrionResizableCornerComponent.h"
#include "ResizableContainer.h"
#include "TabComponentHolder.h"
#include "OrionMenuBar.h"
#include "PrimaryPaneComponent.h"
#include "SidePanelComponent.h"

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
    
    void updateDropDownState(bool newState);
    std::unique_ptr<AudioFormatReaderSource> playSource;
    
    void setDefaultSize();
    
    void drumButtonClicked(int midiNote, int tabIndex, bool isDown);

    ComponentBoundsConstrainer constrainer;
    
private:
    
    std::unique_ptr<OrionResizableCornerComponent<OrionaudioAudioProcessorEditor> > cornerComponent;
    //ComponentBoundsConstrainer constrainer;
    
    std::unique_ptr<OrionMenuBar> menuBar; 
    std::unique_ptr<PrimaryPaneComponent> primaryPane; 
    std::unique_ptr<SidePanelComponent> sidePanel;
    
    std::unique_ptr<DraggableFileBrowserComponent> fileBrowser;
    std::unique_ptr<WaveWiggle> waveWiggle;
    
    std::unique_ptr<CircularMeter> meterLeft;
    std::unique_ptr<CircularMeter> meterRight;
    
    std::unique_ptr<CircularMeter> meterInput;
    std::unique_ptr<TabComponentHolder> tabComponents;
    
    OrionaudioAudioProcessor& processor;
    //ScopedPointer<OrionTabComponent> tabComponent;
    //    std::array<std::unique_ptr<OrionTabComponent>, 7> tabComponent;
    FileBrowserComponent filebrowser;
    
    //    FileTreeComponent tree;
    
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
    
    //ComboBox directory;
    //PopupMenu dir;
    Orionlist maindir;
    ListBox mainlist;
        
    std::unique_ptr<ImageButton> dropDownButton;
    
    int indices[7];
    // std::vector<OrionButton>& buttons;
    
    
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionaudioAudioProcessorEditor)
};
