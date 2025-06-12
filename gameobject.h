#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QDebug>
#include <QString>
#include <QHash>
#include <QMap>
#include <QObject>

#include "component.h"


class GameObject:public QObject
{
    Q_OBJECT
public:

    GameObject(GameObject* parent = nullptr)
    {
        m_id = next_id;
        next_id++;
        m_name = QString::fromStdString("game_object" + std::to_string(m_id));
        m_parent = parent;
        //add_component(new Position());

        //add_component(new Sprite());

        m_components["position"] = new Position();
        m_components["sprite"] = new Sprite();
    }
    GameObject( QString name,GameObject* parent = nullptr)
    {
        m_id = next_id;
        next_id++;
        m_name = name;
        m_parent = parent;
        //add_component(new Position());

        //add_component(new Sprite());
        m_components["position"] = new Position();
        m_components["sprite"] = new Sprite();
    }

    void debug_info()
    {
        qDebug()<<this->m_name;
        QMapIterator<QString, Component*> i(m_components);

        qDebug()<<"Components:";
        while (i.hasNext())
        {
            i.next();
            qDebug()<<(i.key()) << ": " << i.value();
        }
    }

    ~GameObject()
    {
        //m_components.clear();
        delete m_parent;
    }

    QString get_name()
    {
        return m_name;
    }

    void set_name(QString name)
    {
        m_name = name;
        emit name_changed(name);
    }

    void add_component(Component* component)
    {
        if(m_components.contains(component->get_name()))
        {
            qDebug()<<"GameObject " << m_name << " already has " << component->get_name() << " component";
            return;
        }
        //m_components.insert(component->get_name(), component);
        m_components[component->get_name()] = component;
    }


    void remove_component(Component* component)
    {
        if(!m_components.contains(component->get_name()))
        {
            qDebug()<<"No component with name " << component->get_name();
            return;
        }
        m_components.remove(component->get_name());
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



    QMap <QString, Component*> get_all_components()
    {
        if(!m_components.empty())
            return m_components;
        qDebug()<<"m_components are empty";
    }
signals:
    void name_changed(QString new_name);
private:
    unsigned int m_id;
    QString m_name;
    static unsigned int next_id;
    QMap <QString, Component*> m_components;
    GameObject* m_parent;
    QVector<GameObject*> m_children;
};

#endif // GAMEOBJECT_H
