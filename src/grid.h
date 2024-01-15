#include "includes.h"

typedef struct grid_t {
  int nrows;
  int ncols;
  int ncells;
  int nvertices;
  int nindices;
  int nattribs;
  int sumattribs;
} grid_t;

typedef struct vertices_t {
  float *vertices;
  GLuint *indices;
  GLuint VAO, VBO, EBO;
} vertices_t;

void grid_setup(grid_t *g, int nrows, int ncols);
void grid_print(grid_t *g);
void vertices_setup(vertices_t *v, grid_t *g);
void vertices_print(vertices_t *v);
void vertices_print_buffers(vertices_t *v, grid_t *g);
void vertices_setup_gl(vertices_t *v, grid_t *g);
void vertices_free_gl(vertices_t *v);
void vertices_free(vertices_t *v);
