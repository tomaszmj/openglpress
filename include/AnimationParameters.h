#pragma once
#include <array>
#include <glm/glm.hpp>

// AnimationParamters constructor:
// 6 times (each in seconds, counted form animation start) are:
//   time when press starts moving down
//   time when press hits cylinder under the press
//   time when press stops after crushing cylinder
//   time when press starts moving up again, together with the crushed cylinder (which is regaining its shape)
//   time when the cylinder under the press regains its shape, while press continues moving up
//   time when press comes back to the original position
// requirement: times[i + 1] > times[i] for each i in {0, 1, 2, 3, 4}
// 3 heights (y positions in world coordinates):
//   initial position of press lower base
//   initial position of upper base of cylinder under the press
//   final position of press and crushed cylinder
// requirement: heights[0] > heights[1] > heights[2]
// The code calculating other parameters based on the input described above may not
// be readable, because the equations have been derived by hand on a piece of paper.
struct AnimationParameters
{
    AnimationParameters(const std::array<double, 6> times, const std::array<double, 3> heights);
    const std::array<double, 6> t;
    const std::array<double, 3> h;
    double maxVelocityBeforeCrushing;
    double maxVelocityAfterCrushing;
    std::array<double, 3> quadraticVelocityCoefficientsBeforeCrushing;
    std::array<double, 3> quadraticVelocityCoefficientsAfterCrushing;

    static std::array<double, 3> solveLinearEquationsSystem(const glm::dmat3 &m, const glm::dvec3 &v);
};
