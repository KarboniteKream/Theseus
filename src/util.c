#include "util.h"

void init_window(SDL_Window **window, const char *window_title)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "An error has occurred while initializing SDL.", NULL);
		exit(1);
	}

	// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	*window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(*window == NULL)
	{
		puts(SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "An error has occured while creating the window.", NULL);
		exit(1);
	}

	SDL_SetWindowIcon(*window, SDL_LoadBMP("images/icon.bmp"));

	if(SDL_GL_CreateContext(*window) == NULL)
	{
		puts(SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "An error has occured while creating the OpenGL context.", NULL);
		exit(1);
	}

	SDL_GL_SetSwapInterval(1);
	SDL_ShowCursor(SDL_ENABLE);

	load_extensions();

	//glOrtho(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
}

void load_extensions()
{
	glBindBuffer = (GL_BindBuffer)SDL_GL_GetProcAddress("glBindBuffer");
	glCreateShader = (GL_CreateShader)SDL_GL_GetProcAddress("glCreateShader");
	glAttachShader = (GL_AttachShader)SDL_GL_GetProcAddress("glAttachShader");
	glLinkProgram = (GL_LinkProgram)SDL_GL_GetProcAddress("glLinkProgram");
	glGetProgramiv = (GL_GetProgramiv)SDL_GL_GetProcAddress("glGetProgramiv");
	glDeleteProgram = (GL_DeleteProgram)SDL_GL_GetProcAddress("glDeleteProgram");
	glDetachShader = (GL_DetachShader)SDL_GL_GetProcAddress("glDetachShader");
	glCompileShader = (GL_CompileShader)SDL_GL_GetProcAddress("glCompileShader");
	glShaderSource = (GL_ShaderSource)SDL_GL_GetProcAddress("glShaderSource");
	glGetShaderiv = (GL_GetShaderiv)SDL_GL_GetProcAddress("glGetShaderiv");
	glDeleteShader = (GL_DeleteShader)SDL_GL_GetProcAddress("glDeleteShader");
	glUseProgram = (GL_UseProgram)SDL_GL_GetProcAddress("glUseProgram");
	glCreateProgram = (GL_CreateProgram)SDL_GL_GetProcAddress("glCreateProgram");
	glGenBuffers = (GL_GenBuffers)SDL_GL_GetProcAddress("glGenBuffers");
	glBufferData = (GL_BufferData)SDL_GL_GetProcAddress("glBufferData");
	glEnableVertexAttribArray = (GL_EnableVertexAttribArray)SDL_GL_GetProcAddress("glEnableVertexAttribArray");
	glGenVertexArrays = (GL_GenVertexArrays)SDL_GL_GetProcAddress("glGenVertexArrays");
	glBindVertexArray = (GL_BindVertexArray)SDL_GL_GetProcAddress("glBindVertexArray");
	glVertexAttribPointer = (GL_VertexAttribPointer)SDL_GL_GetProcAddress("glVertexAttribPointer");
	glBindAttribLocation = (GL_BindAttribLocation)SDL_GL_GetProcAddress("glBindAttribLocation");
	glGetShaderInfoLog = (GL_GetShaderInfoLog)SDL_GL_GetProcAddress("glGetShaderInfoLog");
	glUniformMatrix4fv = (GL_UniformMatrix4fv)SDL_GL_GetProcAddress("glUniformMatrix4fv");
	glGetUniformLocation = (GL_GetUniformLocation)SDL_GL_GetProcAddress("glGetUniformLocation");
}

// TODO: Change variable names to underscores.
void load_shader(GLuint *shader_program, const char *vs_filename, const char *fs_filename)
{
	//printLog(0, "Loading vertex shader", vsFilename);
	//printLog(0, "Loading fragment shader", fsFilename);

	// TODO: Change to global function.
	FILE *vsFile = fopen(vs_filename, "r");

	// TODO: Better error handling, fallback shader.
	if(vsFile == NULL)
	{
		// printLog(1, "Unable to open vertex shader:", vsFilename);
		exit(1);
	}

	FILE *fsFile = fopen(fs_filename, "r");

	if(fsFile == NULL)
	{
		// printLog(1, "Unable to open fragment shader:", fs_filename);
		exit(1);
	}

	// NOTE: Should fopen() have an argument "a", so there is no need to fseek()?
	fseek(vsFile, 0, SEEK_END);
	fseek(fsFile, 0, SEEK_END);

	long vsLength = ftell(vsFile);
	long fsLength = ftell(fsFile);

	fseek(vsFile, 0, SEEK_SET);
	fseek(fsFile, 0, SEEK_SET);

	// TODO: malloc for better performance.
	GLchar *vsSource = (GLchar *)calloc(vsLength + 1, sizeof(GLchar));
	GLchar *fsSource = (GLchar *)calloc(fsLength + 1, sizeof(GLchar));

	fread(vsSource, sizeof(GLchar), vsLength, vsFile);
	fclose(vsFile);

	fread(fsSource, sizeof(GLchar), fsLength, fsFile);
	fclose(fsFile);

	GLint compileStatus = GL_TRUE;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar **)&vsSource, NULL);
	glCompileShader(vertexShader);
	free(vsSource);

	// TODO: Add a message on successful compilation.
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus == GL_FALSE)
	{
		printf("Unable to compile vertex shader.\n");
		//printLog(1, "Unable to compile vertex shader: ", vsFilename);
		//printInfoLog(vertexShader);
		GLsizei maxLength, length = 0;
		length = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
		char *infoLog = (char *)malloc(maxLength * sizeof(char));

		printf("%s\n", infoLog);
		glDeleteShader(vertexShader);
	}

	//printLog(0, "OK!", vsFilename);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar **)&fsSource, NULL);
	glCompileShader(fragmentShader);
	free(fsSource);

	// TODO: Add a message on successful compilation.
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus == GL_FALSE)
	{
		printf("Unable to compile fragment shader.\n");
		//printLog(1, "Unable to compile fragment shader: ", fsFilename);
		//printInfoLog(fragmentShader);
		GLsizei maxLength, length = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
		char *infoLog = (char *)malloc(maxLength * sizeof(char));
		glGetShaderInfoLog(fragmentShader, maxLength, &length, infoLog);

		if(length > 0)
		{
			printf("%s\n", infoLog);
		}
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
	}

	//printLog(0, "OK!", fsFilename);

	//glUseProgram(*shader_program);
	*shader_program = glCreateProgram();

	// NOTE: What to do if vertexShader is deleted?
	glAttachShader(*shader_program, vertexShader);
	glAttachShader(*shader_program, fragmentShader);

	glBindAttribLocation(*shader_program, 0, "in_Position");
	glBindAttribLocation(*shader_program, 1, "in_Texture");

	glLinkProgram(*shader_program);

	GLint linkStatus;
	glGetProgramiv(*shader_program, GL_LINK_STATUS, &linkStatus);

	if(linkStatus == GL_FALSE)
	{
		//printInfoLog(*shader_program);
		glDeleteProgram(*shader_program);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	//glDetachShader(*shader_program, vertexShader);
	//glDetachShader(*shader_program, fragmentShader);
	//glUseProgram(0);
}

void print_matrix(const Matrix *matrix)
{
	for(int i = 0; i < 16; i++)
	{
		if(i > 0 && i % 4 == 0)
		{
			printf("\n");
		}

		printf("%f ", matrix[i]);
	}

	printf("\n\n");
}

void multiply(Matrix *m1, Matrix *m2)
{
	Matrix temp[16];

	for(int i = 0, j = 0; i < 4; i++, j +=4)
	{
		for(int k = 0; k < 4; k++)
		{
			temp[j + k] = (m1[j] * m2[k]) + (m1[j + 1] * m2[k + 4]) + (m1[j + 2] * m2[k + 8]) + (m1[j + 3] * m2[k + 12]);
		}
	}

	memcpy(m1, temp, sizeof(Matrix) * 16);
}

void multiply_slow(Matrix *m1, Matrix *m2)
{
	GLfloat temp[16];

	for(int x = 0; x < 4; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			temp[y + (x * 4)] = (m1[x * 4] * m2[y]) +
				(m1[(x * 4) + 1] * m2[y + 4]) +
				(m1[(x * 4) + 2] * m2[y + 8]) +
				(m1[(x * 4) + 3] * m2[y + 12]);
		}
	}

	memcpy(m1, temp, sizeof(GLfloat) * 16);
}

void translate(Matrix *matrix, GLfloat x, GLfloat y, GLfloat z)
{
	matrix[0] += x * matrix[3];
	matrix[4] += x * matrix[7];
	matrix[8] += x * matrix[11];
	matrix[12] += x * matrix[15];

	matrix[1] += y * matrix[3];
	matrix[5] += y * matrix[7];
	matrix[9] += y * matrix[11];
	matrix[13] += y * matrix[15];

	matrix[2] += z * matrix[3];
	matrix[6] += z * matrix[7];
	matrix[10] += z * matrix[11];
	matrix[14] += z * matrix[15];
}

void rotate(Matrix *matrix, GLfloat angle, uint8_t axis)
{
	GLfloat new[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	GLfloat sine = sinf(angle * PI / 180);
	GLfloat cosine = cosf(angle * PI / 180);

	if(axis == 0)
	{
		new[5] = cosine;
		new[6] = sine;
		new[9] = -sine;
		new[10] = cosine;
	}
	else if(axis == 1)
	{
		new[0] = cosine;
		new[2] = -sine;
		new[8] = sine;
		new[10] = cosine;
	}
	else if(axis == 2)
	{
		new[0] = cosine;
		new[1] = sine;
		new[4] = -sine;
		new[5] = cosine;
	}

	multiply(matrix, new);
}

void scale(GLfloat *matrix, GLfloat factor)
{
	for(uint8_t i = 0; i < 16; i += 4)
	{
		matrix[i] *= factor;
		matrix[i + 1] *= factor;
		matrix[i + 2] *= factor;
	}
}

// NOTE: SCREEN_WIDTH and SCREEN_HEIGHT?
void perspective(Matrix *matrix, uint16_t width, uint16_t height, uint8_t fov_x, float near_z, float far_z)
{
	float aspect_ratio = (float)height / width;
	float frustum_length = far_z - near_z;

	GLfloat fov = 1 / (tanf(fov_x * PI / 360.0f) * aspect_ratio);

	memset(matrix, 0, sizeof(GLfloat) * 16);
	matrix[0] = aspect_ratio * fov;
	matrix[5] = fov;
	matrix[10] = -(far_z + near_z) / frustum_length;
	matrix[11] = -1;
	matrix[14] = -(2 * far_z * near_z) / frustum_length;
}

void look_at(Matrix *matrix, Vector position, Vector target)
{
	Vector dir = {target.x - position.x, target.y - position.y, target.z - position.z};
	Vector f = normalize(dir);

	Vector u = {0.0f, 1.0f, 0.0f};
	Vector s = normalize(cross(f, u));

	u = cross(s, f);

	matrix[0] = s.x;
	matrix[1] = u.x;
	matrix[2] = -f.x;
	matrix[3] = 0.0f;

	matrix[4] = s.y;
	matrix[5] = u.y;
	matrix[6] = -f.y;
	matrix[7] = 0.0f;

	matrix[8] = s.z;
	matrix[9] = u.z;
	matrix[10] = -f.z;
	matrix[11] = 0.0f;

	matrix[12] = -dot(position, s);
	matrix[13] = -dot(position, u);
	matrix[14] = dot(position, f);
	matrix[15] = 1.0f;
}

void ortho(Matrix *matrix, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near_z, GLfloat far_z)
{
	memset(matrix, 0, sizeof(GLfloat) * 16);

	matrix[0] = 2 / (right - left);
	matrix[5] = 2 / (top - bottom);
	matrix[10] = -2 / (far_z - near_z);
	matrix[12] = -(right + left) / (right - left);
	matrix[13] = -(top + bottom) / (top - bottom);
	matrix[14] = -(far_z + near_z) / (far_z - near_z);
	matrix[15] = 1.0f;
}

GLfloat dot(Vector v1, Vector v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector cross(Vector v1, Vector v2)
{
	Vector result = { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };

	return result;
}

GLfloat length(Vector vector)
{
	return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Vector normalize(Vector vector)
{
	GLfloat len = length(vector);

	if(len > 0)
	{
		vector.x /= len;
		vector.y /= len;
		vector.z /= len;
	}

	return vector;
}
