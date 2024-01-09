/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class EQlzrAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    EQlzrAudioProcessor();
    ~EQlzrAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // # Safak Onol
    static juce::AudioProcessorValueTreeState::ParameterLayout CreateParameterLayout();
    juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", CreateParameterLayout() };
    // #-- Safak Onol
private:

    // # Safak Onol
    
    using Filter = juce::dsp::IIR::Filter<float>; // IIR:Filter has a 12 db/Oct response when configured as low pass or highpass
                                                  
    using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>; // If we need a chain with a response of 48 db/Oct, then we need to define 4 filters

    using MonoChain = juce::dsp::ProcessorChain<CutFilter, Filter, CutFilter>; // MonoChain: LowCut -> Parametric -> HighCut

    MonoChain leftChain, rightChain; // filter instances to create Stereo

    // #-- Safak Onol

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQlzrAudioProcessor)
};
