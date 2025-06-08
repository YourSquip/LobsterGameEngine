#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include "gameobjectinfowidget.h"
#include "editor.h"
#include "gameobjectstreewidget.h"
#include "viewport.h"

class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    Editor* get_editor()
    {
        return m_editor;
    }
    void set_parent(QWidget* parent)
    {
        this->setParent(parent);
    }
    GameObjectsTreeWidget* get_game_objects_tree()
    {
        return m_game_objects_tree;
    }
    GameObjectInfoWidget* get_game_object_info()
    {
        return m_game_object_info;
    }
    Viewport* get_viewport()
    {
        return m_viewport;
    }
signals:

private:
    Editor* m_editor;
    QHBoxLayout* m_layout;
    GameObjectsTreeWidget* m_game_objects_tree;
    GameObjectInfoWidget* m_game_object_info;
    Viewport*  m_viewport;
    static EditorWidget* instance;
    EditorWidget(QWidget *parent=nullptr)
    {
        this->setMinimumSize(720, 512);
        m_layout = new QHBoxLayout(this);
        // m_editor = new Editor();
        m_game_objects_tree = new GameObjectsTreeWidget(this);
        m_viewport = new Viewport(this);
        m_game_object_info = new GameObjectInfoWidget(this);
        m_layout->addWidget(m_game_objects_tree);
        m_layout->addWidget(m_viewport);
        m_layout->addWidget(m_game_object_info);
        connect(m_game_objects_tree,m_game_objects_tree->item_selected, m_game_object_info,m_game_object_info->show_obj_info);
        //connect(m_game_objects_tree, m_game_objects_tree->object_added, m_viewport,m_viewport->add_object_to_curr_scene);
        //connect(m_game_object_info, m_g, m_viewport,m_viewport->add_object_to_curr_scene);
    }
    //GameObject* m_selected_object;

public:
    static EditorWidget* get_instance()
    {
        if(instance)
        {
            return instance;
        }
        else
        {
            instance = new EditorWidget();
            return instance;
        }
    }
};

#endif // EDITORWIDGET_H
