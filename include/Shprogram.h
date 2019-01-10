#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

class ShaderProgram
{
    GLint program_id; 	// The program ID
public:
    // Constructor reads and builds the shader
    ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);

    // Use the program
    void Use() const
    {
        glUseProgram(get_programID());
    }

    // returns program ID
    GLint get_programID() const
    {
        return program_id;
    }
};
