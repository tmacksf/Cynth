#include "synth.h"
#include <math.h>
#include <stdio.h>

SynthWave *initSynthWave(float frequency) {
  SynthWave *synthwave = malloc(sizeof(SynthWave));

  float sample_duration = 1.0f / SAMPLE_NUMBER;

  Oscillator synth_oscillator = {.phase = 0.0f,
                                 .phaseStride = frequency * sample_duration};

  synthwave->oscillator = synth_oscillator;
  synthwave->signalSize = STREAM_BUFFER_SIZE;
  synthwave->signal = malloc(sizeof(float) * STREAM_BUFFER_SIZE);
  synthwave->frequency = frequency;
  // synthwave->sample_duration = sample_duration;

  return synthwave;
}

void updateFrequency(SynthWave *wav, float frequency) {
  wav->frequency = frequency;
  wav->oscillator.phaseStride = frequency * SAMPLE_NUMBER;
}
void incrementFrequency(SynthWave *wav, float increment) {
  wav->frequency += increment;
  wav->oscillator.phaseStride = wav->frequency / SAMPLE_NUMBER;
}

float sinWav(Oscillator *o) { return sinf(2.0f * PI * o->phase); }

float squareWave(Oscillator *o) {
  return sinf(2.0f * PI * o->phase) > 0 ? 1 : -1;
}

float sawWave(Oscillator *o) { return 0.0f; }

void updateSynthBuffer(SynthWave *sw, WaveType wav) {
  for (int i = 0; i < sw->signalSize; i++) {
    sw->oscillator.phase += sw->oscillator.phaseStride;
    if (sw->oscillator.phase >= 1.0f)
      sw->oscillator.phase -= 1.0f;
    switch (wav) {
    case SINWAVE:
      sw->signal[i] = sinWav(&sw->oscillator);
      break;
    case SQUAREWAVE:
      sw->signal[i] = squareWave(&sw->oscillator);
      break;
    case SAWWAVE:
      sw->signal[i] = sawWave(&sw->oscillator);
      break;
    case TRIANGLEWAVE:
      break;
    }
  }
}
