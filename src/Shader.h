#pragma once

#include <glew.h>
#include "File.h"
#include "Array.h"

#include "String.h"
#include "math/Math.h"

class Shader
{
public:
	GLuint shaderProgram;
	Array<String> uniforms;
	Array<GLuint> uniformLocations;
	inline Shader(GLuint shaderProgram)
	{
		this->shaderProgram = shaderProgram;
	}

	inline void setUniform(String uniform)
	{
		this->uniforms.add(uniform);
		this->uniformLocations.add(glGetUniformLocation(this->shaderProgram, uniform.data));
	}
	
	inline GLuint getUniform(String uniform)
	{
		for (int i = 0; i < uniforms.depth; i++)
		{
			//MBW
			if (uniforms.get(i) == uniform) return uniformLocations.get(i);
		}
		return -1;

	}
	inline void uniform(String uniform, Vector3f v)
	{
		glUniform3f(getUniform(uniform), v.x, v.y, v.z);
	}
	inline void uniform(String uniform, float v)
	{
		glUniform1f(getUniform(uniform), v);
	}
	inline void uniform(String uniform, Matrix4f m)
	{
		glUniformMatrix4fv(getUniform(uniform), 1, false, m.elements);
	}

};

inline Shader createShader(const char* vertexPath, const char* fragmentPath)
{
	Shader shader(glCreateProgram());
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vData = read(vertexPath);
	const char* fData = read(fragmentPath);

	glShaderSource(vertexShader, 1, &vData, NULL);
	glShaderSource(fragmentShader, 1, &fData, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glAttachShader(shader.shaderProgram, vertexShader);
	glAttachShader(shader.shaderProgram, fragmentShader);

	glLinkProgram(shader.shaderProgram);


	int status = 0;
	char data[1024]{};
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderInfoLog(vertexShader, 1023, NULL, data);
		printf("Vertex Shader: %s\n", data);
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderInfoLog(fragmentShader, 1023, NULL, data);
		printf("Fragment Shader: %s\n", data);
	}

	glGetProgramiv(shader.shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramInfoLog(shader.shaderProgram, 1023, NULL, data);
		printf("Program Shader: %s\n", data);
	}


	return shader;
}

inline void bindShader(Shader& shader)
{
	glUseProgram(shader.shaderProgram);
}