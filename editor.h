#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

#include "game.h"
//#include "editortool.h"

enum EditorToolType
{
    Coursor = 0,
    PaintBrush = 1,
    Eraser = 2,
    MoveObjectXY = 3
};
enum UseArea
{
    MapTilesArea = 1,
    GameObjectsArea = 2
};

class Editor
{
public:
    static Editor* get_instance()
    {
        if(!instance)
        {
            instance = new Editor();
        }
        return instance;
    }

    EditorToolType get_editor_tool_type()
    {
        return m_editor_tool_type;
    }
    void change_editor_tool_type(EditorToolType tool_type)
    {
        m_editor_tool_type = tool_type;
    }
    Game* get_game()
    {
        return m_game;
    }
private:
    Editor(){
        m_editor_tool_type = Eraser;
        m_use_area = MapTilesArea;

        m_game = new Game();
    }
    static Editor* instance;
    EditorToolType m_editor_tool_type;
    UseArea m_use_area;
    Game* m_game;
    //Editor& operator= (Editor const&) = delete;

};


#endif // EDITOR_H
