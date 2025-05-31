#ifndef EDITOR_H
#define EDITOR_H

#include "editortool.h"

class Editor
{
public:
    static Editor get_instance()
    {
        static Editor instance;
        return instance;
    }

    static EditorTool* get_editor_tool()
    {
        return m_editor_tool;
    }

private:
    Editor();
    static EditorTool* m_editor_tool;
    Editor(Editor const&) = delete;
    Editor& operator= (Editor const&) = delete;
};


#endif // EDITOR_H
