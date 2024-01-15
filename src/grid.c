#include "grid.h"
#include <stdio.h>

void grid_setup(grid_t *g, int nrows, int ncols) {
  g->nrows = nrows;
  g->ncols = ncols;
  g->ncells = nrows * ncols;
  g->nvertices = g->ncells * 4;
  g->nindices = g->ncells * 6;
  g->nattribs = 2;
  g->sumattribs = 4;
}

void grid_print(grid_t *g) {
  printf("Grid :\n"
         "  nrows:      %d\n"
         "  ncols:      %d\n"
         "  ncells:     %d\n"
         "  nvertices:  %d\n"
         "  nindices:   %d\n"
         "  nattribs:   %d\n"
         "  sumattribs: %d\n",
         g->nrows, g->ncols, g->ncells, g->nvertices, g->nindices, g->nattribs,
         g->sumattribs);
}

void vertices_setup(vertices_t *v, grid_t *g) {
  float spacing = 0.5;
  v->vertices = (float *)malloc(g->nvertices * g->sumattribs * sizeof(float));

  int idx = 0;
  for (int i = 0; i < g->nrows; ++i) {
    for (int j = 0; j < g->ncols; ++j) {
      // Top-right corner
      v->vertices[idx++] = -0.5 + ((i + 1) * spacing);
      v->vertices[idx++] = -0.5 + ((j + 1) * spacing);
      v->vertices[idx++] = 1.0;
      v->vertices[idx++] = 1.0;

      // Bottom-right corner
      v->vertices[idx++] = -0.5 + ((i + 1) * spacing);
      v->vertices[idx++] = -0.5 + (j * spacing);
      v->vertices[idx++] = 1.0;
      v->vertices[idx++] = 0.0;

      // Bottom-left
      v->vertices[idx++] = -0.5 + (i * spacing);
      v->vertices[idx++] = -0.5 + (j * spacing);
      v->vertices[idx++] = 0.0;
      v->vertices[idx++] = 0.0;

      // Top-left corner
      v->vertices[idx++] = -0.5 + (i * spacing);
      v->vertices[idx++] = -0.5 + ((j + 1) * spacing);
      v->vertices[idx++] = 0.0;
      v->vertices[idx++] = 1.0;
    }
  }

  // Calculate the number of indices
  v->indices = (GLuint *)malloc(g->nindices * sizeof(GLuint));
  idx = 0;
  for (int i = 0; i < g->nrows; ++i) {
    for (int j = 0; j < g->ncols; ++j) {
      int start = (j * g->nrows + i) * 4;
      v->indices[idx++] = start;     // ◿ : Top-right
      v->indices[idx++] = start + 2; //     Bottom-left
      v->indices[idx++] = start + 1; //     Bottom-right

      v->indices[idx++] = start;     // ◸ : Top-right
      v->indices[idx++] = start + 3; //   : Top-left
      v->indices[idx++] = start + 2; //   : Bottom-left
    }
  }
}

void vertices_print(vertices_t *v) {
  printf("Vertices :\n"
         "  VAO: %d\n"
         "  VBO: %d\n"
         "  EBO: %d\n",
         v->VAO, v->VBO, v->EBO);
}

void vertices_print_buffers(vertices_t *v, grid_t *g) {
  // vertices
  printf("Vertices :\n");
  for (int i = 0; i < g->nvertices * 4; i += 4) {
    printf("  %04d: %+02.2f, %+02.2f, %+02.2f, %+02.2f\n", i / 4,
           v->vertices[i], v->vertices[i + 1], v->vertices[i + 2],
           v->vertices[i + 3]);
  }

  // indices
  printf("Indices :\n");
  for (int i = 0; i < g->nindices; i += 6) {
    printf("  %04d: %03d, %03d, %03d, %03d, %03d, %03d\n", i / 6, v->indices[i],
           v->indices[i + 1], v->indices[i + 2], v->indices[i + 3],
           v->indices[i + 4], v->indices[i + 5]);
  }
}

void vertices_setup_gl(vertices_t *v, grid_t *g) {
  // Generate buffers and bind VAO before VBO, EBO
  glGenVertexArrays(1, &v->VAO);
  glGenBuffers(1, &v->VBO);
  glGenBuffers(1, &v->EBO);
  glBindVertexArray(v->VAO);

  // VBO -> vertices
  glBindBuffer(GL_ARRAY_BUFFER, v->VBO);
  glBufferData(GL_ARRAY_BUFFER, g->nvertices * g->sumattribs * sizeof(float),
               v->vertices, GL_STATIC_DRAW);

  // EBO -> indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, g->nindices * sizeof(GLuint),
               v->indices, GL_STATIC_DRAW);

  // layout (location = 0) in vec2 aPos;
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, g->sumattribs * sizeof(float),
                        (void *)0);
  glEnableVertexAttribArray(0);

  // layout (location = 1) in vec2 aTex;
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, g->sumattribs * sizeof(float),
                        (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void vertices_free_gl(vertices_t *v) {
  glDeleteVertexArrays(1, &v->VAO);
  glDeleteBuffers(1, &v->VBO);
  glDeleteBuffers(1, &v->EBO);
}

void vertices_free(vertices_t *v) {
  if (v->vertices) {
    free(v->vertices);
  }
  if (v->indices) {
    free(v->indices);
  }
}
