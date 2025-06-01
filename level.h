#ifndef LEVEL_H
#define LEVEL_H

#include <QVector>

#include "gameobject.h"


class Level
{
public:
    Level()
    {
        m_id = next_id;
        next_id++;
        m_name = QString::fromStdString("level" + std::to_string(m_id));
        add_game_object(new GameObject(QString("basic_object")));
        if(!m_game_objects.empty()) qDebug()<<"game_objects in level are not empty";
        else qDebug()<<"game_objects in level are EMPTY";
    }
    void add_game_object(GameObject* game_object)
    {
        m_game_objects.push_back(game_object);
    }
    QVector<GameObject*> get_all_game_objects()
    {
        return  m_game_objects;
    }
    unsigned int get_id()
    {
        return m_id;
    }

    QString get_name()
    {
        return m_name;
    }
private:
    unsigned int m_id;
    QString m_name;
    static unsigned int next_id;
    QVector<GameObject*> m_game_objects;
};

#endif // LEVEL_H
