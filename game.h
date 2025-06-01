#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QVector>
#include "level.h"

class Game
{
public:
    Game()
    {
        m_levels.push_back(new Level());
        m_curr_level_id = m_levels[0]->get_id();
        m_curr_level = m_levels[0];
        if(m_curr_level)qDebug()<<"level was created in game";
        else qDebug()<<"level was NOT created in game";
    }
    bool is_game_running()
    {
        return m_is_running;
    }
    void add_level(Level* level)
    {
        m_levels.push_back(level);
    }
    Level* get_curr_level()
    {
        return m_curr_level;
    }
private:
    QString m_title;
    bool m_is_running;
    QVector<Level*> m_levels;
    unsigned int m_curr_level_id;
    Level* m_curr_level;
    //GameSettings* m_settings;
    //Controls* m_controls;
    //QStack<Level> m_levels;
    //other general game settings
};

#endif // GAME_H
