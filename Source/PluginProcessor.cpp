/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
static String doubleToString(double val) { return String(val); }
static double stringToDouble(String s){return std::stod(s.toStdString());}

//==============================================================================
OrionaudioAudioProcessor::OrionaudioAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif

//    tree(*this,nullptr,"PARAMETERS",
//     {
//
//
//         std::make_unique<AudioParameterFloat> ("Pan", "", NormalisableRange<float> (0.0f,0.3f),0.07f),
//         std::make_unique<AudioParameterFloat> ("pitchVal", "", NormalisableRange<float>(-12, 12, 1), 0),
//
//         std::make_unique<AudioParameterFloat> ("delayTime", "", NormalisableRange<float>(0, 300, 1), 0),
//         std::make_unique<AudioParameterFloat> ("delayFeedback", "", NormalisableRange<float>(0, 95, 1), 0),
//         std::make_unique<AudioParameterFloat> ("delayColor", "", NormalisableRange<float>(-100, 100, 1), 0),
//         std::make_unique<AudioParameterFloat> ("delayPan", "", NormalisableRange<float>(-1, 1), 0),
//         std::make_unique<AudioParameterFloat> ("delayDryWet", "", NormalisableRange<float>(0, 100, 1), 0)
//
//     })

{
    midiOutput = MidiOutput::createNewDevice("Orion Audio");
    if (midiOutput != nullptr)
        midiOutput->startBackgroundThread();
    
    undoManager = new UndoManager();
    valueTree = new AudioProcessorValueTreeState(*this, undoManager);
    synth.setup(48000);
    for(int i = 0;i < synth.getNumVoices(); i++)
    {
   
        
        
        valueTree->createAndAddParameter(String("compRatio" + String(i)), "compRatio", "", NormalisableRange<float>(1.0f, 30.0f, 1.0f), 1.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("compAttack" + String(i)), "compAttack", "", NormalisableRange<float>(0.1f, 80.0f, 0.1f), 0.1f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("compRelease" + String(i)), "compRelease", "", NormalisableRange<float>(0.1f, 1000.0f, 0.1f), 0.1f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("compGain" + String(i)), "compGain", "", NormalisableRange<float>(0.0f, 40.0f, 0.1f), 0.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("compThresh" + String(i)), "compThresh", "", NormalisableRange<float>(-60.0f, 0.0f, 0.1f), -60.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("compSwitch" + String(i)), "compSwitch", "", NormalisableRange<float>(0, 1, 1), 0, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("compSwitch" + String(i)), "compSwitch", "", NormalisableRange<float>(0, 1, 1), 0, doubleToString, stringToDouble);
        
        
        valueTree->createAndAddParameter(String("reverbPredelay" + String(i)), "reverbPredelay", "", NormalisableRange<float>(0.0f, 1.0f), 0.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("reverbSize" + String(i)), "reverbSize", "", NormalisableRange<float>(0.0f, 1.0f), 0.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("reverbColor" + String(i)), "reverbColor", "", NormalisableRange<float>(-1.0f, 1.0f/*, 1*/), 0.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("reverbDecay" + String(i)), "reverbDecay", "", NormalisableRange<float>(0.0f, 1.0f), 0.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("reverbDry" + String(i)), "reverbDry", "", NormalisableRange<float>(0.0f, 1.0f), 0.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("reverbSwitch" + String(i)), "reverbSwitch", "", NormalisableRange<float>(0, 1, 1), 0, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("reverbSwitch" + String(i)), "reverbSwitch", "", NormalisableRange<float>(0, 1, 1), 0, doubleToString, stringToDouble);
        
        
        valueTree->createAndAddParameter(String("delayTime" + String(i)), "delayTime", "", NormalisableRange<float>(0.0f, 0.5f), 0.1f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("delayFeedback" + String(i)), "delayFeedback", "", NormalisableRange<float>(0.0f, 0.95f), 0.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("delayColor" + String(i)), "delayColor", "", NormalisableRange<float>(-1.0f, 1.0f/*, 1*/), 0.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("delayPan" + String(i)), "delayPan", "", NormalisableRange<float>(-50.0f, 50.0f, 1.0f), 0.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("delayDryWet" + String(i)), "delayDryWet", "", NormalisableRange<float>(0.0f, 1.0f), 0.3f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("delaySwitch" + String(i)), "delaySwitch", "", NormalisableRange<float>(0, 1, 1), 0, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("delaySwitch" + String(i)), "delaySwitch", "", NormalisableRange<float>(0, 1, 1), 0, doubleToString, stringToDouble);
        
        
        valueTree->createAndAddParameter(String("envAttack" + String(i)), "envAttack", "", NormalisableRange<float>(0.1f, 1500.0f, 0.1f), 0.1f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("envHold" + String(i)), "envHold", "", NormalisableRange<float>(0.1f, 1500.0f, 0.1f), 0.1f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("envDecay" + String(i)), "envDecay", "", NormalisableRange<float>(0.1f, 2500.0f, 0.1f), 0.1f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("envRelease" + String(i)), "envRelease", "", NormalisableRange<float>(0.1f, 2500.0f, 0.1f), 1000.0f, doubleToString, stringToDouble);
        
        valueTree->createAndAddParameter(String("envAttackBend" + String(i)), "envAttackBend", "", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.01f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("envSustain" + String(i)), "envSustain", "", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 1.0f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("envDecayBend" + String(i)), "envDecayBend", "", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.01f, doubleToString, stringToDouble);
        valueTree->createAndAddParameter(String("envReleaseBend" + String(i)), "envReleaseBend", "", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.01f, doubleToString, stringToDouble);
        
        
        
        
        if (auto* voice = dynamic_cast<OrionSamplerVoice*> (synth.getVoice(i)))
        {
            valueTree->addParameterListener(String("delayTime" + String(i)) , voice);
            valueTree->addParameterListener(String("delayFeedback" + String(i)), voice);
            valueTree->addParameterListener(String("delayColor" + String(i)), voice);
            valueTree->addParameterListener(String("delayPan" + String(i)), voice);
            valueTree->addParameterListener(String("delayDryWet" + String(i)), voice);
            valueTree->addParameterListener(String("delaySwitch" + String(i)), voice);
            
            valueTree->addParameterListener(String("compRatio" + String(i)) , voice);
            valueTree->addParameterListener(String("compAttack" + String(i)), voice);
            valueTree->addParameterListener(String("compRelease" + String(i)), voice);
            valueTree->addParameterListener(String("compGain" + String(i)), voice);
            valueTree->addParameterListener(String("compThresh" + String(i)), voice);
            valueTree->addParameterListener(String("compSwitch" + String(i)), voice);
            
            valueTree->addParameterListener(String("reverbPredelay" + String(i)) , voice);
            valueTree->addParameterListener(String("reverbSize" + String(i)), voice);
            valueTree->addParameterListener(String("reverbColor" + String(i)), voice);
            valueTree->addParameterListener(String("reverbDecay" + String(i)), voice);
            valueTree->addParameterListener(String("reverbDry" + String(i)), voice);
            valueTree->addParameterListener(String("reverbSwitch" + String(i)), voice);
            
            valueTree->addParameterListener(String("envAttack" + String(i)) , voice);
            valueTree->addParameterListener(String("envDecay" + String(i)), voice);
            valueTree->addParameterListener(String("envHold" + String(i)), voice);
            valueTree->addParameterListener(String("envRelease" + String(i)), voice);
            
            valueTree->addParameterListener(String("envAttackBend" + String(i)) , voice);
            valueTree->addParameterListener(String("envDecayBend" + String(i)), voice);
            valueTree->addParameterListener(String("envSustain" + String(i)), voice);
            valueTree->addParameterListener(String("envReleaseBend" + String(i)), voice);
        
        }
    }
    valueTree->state = ValueTree("OrionParameters");
    
    
    
}

OrionaudioAudioProcessor::~OrionaudioAudioProcessor()
{
}


void OrionaudioAudioProcessor::createAnalyserPlot (Path& p, const Rectangle<int> bounds, float minFreq, bool input)
{
    if (input)
        inputAnalyser.createPath (p, bounds.toFloat(), minFreq);
    else
        outputAnalyser.createPath (p, bounds.toFloat(), minFreq);
}


//==============================================================================
const String OrionaudioAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OrionaudioAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OrionaudioAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OrionaudioAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OrionaudioAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OrionaudioAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OrionaudioAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OrionaudioAudioProcessor::setCurrentProgram (int index)
{
}

const String OrionaudioAudioProcessor::getProgramName (int index)
{
    return {};
}

void OrionaudioAudioProcessor::changeProgramName (int index, const String& newName)
{
}




//==============================================================================
void OrionaudioAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    const int numInputChannels = getTotalNumInputChannels();
    const int delayBufferSize = 2 * (sampleRate + samplesPerBlock);//2 seconds of delay buffer
    mDelayBuffer.setSize(numInputChannels, delayBufferSize);
    mSampleRate = sampleRate;
    synth.setCurrentPlaybackSampleRate(sampleRate);

}

void OrionaudioAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OrionaudioAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void OrionaudioAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());    
    }
    
    outputLevels.left = buffer.getRMSLevel(0, 0, buffer.getNumSamples())    ;
    outputLevels.right = buffer.getRMSLevel(1, 0, buffer.getNumSamples());

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    //inputAnalyser.addAudioData (buffer, 0, getTotalNumInputChannels());

}

//==============================================================================
bool OrionaudioAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* OrionaudioAudioProcessor::createEditor()
{
    return new OrionaudioAudioProcessorEditor (*this);
}

//==============================================================================
void OrionaudioAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    MemoryOutputStream stream(destData, false);
    valueTree->state.writeToStream(stream);
}

void OrionaudioAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    
    if(tree.isValid())
    {
        if(tree.hasType("OrionParameters"))
        {
            valueTree->state = tree;
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OrionaudioAudioProcessor();
}
