/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

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
//==============================================================================
/**
*/
class OrionaudioAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    OrionaudioAudioProcessorEditor (OrionaudioAudioProcessor&);
    ~OrionaudioAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void tabComponentChanged(int serial);

    std::unique_ptr<AudioFormatReaderSource> playSource;
     OrionFileBrowser filebrowser;
private:
    std::unique_ptr<DraggableFileBrowserComponent> fileBrowser;
    OrionaudioAudioProcessor& processor;
    //ScopedPointer<OrionTabComponent> tabComponent;
    OrionTabComponent *tabComponent[7];
    //FileBrowserComponent filebrowser;

    //FileTreeComponent tree;

    File resourcefolder,skinfolder;
    Image background;
    File* clipbackground;
    File* envbackground;
    File* eqbackground;

    void addMessageToList (const MidiMessage& message);

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

    OrionButton HiHatButton;
    OrionButton cymbalButton;
    OrionButton snapButton;

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

    std::unique_ptr<MidiOutput> midiOutput;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionaudioAudioProcessorEditor)
};
