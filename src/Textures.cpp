#include <Textures.h>
#include <stdexcept>
#include <cassert>
#include <SOIL/SOIL.h>
#include <GL/gl.h>

Textures::Textures(std::initializer_list<std::string> texture_filenames)
    : textureNullObject(0, -1)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    textures.reserve(texture_filenames.size());
    std::vector<GLuint> texture_ids(texture_filenames.size());
    glGenTextures(static_cast<GLsizei>(texture_filenames.size()), texture_ids.data());
    size_t index = 0;
    for(auto filename : texture_filenames)
    {
        loadTexture(filename, texture_ids[index]);
        ++index;
    }
}

const Texture &Textures::operator[](int index) const
{
    if(index < 0 || index >= numberOfTextures())
        return textureNullObject;
    return textures[static_cast<size_t>(index)];
}

int Textures::numberOfTextures() const
{
    return static_cast<int>(textures.size());
}

void Textures::loadTexture(const std::string &filename, GLuint id)
{
    size_t index = textures.size();
    Image img(filename);
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    textures.emplace_back(id, static_cast<int>(index));
}

Textures::Image::Image(const std::string &filename)
    : data(nullptr)
{
    data = SOIL_load_image(filename.c_str(), &width, &height, nullptr, SOIL_LOAD_RGB);
    if(data == nullptr)
        throw std::runtime_error("Failed to load texture from file " + std::string(filename));
}

Textures::Image::~Image()
{
    if(data)
        SOIL_free_image_data(data);
}

Texture::Texture(GLuint id, int index)
    : id(id), index(index)
{ }

void Texture::bind(const GLint program_id, const std::string &name) const
{
    if(index == -1) // null object - no texture
        return;
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, id);
    GLint location = glGetUniformLocation(program_id, name.c_str());
    if(location < 0)
    {
        std::string error(reinterpret_cast<const char*>(gluErrorString(glGetError())));
        throw std::runtime_error("could not bind texture " + std::to_string(index) +
            " in program " + std::to_string(program_id) + ": " + error);
    }
    glUniform1i(location, index);
}
