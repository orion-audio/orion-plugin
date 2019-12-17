#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "OrionGlobalVars.h"

#define NUM_TABS 4

using namespace std;
using namespace juce;
//==============================================================================

OrionaudioAudioProcessorEditor::OrionaudioAudioProcessorEditor (OrionaudioAudioProcessor& p)
        : AudioProcessorEditor (&p), processor (p),
        kickButton(p,"KICK",DrawableButton::ButtonStyle::ImageFitted),
        snareButton(p,"SNARE",DrawableButton::ButtonStyle::ImageFitted ),
        clapButton(p,"CLAP",DrawableButton::ButtonStyle::ImageFitted ),
        percButton(p,"PERC",DrawableButton::ButtonStyle::ImageFitted ),
        hhcButton(p,"HH-C",DrawableButton::ButtonStyle::ImageFitted ),
        hhoButton(p,"HH-O",DrawableButton::ButtonStyle::ImageFitted ),
        snapButton(p,"CRASH",DrawableButton::ButtonStyle::ImageFitted),
        crashButton(p,"CRASH",DrawableButton::ButtonStyle::ImageFitted),
        dropDownButton(p,"DropDown",DrawableButton::ButtonStyle::ImageFitted),
        AppDir("Applications",DrawableButton::ButtonStyle::ImageFitted),
        DeskDir("Desktop",DrawableButton::ButtonStyle::ImageFitted),
        DownDir("Downloads",DrawableButton::ButtonStyle::ImageFitted),
        MusicDir("Music",DrawableButton::ButtonStyle::ImageFitted),
        DocDir("Documents",DrawableButton::ButtonStyle::ImageFitted),
        HomDir("Home",DrawableButton::ButtonStyle::ImageFitted),
        UpBut("Up",DrawableButton::ImageOnButtonBackground),
        filebrowser(1|4|8|32,File::getSpecialLocation(File::SpecialLocationType::userHomeDirectory),nullptr,nullptr),
//tree(DirectoryContentsList(nullptr,TimeSliceThread("thread")))
        mainlist("main", dynamic_cast<ListBoxModel*> (&maindir)), startTime(Time::getMillisecondCounterHiRes()*0.001)
{
        //indices = {kickButton.index, snareButton.index, clapButton.index, percButton.index, HiHatButton.index, cymbalButton.index, snapButton.index};
        for (int i=0; i<7; i++)
        {
                indices[i] = i;
        }
        // buttons[0]=kickButton;
        //std::vector<OrionButton>& buttons{kickButton, snareButton,clapButton, percButton, HiHatButton, cymbalButton, snapButton};
        /*
           resourcefolder = File::getSpecialLocation(File::globalApplicationsDirectory).getChildFile("Orion").getChildFile("OrionSampler").getChildFile("OrionSampler").getChildFile("Contents").getChildFile("Resources");

           skinfolder   = resourcefolder.getChildFile("skin").getChildFile("pictures");
           background   = ImageCache::getFromMemory(BinaryData::orionBackground_png, BinaryData::orionBackground_pngSize);
           kickFileOff  = new File(skinfolder.getChildFile("kick_off.png"));
           kickFileOn   = new File(skinfolder.getChildFile("kick_on.png"));
           snareFileOff = new File(skinfolder.getChildFile("snare_off.png"));
           snareFileOn  = new File(skinfolder.getChildFile("snare_on.png"));
           clapFileOff  = new File(skinfolder.getChildFile("clap_off.png"));
           clapFileOn   = new File(skinfolder.getChildFile("clap_on.png"));
           percFileOff  = new File(skinfolder.getChildFile("perc_off.png"));
           percFileOn   = new File(skinfolder.getChildFile("perc_on.png"));
           hhcFileOff   = new File(skinfolder.getChildFile("hhc_off.png"));
           hhcFileOn    = new File(skinfolder.getChildFile("hhc_on.png"));
           hhoFileOff   = new File(skinfolder.getChildFile("hho_off.png"));
           hhoFileOn    = new File(skinfolder.getChildFile("hho_on.png"));
           crashFileOff = new File(skinfolder.getChildFile("crash_off.png"));
           crashFileOn  = new File(skinfolder.getChildFile("crash_on.png"));
           appFileOn    = new File(skinfolder.getChildFile("appdir.png"));
         */
        background   = ImageCache::getFromMemory(BinaryData::orionBackground_png, BinaryData::orionBackground_pngSize);
        std::unique_ptr<Drawable> buttonOff;
        std::unique_ptr<Drawable> buttonOn;


        buttonOff = Drawable::createFromImageData(BinaryData::kick_off_png, BinaryData::kick_off_pngSize);
        buttonOn = Drawable::createFromImageData(BinaryData::kick_on_png, BinaryData::kick_on_pngSize);


        kickButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
        kickButton.onStateChange = [this] {
                                           drumButtonClicked(MidiNotes::kick, Tabs::kickTab, kickButton.isDown());
                                   };

        kickButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        kickButton.setEnabled(true);//防止用户多次按
        addAndMakeVisible(&kickButton);

        buttonOff = Drawable::createFromImageData(BinaryData::snare_off_png, BinaryData::snare_off_pngSize);
        buttonOn = Drawable::createFromImageData(BinaryData::snare_on_png, BinaryData::snare_on_pngSize);


        snareButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
        snareButton.onStateChange = [this] {
                                            drumButtonClicked(MidiNotes::snare, Tabs::snareTab, snareButton.isDown());
                                    };
        snareButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        snareButton.setEnabled(true);//防止用户多次按
        addAndMakeVisible(&snareButton);

        buttonOff = Drawable::createFromImageData(BinaryData::clap_off_png, BinaryData::clap_off_pngSize);
        buttonOn = Drawable::createFromImageData(BinaryData::clap_on_png, BinaryData::clap_on_pngSize);


        clapButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
        clapButton.onStateChange = [this] {
                                           drumButtonClicked(MidiNotes::clap, Tabs::clapTab, clapButton.isDown());
                                   };
        clapButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        clapButton.setEnabled(true);//防止用户多次按
        addAndMakeVisible(&clapButton);


        buttonOff = Drawable::createFromImageData(BinaryData::perc_off_png, BinaryData::perc_off_pngSize);
        buttonOn = Drawable::createFromImageData(BinaryData::perc_on_png, BinaryData::perc_on_pngSize);


        percButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
        percButton.onStateChange = [this] {
                                           drumButtonClicked(MidiNotes::perc, Tabs::percTab, percButton.isDown());
                                   };
        percButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        percButton.setEnabled(true);//防止用户多次按
        addAndMakeVisible(&percButton);

        buttonOff = Drawable::createFromImageData(BinaryData::snap_0ff_png, BinaryData::snap_0ff_pngSize);
        buttonOn = Drawable::createFromImageData(BinaryData::snap_on_png, BinaryData::snap_on_pngSize);


        snapButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
        snapButton.onStateChange = [this] {
                                           drumButtonClicked(MidiNotes::perc, Tabs::percTab, snapButton.isDown());
                                   };
        snapButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        snapButton.setEnabled(true);//防止用户多次按
        addAndMakeVisible(&snapButton);



        buttonOff = Drawable::createFromImageData(BinaryData::hhc_off_png, BinaryData::hhc_off_pngSize);
        buttonOn = Drawable::createFromImageData(BinaryData::hhc_on_png, BinaryData::hhc_on_pngSize);

        hhcButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
        hhcButton.onStateChange = [this] {
                                          drumButtonClicked(MidiNotes::hhc, Tabs::hhcTab, hhcButton.isDown());
                                  };
        hhcButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        hhcButton.setEnabled(true);//防止用户多次按
        addAndMakeVisible(&hhcButton);


        buttonOff = Drawable::createFromImageData(BinaryData::hho_off_png, BinaryData::hho_off_pngSize);
        buttonOn = Drawable::createFromImageData(BinaryData::hho_on_png, BinaryData::hho_on_pngSize);


        hhoButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
        hhoButton.onStateChange = [this] {
                                          drumButtonClicked(MidiNotes::hho, Tabs::hhoTab, hhoButton.isDown());
                                  };
        hhoButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        hhoButton.setEnabled(true);//防止用户多次按
        addAndMakeVisible(&hhoButton);

        buttonOff = Drawable::createFromImageData(BinaryData::crash_off_png, BinaryData::crash_off_pngSize);
        buttonOn = Drawable::createFromImageData(BinaryData::crash_on_png, BinaryData::crash_on_pngSize);


        crashButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
        crashButton.onStateChange = [this] {
                                            drumButtonClicked(MidiNotes::snap, Tabs::snapTab, crashButton.isDown());
                                    };
        crashButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        crashButton.setEnabled(true);//防止用户多次按
        addAndMakeVisible(&crashButton);

        //->
        buttonOff = Drawable::createFromImageData(BinaryData::arrow_down_png, BinaryData::arrow_down_pngSize);
        buttonOn = Drawable::createFromImageData(BinaryData::arrow_up_png, BinaryData::arrow_up_pngSize);
        dropDownButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
        dropDownButton.onClick = [this] /*capture this event 执行后面{}的指令*/ {
                                         dropDownButtonClicked();
                                 };
        dropDownButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        dropDownButton.setEnabled(true);//防止用户多次按
        addAndMakeVisible(&dropDownButton);


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
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        RectanglePlacement orionBackgroundRectanglePlacement(64);

        if(dropDown) {
                g.drawImageWithin(background, 0, 0,getWidth(),getHeight()/1.50,orionBackgroundRectanglePlacement,false);
        }else{g.drawImageWithin(background, 0, 0,getWidth(),getHeight(),orionBackgroundRectanglePlacement,false);}




        /*
           OrionBrowser* custablook = new OrionBrowser();

           if(auto* newl = dynamic_cast<juce::LookAndFeel*> (custablook))
           {
            filebrowser.setLookAndFeel(newl);
           }
         */
        //auto* preview = dynamic_cast<Component*> (filebrowser.getPreviewComponent());

        //display->setBounds (0, 75, 195, 228);
        //addAndMakeVisible(display);

        File subdir;
        if(AppDir.isDown()==true)
        {
                appdirClicked();
        }
        else if(DeskDir.isDown()==true)
        {
                deskdirClicked();
        }
        else if(DownDir.isDown()==true)
        {
                downdirClicked();
        }
        else if(MusicDir.isDown()==true)
        {
                musicdirClicked();
        }
        else if(DocDir.isDown()==true)
        {
                docdirClicked();
        }
        else if(HomDir.isDown()==true)
        {
                homedirClicked();
        }
        if(UpBut.isDown()==true)
        {
                upbutClicked();
        }

        //std::cout<<"which dir "<<whichdir<<"\n";
        if(changed == 1)
        {
                switch(whichdir)
                {
                case 1:
                        filebrowser.setRoot(File::getSpecialLocation(File::SpecialLocationType::globalApplicationsDirectory));
                        break;
                case 2:
                        filebrowser.setRoot(File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory));
                        break;
                case 3:
                        filebrowser.setRoot(File::getSpecialLocation(File::SpecialLocationType::userHomeDirectory).getChildFile("Downloads"));
                        break;
                case 4:
                        filebrowser.setRoot(File::getSpecialLocation(File::SpecialLocationType::userMusicDirectory));
                        break;
                case 5:
                        filebrowser.setRoot(File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory));
                        break;
                case 6:
                        filebrowser.setRoot(File::getSpecialLocation(File::SpecialLocationType::userHomeDirectory));
                        break;
                }
                changed = 0;
        }

//    auto* display = dynamic_cast<Component*> (filebrowser.getDisplayComponent());
//    display->setBounds(0, 323, 195, 278);
//    addAndMakeVisible(display);
        //std::cout<<"is dragging? "<<filebrowser.isDragAndDropActive()<<"\n";

        auto* list = dynamic_cast<Component*> (&mainlist);
        list->setBounds(0, 75, 195, 228);


}

void OrionaudioAudioProcessorEditor::resized()
{
        setUIScale(float(getWidth() / float(orion::defaultWidth)));
        cornerComponent->setBounds(getWidth() - (getWidth() * .03), getHeight() - (getWidth() * .03), (getWidth() * .03), (getWidth() * .03));

        tabComponents->setBounds(0, getHeight() - getHeight() / 3, getWidth(), getHeight() / 3);

        kickButton.setBounds(OrionGlobalWidth/2 - 200, OrionGlobalHeight/2 - 225, 100, 112);
        snareButton.setBounds(OrionGlobalWidth/2 - 50, OrionGlobalHeight/2 - 225, 100, 112);
        clapButton.setBounds(OrionGlobalWidth/2 + 100, OrionGlobalHeight/2 - 225, 100, 112);
        percButton.setBounds(OrionGlobalWidth/2 + 250, OrionGlobalHeight/2 - 225, 100, 112);

        snapButton.setBounds(OrionGlobalWidth/2 - 200, OrionGlobalHeight/2 - 100, 100, 112);
        hhoButton.setBounds(OrionGlobalWidth/2 - 50, OrionGlobalHeight/2 - 100, 100, 112);
        hhcButton.setBounds(OrionGlobalWidth/2 + 100, OrionGlobalHeight/2 - 100, 100, 112);
        crashButton.setBounds(OrionGlobalWidth/2 + 250, OrionGlobalHeight/2 - 100, 100, 112);

        dropDownButton.setBounds(OrionGlobalWidth/5.15701, OrionGlobalHeight*2.983/5, 50, 50);

        fileBrowser->setBounds(0, getHeight() * .11, getWidth() * .17, getHeight() * .56);

        setBoundsScaled(waveWiggle.get(), {373,388, 469, 64});


        setBoundsScaled(meterInput.get(), 919, /*JUCE_LIVE_CONSTANT(*/ 23 /*)*/, 135, 17);
        setBoundsScaled(meterLeft.get(), 1072, 383, 17, 90);
        setBoundsScaled(meterRight.get(), 1092, 383, 17, 90);

//    AppDir.setBounds(0, 75, 195, 228/10);
//    DeskDir.setBounds(0, 75+228/10, 195, 228/10);
//    DownDir.setBounds(0, 75+228/10*2, 195, 228/10);
//    MusicDir.setBounds(0, 75+228/10*3, 195, 228/10);
//    DocDir.setBounds(0, 75+228/10*4, 195, 228/10);
//    HomDir.setBounds(0, 75+228/10*5, 195, 228/10);
//    UpBut.setBounds(195,323,20,228/10);
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
                processor.synth.noteOn(1, midiNote, 120);
                if (processor.getMidiOutput() != nullptr)
                        processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOn(1, midiNote, 1.f));

                tabComponents->setCurrentTab(tabIndex);


        }

        else
        {
                processor.synth.noteOff(1, midiNote, 0, false /*没有淡出*/);
                if (processor.getMidiOutput() != nullptr)
                        processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOff(1, midiNote, 0.f));
        }

}

void OrionaudioAudioProcessorEditor::dropDownButtonClicked()
{
        dropDown = !dropDown;
        std::unique_ptr<Drawable> buttonBackground;
        if(dropDown) {
                setSize (OrionGlobalWidth, OrionGlobalHeight);
                buttonBackground = Drawable::createFromImageData(BinaryData::arrow_up_png, BinaryData::arrow_up_pngSize);
                dropDownButton.setImages(buttonBackground.get());
        }else{
                setSize (OrionGlobalWidth, OrionGlobalHeight*2/3);
                buttonBackground = Drawable::createFromImageData(BinaryData::arrow_down_png, BinaryData::arrow_down_pngSize);
                dropDownButton.setImages(buttonBackground.get());
        }
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

void OrionaudioAudioProcessorEditor::lookupindex(int index,int ref)
{
        switch(index)
        {
        case 0:
                if(kickButton.index>ref)
                {
                        kickButton.index = kickButton.index - 1;
                        indices[0] = kickButton.index;
                }
                break;
        case 1:
                if(snareButton.index>ref)
                {
                        snareButton.index = snareButton.index -1;
                        indices[1] = snareButton.index;
                }
                break;
        case 2:
                if(clapButton.index>ref)
                {
                        clapButton.index = clapButton.index -1;
                        indices[2] = clapButton.index;
                }
                break;
        case 3:
                if(percButton.index>ref)
                {
                        percButton.index = percButton.index -1;
                        indices[3] = percButton.index;
                }
                break;

        case 4:
                if(snapButton.index>ref)
                {
                        snapButton.index = snapButton.index -1;
                        indices[6] = snapButton.index;
                }
        case 5:
                if(hhcButton.index>ref)
                {
                        hhcButton.index = hhcButton.index -1;
                        indices[4] = hhcButton.index;
                }
                break;
        case 6:
                if(hhoButton.index>ref)
                {
                        hhoButton.index = hhoButton.index -1;
                        indices[5] = hhoButton.index;
                }
                break;
        case 7:
                if(crashButton.index>ref)
                {
                        crashButton.index = crashButton.index -1;
                        indices[6] = crashButton.index;
                }
                break;

        }
}

void OrionaudioAudioProcessorEditor::draganddropped(int index)
{
        //keep track of which instrument is on which voice, determined by files dropped on button
        //int indices[7] = {kickButton.index, 1,2,3,4,5,6};
        //std::vector<OrionButton&> buttons = {&kickButton, &snareButton,&clapButton, &percButton, &HiHatButton, &cymbalButton, &snapButton};
        //std::vector<Ptr> buttons = {*kickButton, *snareButton,*clapButton, *percButton, *HiHatButton, *cymbalButton, *snapButton};
        for (int i=0; i<7; i++)
        {
                if (i!=index)//this is intact, need to move to the front
                {
                        lookupindex(i,indices[index]);
                        //buttons[i].index = buttons[i].index - 1;
                        //std::cout<<"indices" <<indices[0]<<" "<<indices[1]<<" "<<indices[2]<<" "<<indices[3]<<" "<<indices[4]<<" "<<indices[5]<<" "<<indices[6]<<"\n";
                }
        }
}


void OrionaudioAudioProcessorEditor::setDefaultSize()
{
        setSize(orion::defaultWidth, orion::defaultHeight);
}
