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

        QVector<GameObjectPixmapItem*> row;
        for(auto game_object: m_level->get_all_game_objects())
        {
            GameObjectPixmapItem* item = new GameObjectPixmapItem(game_object);
            item->update_pixmap();
            this->addItem(item);
            row.push_back(item);

        }
        m_layers.push_back(row);


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
        QVector<GameObjectPixmapItem*> row;
        for(auto game_object: m_level->get_all_game_objects())
        {
            GameObjectPixmapItem* item = new GameObjectPixmapItem(game_object);
            item->update_pixmap();
            row.push_back(item);
        }
        m_layers.push_back(row);
    }
    GameObjectPixmapItem* get_pixmap_item(int x, int y)
    {
        if(x< m_layers.size() && y < get_layer(0).size())
        {

            return m_layers[x][y];
        }
        return nullptr;
    }

    QVector<QVector<GameObjectPixmapItem*>> get_layers()
    {
        return m_layers;
    }

    QVector<GameObjectPixmapItem*> get_layer(int layer_ind)
    {
        return m_layers[layer_ind];
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

/*
class LevelUpdater: public QWidget
{
    Q_OBJECT
public:
    LevelGraphicsScene* m_scene;
    LevelUpdater(LevelGraphicsScene* scene)
    {
        m_scene = scene;
        m_scene->items();
        qDebug()<<"LevelUpdater:constructor";
        /*for(auto item: m_scene->items())
        {
            PixmapObjectUpdater* pixmap_updater = new PixmapObjectUpdater();
            GameObjectPixmapItem* pixmap_item = dynamic_cast<GameObjectPixmapItem*>(item);
            pixmap_item->add_updater();
            connect(pixmap_item->get_updater(),pixmap_item->get_updater()->x_position_has_changed, this, this->give_signal_of_changed_pos_x);
            connect(pixmap_item->get_updater(),pixmap_item->get_updater()->y_position_has_changed, this, this->give_signal_of_changed_pos_y);

        }*/
        /*if(!scene->get_layers().empty())
        {
            GameObject* new_obj = new GameObject();
            m_scene->get_layer(0).push_back(new GameObjectPixmapItem(new_obj));
            if(!scene->get_layer(0).empty())
            {
                for(int i = 0; i < scene->get_layer(0).size();i++)
                {

                    connect(scene->get_pixmap_item(0,i)->get_updater(),scene->get_pixmap_item(0,i)->get_updater()->x_position_has_changed, this, this->give_signal_of_changed_pos_x);
                    connect(scene->get_pixmap_item(0,i)->get_updater(),scene->get_pixmap_item(0,i)->get_updater()->y_position_has_changed, this, this->give_signal_of_changed_pos_y);

                }
            }
            else
            {
                qDebug()<<"LevelUpdater:scene->get_layer(0 is empty()";
            }

        }
        else
        {
            qDebug()<<"LevelUpdater:scene->get_layers() is empty()";
        }

    }
public slots:
    void give_signal_of_changed_pos_x(float x)
    {
        qDebug()<<"LevelUpdater:give_signal_of_changed_pos_x";
        emit changed_game_obj_x_pos(x);
    }
    void give_signal_of_changed_pos_y(float y)
    {
        qDebug()<<"LevelUpdater:give_signal_of_changed_pos_y";
        emit changed_game_obj_y_pos(y);
    }
signals:
    void changed_game_obj_x_pos(float x);
    void changed_game_obj_y_pos(float y);

};*/

#endif // LEVELGRAPHICSSCENE_H
