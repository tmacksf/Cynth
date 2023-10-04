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
  SetMasterVolume(0.25f);
  SynthWave *synthWave = initSynthWave(10.0f);

  updateSynthBuffer(synthWave, SQUAREWAVE);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (IsAudioStreamProcessed(synth_stream)) {
      // update buffer
      updateSynthBuffer(synthWave, SQUAREWAVE);
      // load buffer
      UpdateAudioStream(synth_stream, synthWave->signal, STREAM_BUFFER_SIZE);
      incrementFrequency(synthWave, 1.0f);
    }

    // drawing line
    for (int i = 0; i < screenWidth - 1; i++) {
      // DrawPixel(i, (float)(screenHeight / 2) - 100 * synth_buffer[i], RED);
      DrawLine(i, middlef - amplitude * synthWave->signal[i], i + 1,
               middlef - amplitude * synthWave->signal[i + 1], RED);
    }

    if (IsAudioStreamPlaying(synth_stream)) {
      DrawText(TextFormat("Freq: %f", synthWave->frequency), 100, 100, 20,
               BLUE);
    }

    EndDrawing();
  }
  CloseAudioDevice();

  CloseWindow();
  return 0;
}
