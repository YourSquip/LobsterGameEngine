#ifndef EDITORTOOL_H
#define EDITORTOOL_H

#include<QGraphicsItem>
#include "editor.h"
//#include "maptile.h"
#include "maptilefactory.h"

class EditorTool
{
private:

    enum EditorToolType
    {
        Coursor = 0,
        PaintBrush = 1,
        Eraser = 2,
        MoveObjectXY = 3
    };
    enum UseArea
    {
        MapTiles = 1,
        GameObjects = 2
    };

public:
    EditorTool()
    {
        change_tool(EditorToolType::PaintBrush );
    }

    void use_tool(QGraphicsItem* item)
    {
        if(m_use_area == MapTiles)
        {
            if(m_curr_tool == PaintBrush)
            {
                item = m_curr_paint_tile;
            }

            if(m_curr_tool == Eraser)
            {
                item->setVisible(false);
            }
        }

        /*if(m_use_area == MapTiles)
        {
            if(m_curr_tool == PaintBrush)
            {
                item = m_curr_paint_tile;
            }

            if(m_curr_tool == Eraser)
            {
                item->setVisible(false);
            }
        }*/
    }

    void change_tool(EditorToolType tool_type)
    {
        m_curr_tool = tool_type;
        if(tool_type == PaintBrush || tool_type == Eraser)
        {
            m_use_area = MapTiles;
            if(tool_type == PaintBrush)
            {
                m_curr_paint_tile = MapTileFactory::get_instance().create_spec_tile("grass";
            }
        }
        else
        {
             m_use_area = GameObjects;
        }
    }

private:
    EditorToolType m_curr_tool;
    UseArea m_use_area;
    QGraphicsItem* m_curr_paint_tile;
};

#endif // EDITORTOOL_H
