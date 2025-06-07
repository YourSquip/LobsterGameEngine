#ifndef LEVELGRAPHICSSCENE_H
#define LEVELGRAPHICSSCENE_H

#include <QGraphicsScene>

#include "level.h"

class LevelGraphicsScene:public QGraphicsScene
{
public:
    LevelGraphicsScene(Level* level):QGraphicsScene()
    {
        m_level = level;
    }

private:
    Level* m_level;
};

#endif // LEVELGRAPHICSSCENE_H
