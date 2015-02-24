#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

#define NAME_VERSION "Theseus 0.15.02.24"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef GLfloat Matrix;

typedef void (APIENTRY * GL_BindBuffer)(GLenum target, GLuint buffer);
typedef void (APIENTRY * GL_AttachShader)(GLuint program, GLuint shader);
typedef void (APIENTRY * GL_DetachShader)(GLuint program, GLuint shader);
typedef void (APIENTRY * GL_LinkProgram)(GLuint program);
typedef void (APIENTRY * GL_GetProgramiv)(GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRY * GL_DeleteProgram)(GLuint program);
typedef void (APIENTRY * GL_CompileShader)(GLuint shader);
typedef void (APIENTRY * GL_ShaderSource)(GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length);
typedef void (APIENTRY * GL_GetShaderiv)(GLuint shader, GLenum pname, GLint *params);
typedef GLuint (APIENTRY * GL_CreateShader)(GLenum shaderType);
typedef void (APIENTRY * GL_DeleteShader)(GLuint shader);
typedef void (APIENTRY * GL_UseProgram)(GLuint program);
typedef GLuint (APIENTRY * GL_CreateProgram)();
typedef void (APIENTRY * GL_GenBuffers)(GLsizei n, GLuint *buffers);
// NOTE: Pointer.
typedef void (APIENTRY * GL_BufferData)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
typedef void (APIENTRY * GL_EnableVertexAttribArray)(GLuint index);
typedef void (APIENTRY * GL_GenVertexArrays)(GLsizei n, GLuint *arrays);
typedef void (APIENTRY * GL_BindVertexArray)(GLuint array);
typedef void (APIENTRY * GL_VertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * GL_BindAttribLocation)(GLuint program, GLuint index, const GLchar *name);
typedef void (APIENTRY * GL_GetShaderInfoLog)(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRY * GL_UniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef GLint (APIENTRY * GL_GetUniformLocation)(GLuint program, const GLchar *name);

// TODO: Initialize to NULL.
GL_BindBuffer glBindBuffer;
GL_AttachShader glAttachShader;
GL_LinkProgram glLinkProgram;
GL_GetProgramiv glGetProgramiv;
GL_DeleteProgram glDeleteProgram;
GL_DetachShader glDetachShader;
GL_CompileShader glCompileShader;
GL_ShaderSource glShaderSource;
GL_GetShaderiv glGetShaderiv;
GL_CreateShader glCreateShader;
GL_DeleteShader glDeleteShader;
GL_UseProgram glUseProgram;
GL_CreateProgram glCreateProgram;
GL_GenBuffers glGenBuffers;
GL_BufferData glBufferData;
GL_EnableVertexAttribArray glEnableVertexAttribArray;
GL_GenVertexArrays glGenVertexArrays;
GL_BindVertexArray glBindVertexArray;
GL_VertexAttribPointer glVertexAttribPointer;
GL_BindAttribLocation glBindAttribLocation;
GL_GetShaderInfoLog glGetShaderInfoLog;
GL_UniformMatrix4fv glUniformMatrix4fv;
GL_GetUniformLocation glGetUniformLocation;

void print_log(const char *summary, const char *details);

#endif
