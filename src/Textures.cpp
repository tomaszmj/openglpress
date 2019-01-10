#include <Textures.h>
#include <stdexcept>
#include <cassert>
#include <SOIL/SOIL.h>
#include <GL/gl.h>

Textures::Textures(std::initializer_list<TextureInitializer> textures)
    : textureIds(textures.size())
{
    textureNames.reserve(textures.size());
    glGenTextures(textures.size(), textureIds.data());
    for(auto texture : textures)
        loadTexture(texture);
}

int Textures::numberOfTextures() const
{
    return static_cast<int>(textureIds.size());
}

void Textures::bindByIndex(GLint programId, int index) const
{
    assert(index < numberOfTextures());
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, textureIds[index]);
    glUniform1i(glGetUniformLocation(programId, textureNames[index].c_str()), index);
}

void Textures::bindAll(GLint programId) const
{
    for(int i = 0; i < numberOfTextures(); ++i)
        bindByIndex(programId, i); 
}

void Textures::loadTexture(const TextureInitializer initializer)
{
    int id = textureNames.size();
    textureNames.emplace_back(initializer.name);
    Image img(initializer.filename);
    glActiveTexture(GL_TEXTURE0 + id);
    glBindTexture(GL_TEXTURE_2D, textureIds[id]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);
}

Textures::Image::Image(const char *filename)
    : data(nullptr)
{
    data = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
    if(data == nullptr)
        throw std::runtime_error("Failed to load texture from file " + std::string(filename));
}

Textures::Image::~Image()
{
    if(data)
        SOIL_free_image_data(data);
}
