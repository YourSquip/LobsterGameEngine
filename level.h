#ifndef LEVEL_H
#define LEVEL_H

#include <QVector>

#include "gameobject.h"


class Level
{
public:
    Level();
    QVector<GameObject*> get_all_game_objects()
    {
        return  m_game_objects;
    }
private:
    unsigned int m_id;
    QVector<GameObject*> m_game_objects;
};

#endif // LEVEL_H
