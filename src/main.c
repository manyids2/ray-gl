#include "grid.h"
#include "raylib.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  grid_t g = {0};
  grid_setup(&g, 1, 1);
  grid_print(&g);

  vertices_t v = {0};
  vertices_setup(&v, &g);
  vertices_setup_gl(&v, &g);
  vertices_print(&v);
  vertices_print_buffers(&v, &g);

  // Shaders
  Shader shader = LoadShader(TextFormat("shaders/text.vs", GLSL_VERSION),
                             TextFormat("shaders/text.fs", GLSL_VERSION));

  // Font
  int fontSize = 32;
  Font font = LoadFontEx("fonts/FiraCode/FiraCodeNerdFont-Regular.ttf",
                         fontSize, 0, 250);

  // Load PNG image
  Image image = LoadImage("assets/test.png"); // Replace with your image path
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image); // Image data is no longer needed after texture creation

  // clang-format off
  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(GRAY);

    glUseProgram(shader.id);
      glBindTexture(GL_TEXTURE_2D, texture.id);
      glBindVertexArray(v.VAO);
      glDrawElements(GL_TRIANGLES, g.nindices, GL_UNSIGNED_INT, 0);
    glUseProgram(0);
    // DrawTexture(texture, 0, 0, DARKGREEN);

    EndDrawing();
  }
  // clang-format on

  vertices_free_gl(&v);
  vertices_free(&v);

  CloseWindow();

  return 0;
}
