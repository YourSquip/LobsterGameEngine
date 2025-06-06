#ifndef EDITOR_H
#define EDITOR_H

#include <QDebug>
#include <QString>
#include <QMap>

#include "game.h"

class Editor
{
public:

    Game* get_game()
    {
        return m_game;
    }
    GameObject* get_selected_game_obj()
    {
        return m_selected_game_obj;
    }

    void set_selected_game_obj(GameObject* game_object)
    {
        m_selected_game_obj = game_object;
    }

    ~Editor()
    {
        delete m_game;
        delete m_selected_game_obj;
    }

    static Editor* get_instance()
    {
        if(instance) return  instance;
        instance = new Editor();
        return instance;
    }
private:
    Editor()
    {
        m_game = new Game();

    }
    static Editor* instance;
    Game* m_game;
    GameObject* m_selected_game_obj;
};

#endif // EDITOR_H
