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
    }

    Level(QString name)
    {
        m_id = next_id;
        next_id++;
        m_name = name;
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
        if(m_game_objects.contains(game_object->get_name()))
        {
            qDebug()<<"Level " << m_name << " already has object with name " << game_object->get_name();
            return;
        }
        m_game_objects.insert(game_object->get_name(), game_object);
    }

    void remove_game_object(GameObject* game_object)
    {
        if(!m_game_objects.contains(game_object->get_name()))
        {
            qDebug()<<"No object with name " << game_object->get_name();
            return;
        }
        m_game_objects.remove(game_object->get_name());
    }


private:
    unsigned int m_id;
    QString m_name;
    static unsigned int next_id;
    QMap<QString, GameObject*> m_game_objects;
};

#endif // LEVEL_H
