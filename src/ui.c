#include "ui.h"
#include "external/raylib/src/raylib.h"
#include "synth.h"

int run() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  const int middle = screenHeight / 2;
  const float middlef = (float)middle;
  InitWindow(screenWidth, screenHeight, "Cynth");

  SetTargetFPS(60);

  InitAudioDevice(); // Initialize audio device
  SetAudioStreamBufferSizeDefault(STREAM_BUFFER_SIZE);
  AudioStream synth_stream =
      LoadAudioStream(SAMPLE_NUMBER, sizeof(float) * 8, 1);
  PlayAudioStream(synth_stream);

  int amplitude = 100;
  float frequency = 10.0f;
  float sample_duration = 1.0f / SAMPLE_NUMBER;

  Oscillator synth_oscillator = {
      .phase = 0.0f,
      .phase_stride = frequency * sample_duration,
  };
  SetMasterVolume(0.25f);

  float synth_buffer[STREAM_BUFFER_SIZE];
  update_buffer(synth_buffer, STREAM_BUFFER_SIZE, &synth_oscillator, SINWAVE);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (IsAudioStreamProcessed(synth_stream)) {
      // update buffer
      update_buffer(synth_buffer, STREAM_BUFFER_SIZE, &synth_oscillator,
                    SINWAVE);
      // load buffer
      UpdateAudioStream(synth_stream, synth_buffer, STREAM_BUFFER_SIZE);
      frequency += 1;
      synth_oscillator.phase_stride = frequency * sample_duration;
    }
    for (int i = 0; i < screenWidth - 1; i++) {
      // DrawPixel(i, (float)(screenHeight / 2) - 100 * synth_buffer[i], RED);
      DrawLine(i, middlef - amplitude * synth_buffer[i], i + 1,
               middlef - amplitude * synth_buffer[i + 1], RED);
    }

    if (IsAudioStreamPlaying(synth_stream)) {
      DrawText(TextFormat("Freq: %f", frequency), 100, 100, 20, BLUE);
    }

    EndDrawing();
  }
  CloseAudioDevice();

  CloseWindow();
  return 0;
}
