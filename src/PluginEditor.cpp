#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "OrionGlobalVars.h"

#define NUM_TABS 4

using namespace std;
using namespace juce;
//==============================================================================

OrionaudioAudioProcessorEditor::OrionaudioAudioProcessorEditor (OrionaudioAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p),
AppDir("Applications",DrawableButton::ButtonStyle::ImageFitted),
DeskDir("Desktop",DrawableButton::ButtonStyle::ImageFitted),
DownDir("Downloads",DrawableButton::ButtonStyle::ImageFitted),
MusicDir("Music",DrawableButton::ButtonStyle::ImageFitted),
DocDir("Documents",DrawableButton::ButtonStyle::ImageFitted),
HomDir("Home",DrawableButton::ButtonStyle::ImageFitted),
UpBut("Up",DrawableButton::ImageOnButtonBackground),
filebrowser(1|4|8|32,File::getSpecialLocation(File::SpecialLocationType::userHomeDirectory),nullptr,nullptr),
mainlist("main", dynamic_cast<ListBoxModel*> (&maindir)), startTime(Time::getMillisecondCounterHiRes()*0.001)
{
    
    menuBar.reset(new OrionMenuBar(&p, this));
    addAndMakeVisible(menuBar.get());
    
    primaryPane.reset(new PrimaryPaneComponent(&p, this));
    addAndMakeVisible(primaryPane.get());
    
    sidePanel.reset(new SidePanelComponent(&p, this));
    addAndMakeVisible(sidePanel.get());
    
    arrangementWindow.reset(new ArrangementWindowComponent(&p, this));
    addAndMakeVisible(arrangementWindow.get());
    
    
    //indices = {kickButton.index, snareButton.index, clapButton.index, percButton.index, HiHatButton.index, cymbalButton.index, snapButton.index};
    for (int i=0; i<7; i++)
    {
        indices[i] = i;
    }
    backgroundImage.reset(new ImageComponent("backgroundImage"));
    backgroundImage->setImage(ImageCache::getFromMemory(BinaryData::orionBackground_png, BinaryData::orionBackground_pngSize), RectanglePlacement::fillDestination);
    addAndMakeVisible(backgroundImage.get());
    
    
    
    std::unique_ptr<Drawable> buttonOff;
    std::unique_ptr<Drawable> buttonOn;
        
    buttonOff = Drawable::createFromImageData(BinaryData::arrow_down_png, BinaryData::arrow_down_pngSize);
    buttonOn = Drawable::createFromImageData(BinaryData::arrow_up_png, BinaryData::arrow_up_pngSize);
    buttonOn = Drawable::createFromImageData(BinaryData::appdir_png, BinaryData::appdir_pngSize);
    
    AppDir.setImages(buttonOn.get(), buttonOn.get(), buttonOn.get());
    //AppDir.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ appdirClicked(); };
    AppDir.setColour(TextButton::buttonColourId, Colours::darkgrey);
    AppDir.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&AppDir);
    
    DeskDir.setImages(buttonOn.get(), buttonOn.get(), buttonOn.get());
    // DeskDir.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ deskdirClicked(); };
    DeskDir.setColour(TextButton::buttonColourId, Colours::darkgrey);
    DeskDir.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&DeskDir);
    
    DownDir.setImages(buttonOn.get(), buttonOn.get(), buttonOn.get());
    //DownDir.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ downdirClicked(); };
    DownDir.setColour(TextButton::buttonColourId, Colours::darkgrey);
    DownDir.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&DownDir);
    
    MusicDir.setImages(buttonOn.get(), buttonOn.get(), buttonOn.get());
    // MusicDir.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ musicdirClicked(); };
    MusicDir.setColour(TextButton::buttonColourId, Colours::darkgrey);
    MusicDir.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&MusicDir);
    
    DocDir.setImages(buttonOn.get(), buttonOn.get(), buttonOn.get());
    // DocDir.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ docdirClicked(); };
    DocDir.setColour(TextButton::buttonColourId, Colours::darkgrey);
    DocDir.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&DocDir);
    
    
    HomDir.setImages(buttonOn.get(), buttonOn.get(), buttonOn.get());
    //HomDir.onStateChange = [this]/*capture this event 执行后面{}的指令*/{ homedirClicked(); };
    HomDir.setColour(TextButton::buttonColourId, Colours::darkgrey);
    HomDir.setEnabled(true);//防止用户多次按
    addAndMakeVisible(&HomDir);
    
    //set up up button's images
    Path arrowPath;
    arrowPath.addArrow ({ 50.0f, 100.0f, 50.0f, 0.0f }, 40.0f, 100.0f, 50.0f);
    
    DrawablePath arrowImage;
    arrowImage.setFill (Colours::black.withAlpha (0.4f));
    arrowImage.setPath (arrowPath);
    UpBut.setImages(&arrowImage);
    addAndMakeVisible(&UpBut);
    
    formatManager.registerBasicFormats();
    
    tabComponents.reset(new TabComponentHolder(p));
    addAndMakeVisible(tabComponents.get());
    
    fileBrowser.reset(new DraggableFileBrowserComponent());
    addAndMakeVisible(fileBrowser.get());
    
    waveWiggle.reset(new WaveWiggle());
    addAndMakeVisible(waveWiggle.get());
    
    meterInput.reset(new CircularMeter());
    meterInput->updaterFunction = [this] {
        return processor.getInputLevel();
    };
    addAndMakeVisible(meterInput.get());
    
    meterLeft.reset(new CircularMeter());
    meterLeft->updaterFunction = [this] {
        return processor.getOutputLevel(0);
    };
    addAndMakeVisible(meterLeft.get());
    
    meterRight.reset(new CircularMeter());
    meterRight->updaterFunction = [this] {
        return processor.getOutputLevel(1);
    };
    addAndMakeVisible(meterRight.get());
    
    constrainer.setFixedAspectRatio((float)OrionGlobalWidth/OrionGlobalHeight);
    constrainer.setSizeLimits((float)OrionGlobalWidth / 2, (float)OrionGlobalHeight / 2, (float)OrionGlobalWidth * 2, (float)OrionGlobalHeight * 2);
    
    cornerComponent.reset(new OrionResizableCornerComponent<OrionaudioAudioProcessorEditor>(this, this, &constrainer));
    addAndMakeVisible(cornerComponent.get());
    
    
    setSize (OrionGlobalWidth, OrionGlobalHeight);
    
}



OrionaudioAudioProcessorEditor::~OrionaudioAudioProcessorEditor()
{
}


//==============================================================================
void OrionaudioAudioProcessorEditor::tabComponentChanged(int serial)
{
    //    tabComponent[serial]->setBounds(0, (getHeight()/3)*2, getWidth(), getHeight()/3);
    //
    //    addAndMakeVisible(tabComponent[serial].get());
}
//==============================================================================

void OrionaudioAudioProcessorEditor::paint (Graphics& g)
{
    //************************************DO NOT PUT ANY SET BOUNDS METHODS OR ANYTHING OTHER THAN DRAWING METHODS********************************
    //*********************************************************************************************************************************************
    //*********************************************************************************************************************************************
    //*********************************************************************************************************************************************
    
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        
}

void OrionaudioAudioProcessorEditor::resized()
{
    setUIScale(float(getWidth() / float(orion::defaultWidth)));
    cornerComponent->setBounds(getWidth() - (getWidth() * .03), getHeight() - (getWidth() * .03), (getWidth() * .03), (getWidth() * .03));
    
    auto area = getLocalBounds();
    
    if (dropDownVisible)
        tabComponents->setBounds(area.removeFromBottom(getHeight() / 3));
    
        
    // MENU BAR
    auto menuBarArea = area;
    menuBarArea = menuBarArea.removeFromTop(getHeight() * .1);
    menuBarArea.removeFromLeft(getWidth() / 6);
    menuBar->setBounds(menuBarArea);
    
    // PRIMARY PANE
    auto primaryPaneArea = area;
    primaryPaneArea.setY(menuBar->getBottom());
    if (dropDownVisible)
        primaryPaneArea.setBottom(tabComponents->getY());
    else
        primaryPaneArea.setBottom(getHeight());
    primaryPaneArea.removeFromLeft(getWidth() / 6);
    if (arrangementWindowVisible)
        arrangementWindow->setBounds(primaryPaneArea);
    else
        primaryPane->setBounds(primaryPaneArea);

    
    // SIDE PANEL
    area = getLocalBounds();
    area = area.removeFromLeft(getWidth() / 6);
//    area.setHeight(h);
    sidePanel->setBounds(area);
    
//    backgroundImage->setBounds(0, 0, getWidth(), getHeight() * (2.f / 3.f));
    
//    kickButton.setBounds(OrionGlobalWidth/2 - 200, OrionGlobalHeight/2 - 225, 100, 112);
//    snareButton.setBounds(OrionGlobalWidth/2 - 50, OrionGlobalHeight/2 - 225, 100, 112);
//    clapButton.setBounds(OrionGlobalWidth/2 + 100, OrionGlobalHeight/2 - 225, 100, 112);
//    percButton.setBounds(OrionGlobalWidth/2 + 250, OrionGlobalHeight/2 - 225, 100, 112);
//
//    snapButton.setBounds(OrionGlobalWidth/2 - 200, OrionGlobalHeight/2 - 100, 100, 112);
//    hhoButton.setBounds(OrionGlobalWidth/2 - 50, OrionGlobalHeight/2 - 100, 100, 112);
//    hhcButton.setBounds(OrionGlobalWidth/2 + 100, OrionGlobalHeight/2 - 100, 100, 112);
//    crashButton.setBounds(OrionGlobalWidth/2 + 250, OrionGlobalHeight/2 - 100, 100, 112);
//
//    setBoundsScaled(dropDownButton.get(), 174.52, 391.5, 50, 50);
//
//    fileBrowser->setBounds(0, getHeight() * .11, getWidth() * .17, getHeight() * .56);
//
//    setBoundsScaled(waveWiggle.get(), {373,388, 469, 64});
//
//    setBoundsScaled(meterInput.get(), 919, /*JUCE_LIVE_CONSTANT(*/ 23 /*)*/, 135, 17);
//    setBoundsScaled(meterLeft.get(), 1072, 383, 17, 90);
//    setBoundsScaled(meterRight.get(), 1092, 383, 17, 90);
//
//    auto* list = dynamic_cast<Component*> (&mainlist);
//    list->setBounds(0, 75, 195, 228);
    
    //    AppDir.setBounds(0, 75, 195, 228/10);
    //    DeskDir.setBounds(0, 75+228/10, 195, 228/10);
    //    DownDir.setBounds(0, 75+228/10*2, 195, 228/10);
    //    MusicDir.setBounds(0, 75+228/10*3, 195, 228/10);
    //    DocDir.setBounds(0, 75+228/10*4, 195, 228/10);
    //    HomDir.setBounds(0, 75+228/10*5, 195, 228/10);
    //    UpBut.setBounds(195,323,20,228/10);
    
    
    //************************************DO NOT PUT ANY SET BOUNDS METHODS OR ANYTHING OTHER THAN DRAWING METHODS********************************
    //*********************************************************************************************************************************************
    //*********************************************************************************************************************************************
    //*********************************************************************************************************************************************
    
    
}

void OrionaudioAudioProcessorEditor::addMessageToList (const MidiMessage& message)
{
    auto time = message.getTimeStamp();
    auto hours   = ((int) (time / 3600.0)) % 24;
    auto minutes = ((int) (time / 60.0)) % 60;
    auto seconds = ((int) time) % 60;
    auto millis  = ((int) (time * 1000.0)) % 1000;
    auto timecode = String::formatted ("%02d:%02d:%02d.%03d",
                                       hours,
                                       minutes,
                                       seconds,
                                       millis);
    //logMessage (timecode + "  -  " + getMidiMessageDescription (message));
}

void OrionaudioAudioProcessorEditor::drumButtonClicked(int midiNote, int tabIndex, bool isDown)
{
    if(isDown)
    {
        waveWiggle->startAnimation();
        processor.getSampler()->noteOn(1, midiNote, 120);
        if (processor.getMidiOutput() != nullptr)
            processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOn(1, midiNote, 1.f));
        
        tabComponents->setCurrentTab(tabIndex);
        
        
    }
    
    else
    {
        processor.getSampler()->noteOff(1, midiNote, 0, false /*没有淡出*/);
        if (processor.getMidiOutput() != nullptr)
            processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOff(1, midiNote, 0.f));
    }
    
}

void OrionaudioAudioProcessorEditor::dropDownButtonClicked()
{
//            dropDown = !dropDown;
//            std::unique_ptr<Drawable> buttonBackground;
//            if(dropDown)
//            {
//                    setSize (orion::defaultWidth * getUIScale(), orion::defaultHeight * getUIScale());
//
//                    buttonBackground = Drawable::createFromImageData(BinaryData::arrow_up_png, BinaryData::arrow_up_pngSize);
//            }
//
//            else
//            {
//                    setSize (orion::defaultWidth * getUIScale(), orion::defaultHeight * getUIScale() * 2/3);
//                    buttonBackground = Drawable::createFromImageData(BinaryData::arrow_down_png, BinaryData::arrow_down_pngSize);
//            }
}

void OrionaudioAudioProcessorEditor::appdirClicked()
{
    //change the below directory
    whichdir = 1;
    changed = 1;
    
}

void OrionaudioAudioProcessorEditor::deskdirClicked()
{
    whichdir = 2;
    changed = 1;
}

void OrionaudioAudioProcessorEditor::downdirClicked()
{
    whichdir = 3;
    changed = 1;
}

void OrionaudioAudioProcessorEditor::musicdirClicked()
{
    whichdir = 4;
    changed = 1;
}

void OrionaudioAudioProcessorEditor::docdirClicked()
{
    whichdir = 5;
    changed = 1;
}

void OrionaudioAudioProcessorEditor::homedirClicked()
{
    whichdir = 6;
    changed = 1;
}

void OrionaudioAudioProcessorEditor::upbutClicked()
{
    filebrowser.goUp();
    
};

void OrionaudioAudioProcessorEditor::setDefaultSize()
{
    setSize(orion::defaultWidth, orion::defaultHeight);
}

void OrionaudioAudioProcessorEditor::updateDropDownState(bool newState)
{
    DBG((int)newState);
    dropDownVisible = newState;
    tabComponents->setVisible(dropDownVisible);
    resized();
}

void OrionaudioAudioProcessorEditor::toggleArrangmentWindow(bool windowVisible)
{
    arrangementWindowVisible = windowVisible;
    arrangementWindow->setVisible(windowVisible);
    primaryPane->setVisible(!windowVisible);
    resized();
}
