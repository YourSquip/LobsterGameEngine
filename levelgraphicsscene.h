#ifndef LEVELGRAPHICSSCENE_H
#define LEVELGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QVector>

#include "level.h"
#include "map.h"
#include "gameobjectpixmapitem.h"
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
        for(auto game_object: m_level->get_all_game_objects())
        {
            this->addItem(new GameObjectPixmapItem(game_object));
        }
    }
    Level* get_level()
    {
        return m_level;
    }

private:
    //QVector<QGraphicsPixmapItem>
    QVector<QVector<GameObjectPixmapItem*>> m_layers;
    Map* m_map;
    Level* m_level;
};

#endif // LEVELGRAPHICSSCENE_H
