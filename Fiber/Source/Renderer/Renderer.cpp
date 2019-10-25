#include "Renderer.h"
#include "..//Renderer/glad/glad.h"

#include <stdio.h>

static const char* vss =
"#version 450 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

static const char* fss =
"#version 450 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

static int s_program;
static unsigned int vao;

int compile_and_link_shaders(const char* _vss, const char* _fss)
{
	int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &_vss, 0);
	glCompileShader(vs);

	int success;
	char infoLog[512];

	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, 0, infoLog);
		fprintf(stderr, "Vertex Shader did not compile:\n%s\n", infoLog);
	}

	int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &_fss, 0);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, 0, infoLog);
		fprintf(stderr, "Fragment Shader did not compile:\n%s\n", infoLog);
	}

	int _shader_program = glCreateProgram();
	glAttachShader(_shader_program, vs);
	glAttachShader(_shader_program, fs);
	glLinkProgram(_shader_program);

	glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_shader_program, 512, 0, infoLog);
		fprintf(stderr, "Shader Program did not link:\n%s\n", infoLog);
	}
	glDeleteShader(vs);
	glDeleteShader(fs);

	return _shader_program;
}

void render_init()
{
	s_program = compile_and_link_shaders(vss, fss);

	float verticies[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	unsigned int vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glClearColor(0.2, 0.6, 0.4, 1.0);
}

void render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(s_program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);


}