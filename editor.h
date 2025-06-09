#ifndef EDITOR_H
#define EDITOR_H

#include <QDebug>
#include <QString>
#include <QMap>

#include "game.h"
//#include "maptile.h"


enum EditorToolType
{
    Coursor = 0,
    PaintBrush = 1,
    Eraser = 2,
    MoveXY = 3
};


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


    //MapTile* get_map_tile()
    //{/
    //    return m_paint_tile;
    //}

    ~Editor()
    {
        //delete m_game;
       // delete m_selected_game_obj;
    }

    static Editor* get_instance()
    {
        if(instance) return  instance;
        instance = new Editor();
        return instance;
    }
    EditorToolType get_editor_tool_type()
    {
        return m_chosen_tool;
    }
    void change_editor_tool_type(EditorToolType tool_type)
    {
        m_chosen_tool = tool_type;
    }

    /*QString get_paint_tile_name()
    {
        return m_paint_tile_name;
    }*/

    /*void set_paint_tile_name(QString paint_tile_name)
    {
        m_paint_tile_name = paint_tile_name;
    }*/

private:
    Editor()
    {
        m_game = new Game();
        m_chosen_tool = Coursor;
        //m_paint_tile = new MapTile();
        //m_paint_tile->set_graphics(new MapTileGraphics(QPixmap(":/sprites/grass32.png")));

    }
    static Editor* instance;
    Game* m_game;
    GameObject* m_selected_game_obj;

    EditorToolType m_chosen_tool;
    //MapTile* m_paint_tile;
};

#endif // EDITOR_H
