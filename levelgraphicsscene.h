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
        //m_level = level;
        m_level = new Level();
        m_map = new Map(10,10);
        m_grid = new Grid(10,10,32);
        m_grid_on = false;
        //this->addItem(m_map);
        m_map->add_map_to_scene(this);
        //this->addItem(m_grid);
        for(auto game_object: m_level->get_all_game_objects())
        {
            GameObjectPixmapItem* item = new GameObjectPixmapItem(game_object);
            item->update_pixmap();
            this->addItem(item);
        }

        //this->show()
    }
    Level* get_level()
    {
        return m_level;
    }
    bool is_grid_shown()
    {
        return m_grid_on;
    }
    void set_show_grid(bool is_shown)
    {
        m_grid_on = is_shown;
        if(is_shown)
        {
            this->addItem(m_grid);
        }
        else
        {
            this->removeItem(m_grid);
        }
    }
    void update_scene()
    {
        m_map->add_map_to_scene(this);
        if(m_grid_on)
        {
            this->addItem(m_grid);
        }
        for(auto game_object: m_level->get_all_game_objects())
        {
            GameObjectPixmapItem* item = new GameObjectPixmapItem(game_object);
            item->update_pixmap();
        }
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
    bool m_grid_on;

};

#endif // LEVELGRAPHICSSCENE_H
