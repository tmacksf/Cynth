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
  float phase_stride;
} Oscillator;

typedef struct {
  float frequency;
  float sample_duration;
  struct Oscillator o;
} SynthWave;

typedef enum WaveType {
  SINWAVE,
  SAWWAVE,
  // TODO: More types

} WaveType;

// waves
float sin_wav(Oscillator *o);

float saw_wav(Oscillator *o);
// update
// TODO: This will become a sin wav
void update_buffer(float *signal, int signalSize, Oscillator *o, WaveType wav);

#endif
