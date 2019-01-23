#include <AnimationParameters.h>
#include <cmath>
#include <cassert>
#include <glm/gtc/matrix_access.hpp>

AnimationParameters::AnimationParameters(const std::array<double, 6> times, const std::array<double, 3> heights)
    : t(times), h(heights)
{
    maxVelocityBeforeCrushing = 2 * (h[0] - h[1]) / (t[1] - t[0]);
    maxVelocityAfterCrushing = 2 * (h[0] - h[1]) / (t[5] - t[4]);
    glm::dmat3 m(
        glm::dvec3(t[1]*t[1], t[2]*t[2], (std::pow(t[2], 3) - std::pow(t[1], 3))/3.0),
        glm::dvec3(t[1], t[2], (t[2]*t[2] - t[1]*t[1])/2.0),
        glm::dvec3(1.0, 1.0, t[2] - t[1])
    );
    assert(glm::all(glm::equal(glm::column(m, 0), glm::dvec3(t[1]*t[1], t[2]*t[2], (std::pow(t[2], 3) - std::pow(t[1], 3))/3.0))));
    glm::dvec3 v(maxVelocityBeforeCrushing, 0.0, h[1] - h[2]);
    quadraticVelocityCoefficientsBeforeCrushing = solveLinearEquationsSystem(m, v);
    //quadraticVelocityCoefficientsAfterCrushing - todo
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
