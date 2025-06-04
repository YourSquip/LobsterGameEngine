#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QDebug>
#include <QString>
#include <QHash>

#include "component.h"

class GameObject
{
public:

    GameObject()
    {
        m_id = next_id;
        next_id++;
        m_name = QString::fromStdString("game_object" + std::to_string(m_id));
    }
    GameObject( QString name)
    {
        m_id = next_id;
        next_id++;
        m_name = name;
    }

    ~GameObject()
    {
        m_components.clear();
    }

    QString get_name()
    {
        return m_name;
    }

    void set_name(QString name)
    {
        m_name = name;
    }

    void add_component(Component* component)
    {
        if(m_components.contains(component->get_name()))
        {
            qDebug()<<"GameObject " << m_name << " already has " << component->get_name() << " component";
            return;
        }
        m_components.insert(component->get_name(), component);
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
private:
    unsigned int m_id;
    QString m_name;
    static unsigned int next_id;
    QHash <QString, Component*> m_components;
};

#endif // GAMEOBJECT_H
