#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QVector>
#include <QMap>

#include "levelgraphicsscene.h"
#include "editor.h"
#include "level.h"
#include <QAudioInput>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QLineEdit>
#include <QCheckBox>

class Viewport: public QGraphicsView
{
    Q_OBJECT
public:
    Viewport(QWidget* parent = nullptr):QGraphicsView(parent)
    {
        m_curr_scene = new LevelGraphicsScene();

        m_scene_before_play = new LevelGraphicsScene();
        this->setScene(m_curr_scene);

        this->show();

        qDebug()<<"Viewport constructor";
    }

    void change_curr_scene(QString level_name)
    {
        for(auto scene: m_all_scenes)
        {
            if(scene->get_level()->get_name() == level_name)
            {
                m_curr_scene = scene;
                m_scene_before_play->copy_to_current(scene);
            }
        }
        this->show();
    }

public slots:
    void add_object_to_curr_scene(GameObject* game_object)
    {
        if(!game_object)
        {
            qDebug()<<"GAMEOBJECT IS NULL";
        }
        m_curr_scene->addItem(new GameObjectPixmapItem(game_object));

        this->setScene(m_curr_scene);
        this->show();
        qDebug()<<"add object to current scene slot";
    }
    void show_grid()
    {
        if(m_curr_scene->is_grid_shown())
        {
            m_curr_scene->set_show_grid(false);
        }
        else
        {
            m_curr_scene->set_show_grid(true);
        }

    }
    void object_changed_pixmap()
    {
        m_curr_scene->update_scene();
    }
    void give_signal_of_changed_pos_x(float x)
    {
        emit changed_game_obj_x_pos(x);
        qDebug()<<"Viewport:changed_game_obj_x_pos";
    }
    void give_signal_of_changed_pos_y(float y)
    {
        emit changed_game_obj_y_pos(y);
        qDebug()<<"Viewport:changed_game_obj_y_pos";
    }



signals:
    void changed_game_obj_x_pos(float x);
    void changed_game_obj_y_pos(float y);
private:
    LevelGraphicsScene* m_curr_scene;
    LevelGraphicsScene* m_scene_before_play;
    QVector<LevelGraphicsScene*> m_all_scenes;
    QCheckBox* m_show_grid_check;
    QGraphicsScene* m_tiles_list;

};

#endif // VIEWPORT_H
