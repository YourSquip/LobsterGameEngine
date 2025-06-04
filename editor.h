#ifndef EDITOR_H
#define EDITOR_H

#include <QDebug>
#include <QString>
#include <QMap>

#include "game.h"

class Editor
{
public:
    Editor()
    {
        m_game = new Game();
    }
    Game* get_game()
    {
        return m_game;
    }

    ~Editor()
    {
        delete m_game;
    }
private:
    Game* m_game;
};

#endif // EDITOR_H
