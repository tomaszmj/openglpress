#include <Scene.h>
#include <ShaderProgram.h>
#include <Window.h>
#include <Textures.h>
#include <VAOWrapper.h>

Scene::Scene()
    : renderedObjects(0), lightPosition(14.0f, 29.0f, 14.0f), lightColor(1.0, 1.0, 1.0)
{ }

void Scene::render(const Window &window) const
{
    for(const auto &object : renderedObjects)
    {
        object->prepareRender();
        const ShaderProgram &program = object->getShaderProgram();
        program.setMat4Uniform("transform", window.getTransfromMatrix() * object->modelMatrix);
        program.setVec3Uniform("lightColor", lightColor);
        program.setVec3Uniform("lightPosition", lightPosition);
        object->render();
        object->endRender();
    }
}

void Scene::addObject(std::unique_ptr<RenderedObject> object)
{
    renderedObjects.emplace_back(std::move(object));
}

void Scene::makeAndAddObject(const ShaderProgram &shader, const VAOWrapper &vao, const glm::mat4 &model, const Texture &texture)
{
    renderedObjects.emplace_back(new RenderedObject(shader, vao, model, texture));
}

void Scene::setUpLightSource(const glm::vec3 &position, const glm::vec3 &color)
{
    lightPosition = position;
    lightColor = color;
}
