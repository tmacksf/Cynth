#include "synth.h"
#include <math.h>

float sin_wav(Oscillator *o) { return sinf(2.0f * PI * o->phase); }

float saw_wav(Oscillator *o) { return 0.0f; }

void update_buffer(float *signal, int signalSize, Oscillator *o, WaveType wav) {
  for (int i = 0; i < signalSize; i++) {
    o->phase += o->phase_stride;
    if (o->phase >= 1.0f)
      o->phase -= 1.0f;
    switch (wav) {
    case SINWAVE:
      signal[i] = sin_wav(o);
      break;
    case SAWWAVE:
      signal[i] = saw_wav(o);
      break;
    }
  }
}
