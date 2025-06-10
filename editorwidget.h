#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "gameobjectinfowidget.h"
#include "editor.h"
#include "gameobjectstreewidget.h"
#include "viewport.h"
#include "editortoolswidget.h"
#include "maptileslist.h"

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
    QVBoxLayout* m_map_editor_layout;
    GameObjectsTreeWidget* m_game_objects_tree;
    GameObjectInfoWidget* m_game_object_info;
    Viewport*  m_viewport;
    MapTilesList* m_tile_list;
    EditorToolsWidget* m_editor_tools;
    static EditorWidget* instance;
    EditorWidget(QWidget *parent=nullptr)
    {
        this->setMinimumSize(720, 512);
        m_layout = new QHBoxLayout(this);
        m_map_editor_layout = new QVBoxLayout(this);
        // m_editor = new Editor();
        m_game_objects_tree = new GameObjectsTreeWidget(this);
        m_viewport = new Viewport(this);
        m_game_object_info = new GameObjectInfoWidget(this);
        m_editor_tools = new EditorToolsWidget(m_viewport,this);
        m_tile_list = new MapTilesList(this);
        m_layout->addWidget(m_game_objects_tree);
        m_map_editor_layout->addWidget(m_editor_tools);
        m_map_editor_layout->addWidget(m_viewport);
        m_map_editor_layout->addWidget(m_tile_list);
        m_layout->addLayout( m_map_editor_layout);
        m_layout->addWidget(m_game_object_info);

        connect(m_game_objects_tree,m_game_objects_tree->item_selected, m_game_object_info,m_game_object_info->show_obj_info);
        connect(m_game_objects_tree,m_game_objects_tree->object_added, m_viewport,m_viewport->add_object_to_curr_scene);
        //SpriteComponentInfoWidget* sprite_info = dynamic_cast<SpriteComponentInfoWidget*>(m_game_object_info->get_component_info_widget(QString::fromStdString("sprite")));
        //connect(sprite_info->get_sprite(),sprite_info->get_sprite()->pixmap_was_changed,m_viewport,m_viewport->object_changed_pixmap);
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
    ~EditorWidget()
    {
        //delete m_editor;
        delete m_layout;
        delete m_game_objects_tree;
        delete m_game_object_info;
        delete  m_viewport;
    }
};

#endif // EDITORWIDGET_H
