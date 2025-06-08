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

class Viewport: public QGraphicsView
{
public:
    Viewport(QWidget* parent = nullptr):QGraphicsView(parent)
    {
        m_curr_scene = new LevelGraphicsScene();
        this->setScene(m_curr_scene);
        QMediaPlayer* player = new QMediaPlayer();
        QAudioOutput* audioOutput = new QAudioOutput();

        player->setAudioOutput(audioOutput);
        // ...
        player->setSource(QUrl::fromLocalFile("D:/QtProjects/LobsterGameEngine2.0/LobsterGameEngine/audio/title_music.mp3"));
        audioOutput->setVolume(50);
        player->play();
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
        m_curr_scene->addItem(new GameObjectPixmapItem(game_object));
        m_curr_scene->get_level()->add_game_object(game_object);
        this->setScene(m_curr_scene);
        this->show();
    }
private:
    LevelGraphicsScene* m_curr_scene;
    QVector<LevelGraphicsScene*> m_all_scenes;
};

#endif // VIEWPORT_H
