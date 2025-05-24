#ifndef LEVEL_H
#define LEVEL_H

#include <QVector>

#include "gameobject.h"


class Level
{
public:
    Level();

private:
    unsigned int m_id;
    QVector<GameObject*> m_game_objects;
};

#endif // LEVEL_H
