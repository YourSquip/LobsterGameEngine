#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>
#include <QVector>
#include <iostream>

#include "Components.h"


class GameObject
{

public:
    GameObject(GameObject* parent = nullptr)
    {
        m_id = next_id;
        next_id++;
        m_name = QString::fromStdString("untitled" + std::to_string(m_id));
        COMPONENTS.positions[m_id] = Position{0.0f,0.0f};
        m_parent = parent;
    }

    ~GameObject()
    {
        delete m_parent;
    }

    void add_child(GameObject* game_object)
    {
        m_children.push_back(game_object);
    }

    void remove_child_by_id(unsigned int id)
    {
        for(int i=0; i < m_children.size(); i++)
        {
            if(m_children[i]->m_id == id)
            {
                m_children.remove(i);
            }
        }
    }

    QVector<GameObject*> get_all_children()
    {
        return m_children;
    }

    GameObject* get_parent()
    {
        return m_parent;
    }

    void set_parent(GameObject* parent)
    {
        m_parent = parent;
    }

    unsigned int get_id()
    {
        return m_id;
    }

    QString get_name()
    {
        return m_name;
    }

protected:

    unsigned int m_id;
    QString m_name;
    static unsigned int next_id;
    GameObject* m_parent;
    QVector<GameObject*> m_children;
};

class Player: public GameObject
{
    Player():GameObject()
    {
        m_name = QString::fromStdString("player" + std::to_string(m_id));
    }
};



#endif // GAMEOBJECT_H
