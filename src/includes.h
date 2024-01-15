#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(PLATFORM_DESKTOP)
#if defined(GRAPHICS_API_OPENGL_ES2)
#include "glad_gles2.h" // Required for: OpenGL functionality
#define glGenVertexArrays glGenVertexArraysOES
#define glBindVertexArray glBindVertexArrayOES
#define glDeleteVertexArrays glDeleteVertexArraysOES
#define GLSL_VERSION 100
#else
#if defined(__APPLE__)
#include <OpenGL/gl3.h>    // OpenGL 3 library for OSX
#include <OpenGL/gl3ext.h> // OpenGL 3 extensions library for OSX
#else
#include "glad.h" // Required for: OpenGL functionality
#endif
#define GLSL_VERSION 330
#endif
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

#include "raymath.h" // Required for: MatrixMultiply(), MatrixToFloat()
#include "rlgl.h" // Required for: rlDrawRenderBatchActive(), rlGetMatrixModelview(), rlGetMatrixProjection()
#include <stdio.h>
#include <stdlib.h>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif
