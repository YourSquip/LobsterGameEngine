#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>
#include "Components.h"

class GameObject
{

public:
    GameObject()
    {
        m_id = next_id;
        next_id++;
        m_name = QString::fromStdString("untitled" + std::to_string(m_id));
        Components::positions[m_id] = Position{0.0f,0.0f};
    }

private:
    unsigned int m_id;
    QString m_name;
    static unsigned int next_id;
};

#endif // GAMEOBJECT_H
