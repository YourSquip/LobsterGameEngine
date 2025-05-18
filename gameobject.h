#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>

class GameObject
{

public:
    GameObject()
    {
        m_id = next_id;
        next_id++;
        m_name = QString::fromStdString("untitled" + std::to_string(m_id));
    }
private:
    unsigned int m_id;
    QString m_name;
    static unsigned int next_id;
};

#endif // GAMEOBJECT_H
