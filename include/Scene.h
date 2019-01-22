#pragma once
#include <RenderedObject.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class Window;
class VAOWrapper;
class ShaderProgram;
class Texture;

class Scene
{
public:
    Scene();
    void render(const Window &window) const;
//    void update(time)
    void addObject(std::unique_ptr<RenderedObject> object);
    void makeAndAddObject(const ShaderProgram &shader, const VAOWrapper &vao, const glm::mat4 &model, const Texture &texture);
    void setUpLightSource(const glm::vec3 &position, const glm::vec3 &color);

private:
    std::vector<std::unique_ptr<RenderedObject>> renderedObjects;
    glm::vec3 lightPosition;
    glm::vec3 lightColor;
};
