#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>

class Texture
{
public:
    Texture(GLuint id=0, int index=-1); // default index -1: "null object" (bind will do nothing)
    void bind(const GLint program_id, const std::string &name) const;

private:
    GLuint id;
    int index;
};

class Textures
{
public:
    Textures(std::initializer_list<std::string> texture_filenames);
    const Texture &operator[](int index) const;
    int numberOfTextures() const;

private:
    struct Image
    {
        unsigned char *data;
        int width;
        int height;

        Image(const std::string &filename);
        ~Image();
    };

    std::vector<Texture> textures;
    Texture textureNullObject;

    void loadTexture(const std::string &filename, GLuint id);
};
