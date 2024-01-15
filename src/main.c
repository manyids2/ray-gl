#include "includes.h"
#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

GLuint VAO, VBO, EBO;
int rows = 2;
int cols = 5;

// Function to initialize VAO, VBO, and EBO
// for a grid with color and texture coords
void initGrid(int r, int c, Rectangle rec, Rectangle size) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  // Each vertex now has 5 floats:
  // 1 for index, 2 for top left, 2 for size
  int numVertices = r * c;
  int sumAttribs = 4;
  float *vertices = (float *)malloc(numVertices * sumAttribs * sizeof(float));
  int idx = 0;
  float spacing = 0.5;

  for (int i = 0; i < c; ++i) {
    for (int j = 0; j < r; ++j) {
      // Rectangle of texture coordinates
      vertices[idx++] = i * spacing;
      vertices[idx++] = j * spacing;
      vertices[idx++] = (rec.x) / size.width;
      vertices[idx++] = (rec.y) / size.height;
      printf("%d: %f, %f; %f, %f\n", idx, vertices[idx - 4], vertices[idx - 3],
             vertices[idx - 2], vertices[idx - 1]);

      // Top-right corner
      vertices[idx++] = (i + 1) * spacing;
      vertices[idx++] = j * spacing;
      vertices[idx++] = (rec.x + rec.width) / size.width;
      vertices[idx++] = (rec.y) / size.height;
      printf("%d: %f, %f; %f, %f\n", idx, vertices[idx - 4], vertices[idx - 3],
             vertices[idx - 2], vertices[idx - 1]);

      // Bottom-right corner
      vertices[idx++] = (i + 1) * spacing;
      vertices[idx++] = (j + 1) * spacing;
      vertices[idx++] = (rec.x + rec.width) / size.width;
      vertices[idx++] = (rec.y + rec.height) / size.height;
      printf("%d: %f, %f; %f, %f\n", idx, vertices[idx - 4], vertices[idx - 3],
             vertices[idx - 2], vertices[idx - 1]);

      // Bottom-left corner
      vertices[idx++] = i * spacing;
      vertices[idx++] = (j + 1) * spacing;
      vertices[idx++] = (rec.x) / size.width;
      vertices[idx++] = (rec.y + rec.height) / size.height;
      printf("%d: %f, %f; %f, %f\n", idx, vertices[idx - 4], vertices[idx - 3],
             vertices[idx - 2], vertices[idx - 1]);
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sumAttribs * sizeof(float),
               vertices, GL_STATIC_DRAW);
  free(vertices);

  // texcoord -> x, y
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sumAttribs * sizeof(float),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sumAttribs * sizeof(float),
                        (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Calculate the number of indices
  int numIndices = (r - 1) * (c - 1) * 6;
  GLuint *indices = (GLuint *)malloc(numIndices * sizeof(GLuint));
  idx = 0;

  for (int i = 0; i < r - 1; ++i) {
    for (int j = 0; j < c - 1; ++j) {
      int start = i * c + j;
      indices[idx++] = start;
      indices[idx++] = start + 1;
      indices[idx++] = start + c;

      indices[idx++] = start + 1;
      indices[idx++] = start + 1 + c;
      indices[idx++] = start + c;
    }
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices,
               GL_STATIC_DRAW);
  free(indices);
}

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  Font font =
      LoadFontEx("fonts/FiraCode/FiraCodeNerdFont-Bold.ttf", 32, 0, 250);
  Shader shader = LoadShader(TextFormat("shaders/text.vs", GLSL_VERSION),
                             TextFormat("shaders/text.fs", GLSL_VERSION));

  // Save glyph rectangle to vertices buffer
  int character = 'A'; // Replace with your desired character
  // GlyphInfo glyphInfo = GetGlyphInfo(font, character);
  Rectangle sourceRec = GetGlyphAtlasRec(font, character);

  // Get size of texture
  Rectangle sourceSize = GetGlyphAtlasRec(font, character);
  sourceSize.x = 0;
  sourceSize.y = 0;
  sourceSize.width = font.texture.width;
  sourceSize.height = font.texture.height;

  // // Destination rectangle for the texture
  // Rectangle destRec = {200, 250, glyphInfo.image.width,
  // glyphInfo.image.height};

  glBindTexture(GL_TEXTURE_2D, font.texture.id);
  initGrid(rows, cols, sourceRec, sourceSize);

  while (!WindowShouldClose()) {
    BeginDrawing();

    glClearColor(0.5, 0.1, 0.1, 0.7); // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT);

    BeginShaderMode(shader);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, rows * cols * 6, GL_UNSIGNED_INT, 0);
    EndShaderMode();

    EndDrawing();
  }

  // Reset buffers?
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  CloseWindow();

  return 0;
}
