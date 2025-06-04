#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QString>
#include <QMap>

#include "level.h"

class Game
{
public:
    Game()
    {
        m_title = "Untitled Game";
    }
    Game(QString title)
    {
        m_title = title;
    }

    void add_level(Level* level)
    {
        if(m_levels.contains(level->get_name()))
        {
            qDebug()<<"Level with name "<< level->get_name() << " already exists in this game";
            return;
        }
        m_levels.insert(level->get_name(), level);
    }
    void remove_level(Level* level)
    {
        if(!m_levels.contains(level->get_name()))
        {
            qDebug()<<"No level with name"<< level->get_name();
            return;
        }
        m_levels.insert(level->get_name(), level);
    }
private:
    QString m_title;
    QMap<QString, Level*> m_levels;
};

#endif // GAME_H
