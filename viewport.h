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
public:
    Viewport(QWidget* parent = nullptr):QGraphicsView(parent)
    {
        m_curr_scene = new LevelGraphicsScene();
        //m_show_grid_check = new QCheckBox("show grid",this);
        this->setScene(m_curr_scene);
        //QMediaPlayer* player = new QMediaPlayer();
        //QAudioOutput* audioOutput = new QAudioOutput();

        //player->setAudioOutput(audioOutput);
        // ...
        //player->setSource(QUrl::fromLocalFile("D:/QtProjects/LobsterGameEngine2.0/LobsterGameEngine/audio/title_music.mp3"));
        //audioOutput->setVolume(50);
        //player->play();
        //m_tabs = new QTabWidget(parent);
        /*QMap<QString, Level*> levels = Editor::get_instance()->get_game()->get_all_levels();
        QMapIterator<QString, Level*> i(levels);
        while (i.hasNext())
        {
            i.next();
            qDebug()<<(i.key()) << ": " << i.value();
            m_all_scenes.push_back(new LevelGraphicsScene(i.value()));
        }

        if(!m_all_scenes.empty())
        {
            m_curr_scene = m_all_scenes[0];
        }
        else
        {
            m_curr_scene = new LevelGraphicsScene();
        }*/
        //m_tabs->addTab(parent,"ass");
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
        //m_curr_scene->get_level()->add_game_object(game_object);
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
        //m_curr_scene->update();
        //this->setScene(m_curr_scene);
        //this->show();
    }
    void object_changed_pixmap()
    {
        m_curr_scene->update_scene();
    }
private:
    LevelGraphicsScene* m_curr_scene;
    QVector<LevelGraphicsScene*> m_all_scenes;
    QCheckBox* m_show_grid_check;
    QGraphicsScene* m_tiles_list;

};

#endif // VIEWPORT_H
