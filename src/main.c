#include "globals.h"
#include "util.h"

typedef struct
{
	GLfloat position[3];
	GLfloat color[3];
	GLfloat texture[2];
} Vertex;

typedef struct
{
	Matrix *mesh;
	GLfloat position[3];
} Object;

const Vertex cube[36] =
{
	{
		{-1.0f, -1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 0.33f}
	},
	{
		{1.0f, -1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.5f, 0.33f}
	},
	{
		{1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.5f, 0.0f}
	},
	{
		{-1.0f, -1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 0.33f}
	},
	{
		{1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.5f, 0.0f}
	},
	{
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f}
	},
	{
		{1.0f, -1.0f, 1.0f},
		{0.0f, 1.0f, 0.0f},
		{0.5f, 0.66f}
	},
	{
		{1.0f, -1.0f, -1.0f},
		{0.0f, 1.0f, 0.0f},
		{1.0f, 0.66f}
	},
	{
		{1.0f, 1.0f, -1.0f},
		{0.0f, 1.0f, 0.0f},
		{1.0f, 0.33f}
	},
	{
		{1.0f, -1.0f, 1.0f},
		{0.0f, 1.0f, 0.0f},
		{0.5f, 0.66f}
	},
	{
		{1.0f, 1.0f, -1.0f},
		{0.0f, 1.0f, 0.0f},
		{1.0f, 0.33f}
	},
	{
		{1.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 0.0f},
		{0.5f, 0.33f}
	},
	{
		{1.0f, -1.0f, -1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.5f, 0.33f}
	},
	{
		{-1.0f, -1.0f, -1.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 0.33f}
	},
	{
		{-1.0f, 1.0f, -1.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 0.0f}
	},
	{
		{1.0f, -1.0f, -1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.5f, 0.33f}
	},
	{
		{-1.0f, 1.0f, -1.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 0.0f}
	},
	{
		{1.0f, 1.0f, -1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.5f, 0.0f}
	},
	{
		{-1.0f, -1.0f, -1.0f},
		{1.0f, 1.0f, 0.0f},
		{0.0f, 0.66f}
	},
	{
		{-1.0f, -1.0f, 1.0f},
		{1.0f, 1.0f, 0.0f},
		{0.5f, 0.66f}
	},
	{
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 0.0f},
		{0.5f, 0.33f}
	},
	{
		{-1.0f, -1.0f, -1.0f},
		{1.0f, 1.0f, 0.0f},
		{0.0f, 0.66f}
	},
	{
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 0.0f},
		{0.5f, 0.33f}
	},
	{
		{-1.0f, 1.0f, -1.0f},
		{1.0f, 1.0f, 0.0f},
		{0.0f, 0.33f}
	},
	{
		{-1.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f}
	},
	{
		{1.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.5f, 1.0f}
	},
	{
		{1.0f, 1.0f, -1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.5f, 0.66f}
	},
	{
		{-1.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f}
	},
	{
		{1.0f, 1.0f, -1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.5f, 0.66f}
	},
	{
		{-1.0f, 1.0f, -1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 0.66f}
	},
	{
		{-1.0f, -1.0f, -1.0f},
		{1.0f, 0.0f, 1.0f},
		{0.5f, 1.0f}
	},
	{
		{1.0f, -1.0f, -1.0f},
		{1.0f, 0.0f, 1.0f},
		{1.0f, 1.0f}
	},
	{
		{1.0f, -1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f},
		{1.0f, 0.66f}
	},
	{
		{-1.0f, -1.0f, -1.0f},
		{1.0f, 0.0f, 1.0f},
		{0.5f, 1.0f}
	},
	{
		{1.0f, -1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f},
		{1.0f, 0.66f}
	},
	{
		{-1.0f, -1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f},
		{0.5f, 0.66f}
	}
};

int load_texture(GLuint *texture_id, const char *filename)
{
	SDL_Surface *image = IMG_Load(filename);

	// TODO: Does it return NULL?
	if(image == NULL)
	{
		return -1;
	}

	int width = image->w, height = image->h;

	glGenTextures(1, texture_id);
	glBindTexture(GL_TEXTURE_2D, *texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	SDL_FreeSurface(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	return 0;
}

int main(int argc, char **argv)
{
	/*
	Matrix asd[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

	for(int x = 0; x < 100000000; x++)
	{
		translate(asd, 1, 1, 1);
	}

	for(int x = 0; x < 100000000; x++)
	{
		translate_fast(asd, 1, 1, 1);
	}

	return 0;
	*/

	// TEMP: Supress a warning.
	if(argc > 1)
	{
		printf("ARGUMENTS:\n");

		for(int i = 1; i < argc; i++)
		{
			printf("    %s\n", argv[i]);
		}
	}

	SDL_Window *window = NULL;
	init_window(&window, NAME_VERSION);

	GLuint vao, vbo;

	Matrix projectionMatrix[16];
	Matrix modelMatrix[16];
	const Matrix identityMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	GLuint program;

	GLuint texture_id = 0;
	int err = load_texture(&texture_id, "images/box.png");

	if(err < 0)
	{
		printf("ERR");
		return 1;
	}

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(Vertex), cube, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)offsetof(Vertex, color));
	// glEnableVertexAttribArray(1);

	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);

	load_shader(&program, "shaders/vertex.glsl", "shaders/fragment.glsl");

	glUseProgram(program);

	perspective(projectionMatrix, SCREEN_WIDTH, SCREEN_HEIGHT, 75, 0.1f, 100.0f);

	fflush(stdout);

	bool quit_game = false;
	SDL_Event event;

	/*memcpy(modelMatrix, identityMatrix, sizeof(GLfloat) * 16);
	scale(modelMatrix, 0.5f);
	translate(modelMatrix, 0, 0, -5.0);

	// NOTE: Matrix or GLfloat?/
	Matrix temp[16];
	memcpy(temp, modelMatrix, sizeof(GLfloat) * 16);*/

	int i = 0;

	Matrix viewMatrix[16];
	Vector position = {5.0f, 5.0f, 5.0f};
	Vector target = {0.0f, 0.0f, 0.0f};
	look_at(viewMatrix, position, target);

	bool is_dragging = false;

	while(quit_game == false)
	{
		// memcpy(modelMatrix, temp, sizeof(GLfloat) * 16);

		memcpy(modelMatrix, identityMatrix, sizeof(GLfloat) * 16);
		scale(modelMatrix, 0.25f);
		rotate(modelMatrix, i, 0);
		rotate(modelMatrix, i, 1);
		rotate(modelMatrix, i * 2, 2);

		//translate(modelMatrix, 0, i * 0.01, 0);

		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_QUIT)
			{
				quit_game = true;
			}
			else if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit_game = true;
					break;

					case SDLK_LEFT:
						position.x -= 0.5f;
						position.z += 0.5f;
						target.x -= 0.5f;
						target.z += 0.5f;
					break;

					case SDLK_RIGHT:
						position.x += 0.5f;
						position.z -= 0.5f;
						target.x += 0.5f;
						target.z -= 0.5f;
					break;

					case SDLK_UP:
						position.x -= 0.5f;
						position.z -= 0.5f;
						target.x -= 0.5f;
						target.z -= 0.5f;
					break;

					case SDLK_DOWN:
						position.x += 0.5f;
						position.z += 0.5f;
						target.x += 0.5f;
						target.z += 0.5f;
					break;
				}
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					// SDL_CaptureMouse(SDL_TRUE);
					SDL_SetRelativeMouseMode(SDL_TRUE);
					is_dragging = true;
				}
			}
			else if(event.type == SDL_MOUSEBUTTONUP)
			{
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					// SDL_CaptureMouse(SDL_FALSE);
					// TODO: Set mouse to block position.
					SDL_SetRelativeMouseMode(SDL_FALSE);
					is_dragging = false;
				}
			}
			else if(is_dragging == true && event.type == SDL_MOUSEMOTION)
			{
				// TODO: Move relative to zoom level.
				position.x -= event.motion.xrel * 0.007f;
				position.z += event.motion.xrel * 0.007f;
				target.x -= event.motion.xrel * 0.007f;
				target.z += event.motion.xrel * 0.007f;

				position.x -= event.motion.yrel * 0.007f;
				position.z -= event.motion.yrel * 0.007f;
				target.x -= event.motion.yrel * 0.007f;
				target.z -= event.motion.yrel * 0.007f;
			}
			else if(event.type == SDL_MOUSEWHEEL)
			{
				Vector dir = {target.x - position.x, target.y - position.y, target.z - position.z};
				normalize(dir);

				if(event.wheel.y < 0)
				{
					position.x -= dir.x * 0.15f;
					position.y -= dir.y * 0.15f;
					position.z -= dir.z * 0.15f;
				}
				else
				{
					position.x += dir.x * 0.15f;
					position.y += dir.y * 0.15f;
					position.z += dir.z * 0.15f;
				}
			}
		}
		
		i++;

		memcpy(viewMatrix, identityMatrix, sizeof(GLfloat) * 16);

		look_at(viewMatrix, position, target);

		multiply(modelMatrix, viewMatrix);
		multiply(modelMatrix, projectionMatrix);

		glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, GL_FALSE, modelMatrix);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		SDL_GL_SwapWindow(window);

		// SDL_Delay(16);
	}

	return 0;
}
