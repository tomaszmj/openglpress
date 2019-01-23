#pragma once
#include <glm/glm.hpp>
#include <memory>

class ShaderProgram;
class VAOWrapper;
class ModelMatrix;
class Texture;

class RenderedObject
{
public:
    RenderedObject(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
                   ModelMatrix &model_matrix, const Texture &texture);
    virtual ~RenderedObject();
    virtual void prepareRender() const;
    virtual void render() const;
    virtual void endRender() const;
    virtual void startAnimation();
    virtual void animationStep(double time_diff);
    virtual void stopAnimation();
    const ShaderProgram &getShaderProgram() const;
    const VAOWrapper &getVaoWrapper() const;
    const ModelMatrix &getModelMatrix() const;
    const Texture &getTexture() const;

private:
    const ShaderProgram &shaderProgram;
    const VAOWrapper &vaoWrapper;
    ModelMatrix &modelMatrix;
    const Texture &texture;
};
