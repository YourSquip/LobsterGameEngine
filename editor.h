#ifndef EDITOR_H
#define EDITOR_H

#include <QDebug>
#include <QString>
#include <QMap>

#include "game.h"
#include "maptilegraphics.h"


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


    MapTileGraphics* get_tile_graphics()
    {
        return m_paint_tile;
    }
    void set_tile_graphics(MapTileGraphics* graphics)
    {
        m_paint_tile = graphics;
    }

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



private:
    Editor()
    {
        m_game = new Game();
        m_chosen_tool = Coursor;
        m_paint_tile = new MapTileGraphics(QPixmap(":/sprites/grass_tile.png"));
    }
    static Editor* instance;
    Game* m_game;
    GameObject* m_selected_game_obj;
    MapTileGraphics* m_paint_tile;
    EditorToolType m_chosen_tool;
};

#endif // EDITOR_H
