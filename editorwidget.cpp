#include "editorwidget.h"

EditorWidget::EditorWidget(QWidget *parent)
    : QWidget{parent}
{
    m_layout = new QHBoxLayout(this);
    m_editor = new Editor();
    GameObjectsTreeWidget* game_obj_tree = new GameObjectsTreeWidget(m_editor);
    m_layout->addWidget(game_obj_tree);

}
