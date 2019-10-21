

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
//==============================================================================
/**
*/
class OrionaudioAudioProcessorEditor : public AudioProcessorEditor
{
public:
    
    enum MidiNotes : int
    {
        kick = 36,
        snare = 38,
        clap = 39,
        snap = 46,
        perc = 41,
        hhc = 42,
        hho = 43,
        crash = 50
    };
    
    enum Tabs : int
    {
        kickTab = 0,
        snareTab,
        clapTab,
        percTab,
        snapTab,
        hhcTab,
        hhoTab,
        crashTab
    };

    
    OrionaudioAudioProcessorEditor (OrionaudioAudioProcessor&);
    ~OrionaudioAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void tabComponentChanged(int serial);
 
    std::unique_ptr<AudioFormatReaderSource> playSource;
//     OrionFileBrowser filebrowser;
private:
    
    
    std::unique_ptr<DraggableFileBrowserComponent> fileBrowser;
    std::unique_ptr<WaveWiggle> waveWiggle;
    
    std::unique_ptr<CircularMeter> meterLeft;
    std::unique_ptr<CircularMeter> meterRight;
    
    OrionaudioAudioProcessor& processor;
    //ScopedPointer<OrionTabComponent> tabComponent;
    std::array<std::unique_ptr<OrionTabComponent>, 7> tabComponent;
    FileBrowserComponent filebrowser;
   
//    FileTreeComponent tree;
    
    
    
    File resourcefolder,skinfolder;
    Image background;
    File* clipbackground;
    File* envbackground;
    File* eqbackground;
    
    void addMessageToList (const MidiMessage& message);
    
    void drumButtonClicked(int midiNote, int tabIndex, bool isDown);

    void kickButtonClicked();
    void snareButtonClicked();
    void clapButtonClicked();
    void percButtonClicked();
    
    
    void HiHatButtonClicked();
    void cymbalButtonClicked();
    void snapButtonClicked();
    
    
    void appdirClicked();
    void deskdirClicked();
    void downdirClicked();
    void musicdirClicked();
    void docdirClicked();
    void homedirClicked();
    void upbutClicked();
    
    void lookupindex(int index,int ref);
    void draganddropped(int index);
    TextButton instrumentTriggers[6];
    
    //ComboBox directory;
    //PopupMenu dir;
    Orionlist maindir;
    ListBox mainlist;
    
    //DrawableButton kickButton;
    OrionButton kickButton;
    OrionButton snareButton;
    OrionButton clapButton;
    OrionButton percButton;
    
    OrionButton snapButton;
    OrionButton hhcButton;//this used to be hihat
    OrionButton hhoButton;//cymbal
    OrionButton crashButton;//snap
    
    
    
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
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionaudioAudioProcessorEditor)
};
