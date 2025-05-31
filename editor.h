#ifndef EDITOR_H
#define EDITOR_H

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
    static Editor get_instance()
    {
        static Editor instance;
        return instance;
    }

    EditorToolType get_editor_tool_type()
    {
        return m_editor_tool_type;
    }


private:
    Editor(){
        m_editor_tool_type = PaintBrush;
        m_use_area = MapTilesArea;
    }
    EditorToolType m_editor_tool_type;
    UseArea m_use_area;
    Editor& operator= (Editor const&) = delete;
};


#endif // EDITOR_H
