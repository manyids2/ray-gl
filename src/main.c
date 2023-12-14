#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  Shader shader = LoadShader(TextFormat("shaders/basic.vs", GLSL_VERSION),
                             TextFormat("shaders/basic.fs", GLSL_VERSION));

  Texture2D texture =
      LoadTexture(ASSETS_PATH "test.png"); // Check README.md for how this works

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
    const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;

    BeginShaderMode(shader);
    DrawTexture(texture, texture_x, texture_y, WHITE);
    EndShaderMode();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
