#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <unordered_map>
#include <QPixmap>
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

struct Sprite
{
    QPixmap pixmap;
};

template <typename Type>
using ComponentMap = std::unordered_map<unsigned int, Type>;

using Positions = ComponentMap<Position>;
using Velocities = ComponentMap<Velocity>;
using Healths = ComponentMap<Health>;
using Sprites = ComponentMap<Sprite>;

struct Components
{
    Positions positions;
    Velocities velocities;
    Healths healths;
    Sprites sprites;
};

static Components COMPONENTS;

#endif // COMPONENTS_H

