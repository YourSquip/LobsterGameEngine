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
        Level* empty_level = new Level();
        empty_level->add_game_object(new GameObject());
        add_level(empty_level);
        curr_level = empty_level;
    }
    Game(QString title):Game()
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

    Level* get_curr_level()
    {
        return curr_level;
    }

    QMap<QString, Level*> get_all_levels()
    {
        return m_levels;
    }
    ~Game()
    {
        m_levels.clear();
        delete curr_level;
    }

private:
    QString m_title;
    QMap<QString, Level*> m_levels;
    Level* curr_level;
};

#endif // GAME_H
