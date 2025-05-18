#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <unordered_map>
struct Position
{
    float x;
    float y;
};

struct Velocity
{
    float x;
    float y;
};

struct Health
{
    int max;
    int current;
};

template <typename Type>
using ComponentMap = std::unordered_map<unsigned int, Type>;

using Positions = ComponentMap<Position>;
using Velocities = ComponentMap<Velocity>;
using Healths = ComponentMap<Health>;

struct Components
{
    Positions positions;
    Velocities velocities;
    Healths healths;
};

#endif // COMPONENTS_H

