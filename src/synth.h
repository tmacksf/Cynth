#ifndef SYNTH_H
#define SYNTH_H

#include "external/raylib/src/raylib.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// number of samples per second
#define SAMPLE_NUMBER 44100
// buffer size of the samples
#define STREAM_BUFFER_SIZE 1024

typedef struct Oscillator {
  float phase;
  float phaseStride;
} Oscillator;

typedef enum WaveType {
  SINWAVE,
  SAWWAVE,
  SQUAREWAVE,
  TRIANGLEWAVE,
} WaveType;

typedef struct SynthWave {
  // TODO: Figure out if i want to add a wavetype enum in this
  float frequency;
  // float sample_duration;
  float *signal;
  int signalSize;
  struct Oscillator oscillator;
} SynthWave;

SynthWave *initSynthWave(float frequency);

void updateFrequency(SynthWave *wav, float frequency);

void incrementFrequency(SynthWave *wav, float increment);

// waves
float sinWave(Oscillator *o);

float sawWave(Oscillator *o);

float squareWave(Oscillator *o);

// update
void updateSynthBuffer(SynthWave *sw, WaveType wav);

#endif
