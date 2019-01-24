#include <AnimationParameters.h>
#include <cmath>
#include <cassert>
#include <glm/gtc/matrix_access.hpp>

AnimationParameters::AnimationParameters(const std::array<double, 4> times, const std::array<double, 3> heights)
    : h(heights)
{
    t[0] = times[0];
    t[2] = times[1];
    t[3] = times[2];
    t[5] = times[3];
    maxVelocityBeforeCrushing = 2 * (h[0] - h[2]) / (t[2] - t[0]);
    maxVelocityAfterCrushing = 2 * (h[0] - h[2]) / (t[5] - t[3]);
    t[1] = 2 * (h[0] - h[1]) / maxVelocityBeforeCrushing + t[0];
    t[4] = 2 * (h[1] - h[2]) / maxVelocityAfterCrushing + t[3];
}

double AnimationParameters::calculateY(double time) const
{
    while(time > t[5])
        time -= t[5];
    if(time < t[0])
        return h[0];
    if(time < t[1])
    {
        double v = maxVelocityBeforeCrushing * (time - t[0]) / (t[1] - t[0]);
        return h[0] - 0.5 * v * (time - t[0]);
    }
    if(time < t[2])
    {
        double v = maxVelocityBeforeCrushing * (t[2] - time) / (t[2] - t[1]);
        return h[1] - 0.5 * (maxVelocityBeforeCrushing + v) * (time - t[1]);
    }
    if(time < t[3])
        return h[2];
    if(time < t[4])
    {
        double v = maxVelocityAfterCrushing * (time - t[3]) / (t[4] - t[3]);
        return h[2] + 0.5 * v * (time - t[3]);
    }
    // else - if time <= t[5]
    double v = maxVelocityAfterCrushing * (t[5] - time) / (t[5] - t[4]);
    return h[1] + 0.5 * (v + maxVelocityAfterCrushing) * (time - t[4]);
}

std::array<double, 3> AnimationParameters::solveLinearEquationsSystem(const glm::dmat3 &m, const glm::dvec3 &v)
{
    std::array<double, 3> retval;
    double main_determinant = glm::determinant(m);
    assert(main_determinant != 0.0);
    retval[0] = glm::determinant(glm::dmat3(v, glm::column(m, 1), glm::column(m, 2))) / main_determinant;
    retval[1] = glm::determinant(glm::dmat3(glm::column(m, 0), v, glm::column(m, 2))) / main_determinant;
    retval[2] = glm::determinant(glm::dmat3(glm::column(m, 0), glm::column(m, 1), v)) / main_determinant;
    return retval;
}
