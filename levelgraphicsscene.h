#ifndef LEVELGRAPHICSSCENE_H
#define LEVELGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QVector>

#include "level.h"
#include "grid.h"
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
        m_grid = new Grid(5,5,32);
        //this->addItem(m_map);
        m_map->add_map_to_scene(this);
        this->addItem(m_grid);
        /*for(auto game_object: m_level->get_all_game_objects())
        {
            this->addItem(new GameObjectPixmapItem(game_object));
        }*/
        //this->show()
    }
    Level* get_level()
    {
        return m_level;
    }

    ~LevelGraphicsScene()
    {
        m_layers.clear();
        delete m_map;
        delete m_grid;
        delete m_level;
    }

private:
    //QVector<QGraphicsPixmapItem>
    QVector<QVector<GameObjectPixmapItem*>> m_layers;
    Map* m_map;
    Grid* m_grid;
    Level* m_level;

};

#endif // LEVELGRAPHICSSCENE_H
