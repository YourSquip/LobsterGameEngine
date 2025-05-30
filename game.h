#ifndef GAME_H
#define GAME_H

#include <QString>


class Game
{
public:
    Game();
    bool is_game_running()
    {
        return m_is_running;
    }
private:
    QString m_title;
    bool m_is_running;

    //GameSettings* m_settings;
    //Controls* m_controls;
    //QStack<Level> m_levels;
    //other general game settings
};

#endif // GAME_H
