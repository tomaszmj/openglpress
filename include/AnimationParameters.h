#pragma once
#include <array>
#include <glm/glm.hpp>

// AnimationParamters constructor:
// 4 times (each in seconds, counted form animation start) are:
//   time when press starts moving down
//   time when press stops after crushing cylinder
//   time when press starts moving up again, together with the crushed cylinder (which is regaining its shape)
//   time when press comes back to the original position
// additionally, two more times will be computed:
//   time when press hits cylinder under the press
//   time when the cylinder under the press regains its shape, while press continues moving up
// constraint: times[i + 1] > times[i] for each i in {0, 1, 2, 3, 4}
// 3 heights (y positions in world coordinates):
//   initial position of press lower base
//   initial position of upper base of cylinder under the press
//   final position of press and crushed cylinder
// constraint: heights[0] > heights[1] > heights[2]
struct AnimationParameters
{
    AnimationParameters(const std::array<double, 4> times, const std::array<double, 3> heights);
    std::array<double, 6> t;
    std::array<double, 3> h;
    double maxVelocityBeforeCrushing;
    double maxVelocityAfterCrushing;

    double calculateY(double time) const;
};
