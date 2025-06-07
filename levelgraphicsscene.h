#ifndef LEVELGRAPHICSSCENE_H
#define LEVELGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QVector>>

#include "level.h"
#include "map.h"
//#include "maptile"

class LevelGraphicsScene:public QGraphicsScene
{
public:
    LevelGraphicsScene(Level* level = nullptr):QGraphicsScene()
    {

        qDebug()<<"LevelGraphicsScene constructor";
        m_level = level;
        m_map = new Map(5,5);
        this->addItem(m_map);
    }

private:
    //QVector<QGraphicsPixmapItem>
    Map* m_map;
    Level* m_level;
};

#endif // LEVELGRAPHICSSCENE_H
