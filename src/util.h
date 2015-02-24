#ifndef UTIL_H
#define UTIL_H

#include <math.h>

#include "globals.h"

#define PI 3.14159265358979323846

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Vector;

void init_window(SDL_Window **window, const char *window_title);
void load_extensions();
void load_shader(GLuint *shader_program, const char *vs_filename, const char *fs_filename);
void print_matrix(const Matrix *matrix);

void multiply(Matrix *m1, Matrix *m2);
void translate(Matrix *matrix, float x, float y, float z);
void rotate(Matrix *matrix, GLfloat angle, uint8_t axis);
void scale(Matrix *matrix, float factor);
void perspective(Matrix *matrix, uint16_t width, uint16_t height, uint8_t fov_x, float near_z, float far_z);
void look_at(Matrix *matrix, Vector position, Vector target);

GLfloat dot(Vector v1, Vector v2);
Vector cross(Vector v1, Vector v2);
GLfloat length(Vector vector);
Vector normalize(Vector vector);

void multiply_slow(Matrix *m1, Matrix *m2);

#endif
