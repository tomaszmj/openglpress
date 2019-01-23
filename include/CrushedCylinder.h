#pragma once
#include <RenderedObject.h>

class CrushedCylinder: public RenderedObject
{
public:
    CrushedCylinder();
    virtual ~CrushedCylinder() override;
    virtual void prepareRender() const override;
    virtual void render() const override;
    virtual void endRender() const override;
    virtual void startAnimation() override;
    virtual void animationStep(double time_diff) override;
    virtual void stopAnimation() override;
};
