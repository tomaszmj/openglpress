#include <Scene.h>
#include <ShaderProgram.h>
#include <Window.h>
#include <Textures.h>
#include <ModelMatrix.h>
#include <VAOWrapper.h>

Scene::Scene()
    : renderedObjects(0), lightPosition(0.0), lightColor(0.0)
{ }

void Scene::update(const Window &window)
{
    double delta_t = window.getLastFrameTimeDifference();
    for(const auto &object : renderedObjects)
        object->animationStep(delta_t);
}

void Scene::render(const Window &window) const
{
    for(const auto &object : renderedObjects)
    {
        object->prepareRender();
        const ShaderProgram &program = object->getShaderProgram();
        program.setMat4Uniform("transform", window.getTransfromMatrix() * object->getModelMatrix().get());
        program.setVec3Uniform("lightColor", lightColor);
        program.setVec3Uniform("lightPosition", lightPosition);
        program.setVec3Uniform("cameraPosition", window.getCamera().getPosition());
        object->render();
        object->endRender();
    }
}

void Scene::addObject(std::unique_ptr<RenderedObject> object)
{
    renderedObjects.emplace_back(std::move(object));
}

void Scene::setUpLightSource(const glm::vec3 &position, const glm::vec3 &color)
{
    lightPosition = position;
    lightColor = color;
}
