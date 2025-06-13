#ifndef LEVEL_H
#define LEVEL_H

#include <QDebug>
#include <QString>
#include <QVector>
#include <QMap>

#include "gameobject.h"

class Level
{
public:

    Level()
    {
        m_id = next_id;
        next_id++;
        m_name = QString::fromStdString("level" + std::to_string(m_id));
        GameObject* game_object = new GameObject();
        add_game_object(game_object);
    }

    Level(QString name)
    {
        m_id = next_id;
        next_id++;
        m_name = name;
        GameObject* game_object = new GameObject();
        add_game_object(game_object);
    }

    QString get_name()
    {
        return m_name;
    }

    void set_name(QString name)
    {
       m_name = name;
    }

    void add_game_object(GameObject* game_object)
    {
        m_game_objects.push_back(game_object);
        /*if(!m_game_objects.empty())
        {

        }*/


    }

    void remove_game_object(GameObject* game_object)
    {
        /*if(!m_game_objects.contains(game_object->get_name()))
        {
            qDebug()<<"No object with name " << game_object->get_name();
            return;
        }
        m_game_objects.remove(game_object->get_name());*/
    }

    QVector<GameObject*> get_all_game_objects()
    {
        return m_game_objects;
    }
    ~Level()
    {
        m_game_objects.clear();
    }
private:
    unsigned int m_id;
    QString m_name;
    static unsigned int next_id;
    //QMap<QString, GameObject*> m_game_objects;
    QVector<GameObject*> m_game_objects;
};

#endif // LEVEL_H
