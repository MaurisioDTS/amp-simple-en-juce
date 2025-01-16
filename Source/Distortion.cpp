#include "../JuceLibraryCode/JuceHeader.h"
#include "Distortion.h"

//==============================================================================
Distortion::Distortion(AudioProcessorValueTreeState& vt)
    : mParameters(vt),
    mSelector(0) // Inicializamos el selector
{
    mOversampling.reset(new dsp::Oversampling<float>(2, 3, dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, false));

    // Define las funciones de onda
    mWaveFunctions = {
        [](float x) { return std::tanh(7.0f * x); },               // Función 0
        [](float x) {
            float highFreqBoost = x - 0.8f * std::tanh(x); // Atenúa bajas frecuencias
            float emphasized = x + 0.4f * (highFreqBoost - x); // Realza los agudos
            emphasized = emphasized * 1.2f; // Amplifica la señal
            return std::clamp(emphasized, -0.9f, 0.9f);
        },         // Función 1
        [](float x) { return std::clamp(x, -0.5f, 0.5f); }         // Función 2
    };

    // Configura una función de onda inicial
    mCurrentWaveFunction = mWaveFunctions[0];
}

Distortion::~Distortion()
{
    // Destructor vacío
}

void Distortion::prepare(dsp::ProcessSpec spec)
{
    mSampleRate = static_cast<float>(spec.sampleRate);
    mMaxBlockSize = spec.maximumBlockSize;
    mNumChannels = spec.numChannels;

    mInputVolume.prepare(spec);
    mOutputVolume.prepare(spec);

    mOversampling->initProcessing(static_cast<size_t>(mMaxBlockSize));
    reset();
}

void Distortion::reset()
{
    mOversampling->reset();
}

void Distortion::process(dsp::ProcessContextReplacing<float> context)
{
    ScopedNoDenormals noDenormals;

    mInputVolume.process(context);

    // Upsample
    dsp::AudioBlock<float> oversampledBlock = mOversampling->processSamplesUp(context.getInputBlock());

    // Aplica la función de onda actual manualmente
    for (size_t channel = 0; channel < oversampledBlock.getNumChannels(); ++channel)
    {
        auto* samples = oversampledBlock.getChannelPointer(channel);

        for (size_t sampleIndex = 0; sampleIndex < oversampledBlock.getNumSamples(); ++sampleIndex)
        {
            samples[sampleIndex] = mCurrentWaveFunction(samples[sampleIndex]);
        }
    }

    oversampledBlock *= 0.7f; // Escala el volumen después del procesamiento

    // Downsample
    mOversampling->processSamplesDown(context.getOutputBlock());

    mOutputVolume.process(context);
}


void Distortion::updateParameters()
{
    float inputVolume = *mParameters.getRawParameterValue(IDs::inputVolume);
    float outputVolume = *mParameters.getRawParameterValue(IDs::outputVolume);
    int selector = static_cast<int>(*mParameters.getRawParameterValue(IDs::selector));

    auto inputdB = Decibels::decibelsToGain(inputVolume);
    auto outputdB = Decibels::decibelsToGain(outputVolume);

    if (mInputVolume.getGainLinear() != inputdB) mInputVolume.setGainLinear(inputdB);
    if (mOutputVolume.getGainLinear() != outputdB) mOutputVolume.setGainLinear(outputdB);

    // Actualiza la función de onda según el selector
    if (selector >= 0 && selector < mWaveFunctions.size())
    {
        mCurrentWaveFunction = mWaveFunctions[selector];
    }
}
