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
        m_level = new Level();
        m_map = new Map(7,7);
        m_grid = new Grid(7,7,32);
        m_grid_on = false;
        m_map->add_map_to_scene(this);

        QVector<GameObjectPixmapItem*> row;
        for(auto game_object: m_level->get_all_game_objects())
        {
            GameObjectPixmapItem* item = new GameObjectPixmapItem(game_object);
            item->update_pixmap();
            this->addItem(item);
            row.push_back(item);

        }
        m_layers.push_back(row);

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
    /*void update() override
    {

    }*/
    ~LevelGraphicsScene()
    {
        m_layers.clear();
        delete m_map;
        delete m_grid;
        delete m_level;
    }

    bool do_item_intersects_with_item(GameObjectPixmapItem* item1, GameObjectPixmapItem* item2)
    {
        return item1->boundingRect().intersects(item2->boundingRect());
    }

    QVector<GameObjectPixmapItem*> get_all_intersected_objects(GameObjectPixmapItem* item1)
    {
        QVector<GameObjectPixmapItem*> intersected_items;
        for(auto item: this->items())
        {
            GameObjectPixmapItem* game_item = dynamic_cast<GameObjectPixmapItem*>(item);
            if(do_item_intersects_with_item(item1,game_item))
            {
                intersected_items.push_back(game_item);
            }
        }
        return intersected_items;
    }

    QVector<GameObjectPixmapItem*> get_all_intersected_interactable_objects(GameObjectPixmapItem* item1)
    {
        QVector<GameObjectPixmapItem*> intersected_items;
        for(auto item: this->items())
        {
            GameObjectPixmapItem* game_item = dynamic_cast<GameObjectPixmapItem*>(item);
            if(game_item)
            {
                qDebug()<<"game_item: "<<game_item->get_game_object()->get_name();
                qDebug()<<"item1: "<<item1->get_game_object()->get_name();
                if(do_item_intersects_with_item(item1,game_item) && game_item->get_game_object()->get_states()->m_interactable)
                {
                    intersected_items.push_back(game_item);
                }
            }
        }
        return intersected_items;
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        GameObjectPixmapItem* curr_item =  get_current_item();
        curr_item->keyPressEvent(event);
        curr_item->update_pixmap();
        if(Editor::get_instance()->game_running_state())
        {
            qDebug()<<"keyPressEvent:game running";
            if(curr_item->get_game_object()->get_states()->m_controlable)
            {
                qDebug()<<"keyPressEvent:game object is controlable";
                qreal x = curr_item->pos().x();
                qreal y = curr_item->pos().y();
                float velocity = 20;
                float new_x = x;
                float new_y = y;
                if(event->key() == Qt::Key_W)
                {
                    new_x = x;
                    new_y = y - velocity;
                    curr_item->setPos(new_x, new_y);
                    qDebug()<<"GameObjectPixmapItem: y_position_has_changed";

                }
                if(event->key() == Qt::Key_A)
                {
                    new_x = x - velocity;
                    new_y = y;
                    curr_item->setPos(new_x, new_y);
                    qDebug()<<"GameObjectPixmapItem:x_position_has_changed";
                }
                if(event->key() == Qt::Key_S)
                {
                    new_x = x;
                    new_y = y + velocity;
                    curr_item->setPos(new_x, new_y);
                    qDebug()<<"GameObjectPixmapItem:y_position_has_changed";
                }
                if(event->key() == Qt::Key_D)
                {
                    new_x = x + velocity;
                    new_y = y;
                    curr_item->setPos(new_x, new_y);
                    qDebug()<<"GameObjectPixmapItem:x_position_has_changed";
                }

                //QGraphicsScene::keyPressEvent(event);

                if(curr_item->get_game_object()->get_states()->m_can_interact)
                {

                    if(event->key() == Qt::Key_Space)
                    {
                        curr_item->update_pixmap();
                        //auto colliding_items = curr_item->collidesWithItem();
                        QVector<GameObjectPixmapItem*> items = get_all_intersected_interactable_objects(curr_item);
                        for(auto item: items)
                        {
                            if(curr_item->collidesWithItem(item))
                            {
                                Audio* audio = dynamic_cast<Audio*>(item->get_game_object()->get_component("audio"));
                                if(audio->get_play_on_interact())
                                {
                                    audio->play_audio();
                                }
                            }

                        }

                    }
                }
            }


        }
    }

    GameObjectPixmapItem* get_current_item()
    {
        for(auto item: this->items())
        {
            GameObjectPixmapItem* game_item = dynamic_cast<GameObjectPixmapItem*>(item);
            if(game_item->get_current_in_scene())
            {
                return game_item;
            }
        }
    }

    void copy_to_current(LevelGraphicsScene* scene)
    {
        this->clear();
        for(auto item: scene->items())
        {
            GameObjectPixmapItem* game_item = dynamic_cast<GameObjectPixmapItem*>(item);
            this->addItem(game_item);
        }

    }

    QVector<GameObjectPixmapItem*> get_all_controlable();

private:
    QVector<QVector<GameObjectPixmapItem*>> m_layers;
    Map* m_map;
    Grid* m_grid;
    Level* m_level;
    bool m_grid_on;

};



#endif // LEVELGRAPHICSSCENE_H
