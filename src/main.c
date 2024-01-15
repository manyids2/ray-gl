#include "includes.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

int main(void) {
  // Define grid dimensions
  const int rows = 10;
  const int cols = 10;
  const float spacing = 50.0f;

  // Calculate total vertices
  int totalVertices = rows * cols;
  Vector3 *vertices = (Vector3 *)malloc(totalVertices * sizeof(Vector3));

  // Populate the vertex array
  for (int x = 0; x < cols; ++x) {
    for (int y = 0; y < rows; ++y) {
      vertices[y * cols + x] = (Vector3){x * spacing, y * spacing, 0.0f};
    }
  }

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  // Create a mesh and assign vertices
  Mesh gridMesh = {0};
  gridMesh.vertexCount = totalVertices;
  gridMesh.vertices = (float *)vertices;
  UploadMesh(&gridMesh, false);

  Texture2D texture =
      LoadTexture(ASSETS_PATH "test.png"); // Check README.md for how this works
  Font font =
      LoadFontEx("fonts/FiraCode/FiraCodeNerdFont-Bold.ttf", 32, 0, 250);
  Shader shader = LoadShader(TextFormat("shaders/text.vs", GLSL_VERSION),
                             TextFormat("shaders/text.fs", GLSL_VERSION));

  // Get glyph info for a specific character
  int character = 'A'; // Replace with your desired character
  GlyphInfo glyphInfo = GetGlyphInfo(font, character);

  // Get glyph atlas rectangle
  Rectangle sourceRec = GetGlyphAtlasRec(font, character);

  // Destination rectangle for the texture
  Rectangle destRec = {200, 250, glyphInfo.image.width, glyphInfo.image.height};

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
    const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;

    BeginShaderMode(shader);
    DrawTexture(texture, texture_x, texture_y, WHITE);
    EndShaderMode();

    glClearColor(0.5, 0.1, 0.1, 0.7); // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw text using the TTF font
    DrawTextEx(font, "AAA!", (Vector2){190, 200}, font.baseSize, 2, BLACK);

    // Draw the single character texture
    DrawTexturePro(font.texture, sourceRec, destRec, (Vector2){0, 0}, 0.0f,
                   BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
