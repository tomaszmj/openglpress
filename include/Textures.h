#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>

struct TextureInitializer
{
    const char *filename;
    const char *name;

    TextureInitializer(const char *filename_, const char *name_)
        : filename(filename_), name(name_)
    {}
};


class Texture
{
public:
    Texture(const std::string &filename, const std::string &texture_name);
    void bind(GLint programId) const;

private:
    struct Image
    {
        unsigned char *data;
        int width;
        int height;

        Image(const char *filename);
        ~Image();
    };

    GLuint id;
    const std::string name;
};

class Textures
{
public:
    Textures(std::initializer_list<TextureInitializer> textures);
    int numberOfTextures() const;
    void bindByIndex(GLint programId, int index) const;
    void bindAll(GLint programId) const;

private:
    struct Image
    {
        unsigned char *data;
        int width;
        int height;

        Image(const char *filename);
        ~Image();
    };

    std::vector<GLuint> textureIds;
    std::vector<std::string> textureNames;

    void loadTexture(const TextureInitializer initializer);
};
