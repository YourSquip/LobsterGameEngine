#ifndef EDITORTOOLSWIDGET_H
#define EDITORTOOLSWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "levelgraphicsview.h"
#include "editor.h"

class EditorToolsWidget : public QWidget
{
    Q_OBJECT
public:
    EditorToolsWidget(LevelGraphicsView* level_view,QWidget *parent = nullptr)
    {
        m_level_view = level_view;
        m_show_grid_check_box = new QCheckBox("show grid",this);
        m_show_grid_check_box->setChecked(false);

        m_paint_brush_tool_bttn = new QPushButton(this);
        QPixmap pixmap("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/paint_brush.png");
        m_paint_brush_tool_bttn->setIcon(QIcon(pixmap));
        m_paint_brush_tool_bttn->setIconSize(QSize(32,32));
        m_paint_brush_tool_bttn->resize(32,32);

        m_eraser_tool_bttn = new QPushButton(this);
        m_eraser_tool_bttn->resize(32,32);
        m_eraser_tool_bttn->setIcon(QIcon("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/eraser.png"));
        m_eraser_tool_bttn->setIconSize(QSize(32,32));

        m_coursor_tool_bttn = new QPushButton(this);
        m_coursor_tool_bttn->resize(32,32);
        m_coursor_tool_bttn->setIcon(QIcon("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/coursor.png"));
        m_coursor_tool_bttn->setIconSize(QSize(32,32));

        m_move_tool_bttn = new QPushButton(this);
        m_move_tool_bttn->resize(32,32);
        m_move_tool_bttn->setIcon(QIcon("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/transform.png"));
        m_move_tool_bttn->setIconSize(QSize(32,32));

        m_layout = new QHBoxLayout(this);

        m_layout->addWidget(m_show_grid_check_box);
        m_layout->addWidget(m_paint_brush_tool_bttn);
        m_layout->addWidget(m_eraser_tool_bttn);
        m_layout->addWidget(m_coursor_tool_bttn);
        m_layout->addWidget(m_move_tool_bttn);

        connect(m_show_grid_check_box,&QCheckBox::stateChanged, m_level_view,m_level_view->show_grid);
        //connect(m_paint_brush_tool_bttn, );
        connect(m_paint_brush_tool_bttn,m_paint_brush_tool_bttn->clicked, this, take_paint_brush);
        connect(m_eraser_tool_bttn,m_eraser_tool_bttn->clicked, this, take_eraser);
        connect(m_coursor_tool_bttn,m_coursor_tool_bttn->clicked, this, take_coursor);
        connect(m_move_tool_bttn,m_move_tool_bttn->clicked, this, take_move_tool);
    }

public slots:
    void take_paint_brush()
    {
        Editor::get_instance()->change_editor_tool_type(PaintBrush);
    }
    void take_eraser()
    {
        Editor::get_instance()->change_editor_tool_type(Eraser);
    }
    void take_coursor()
    {
        Editor::get_instance()->change_editor_tool_type(Coursor);
    }
    void take_move_tool()
    {
        Editor::get_instance()->change_editor_tool_type(MoveObjectXY);
    }
signals:

private:
    LevelGraphicsView* m_level_view;
    QCheckBox* m_show_grid_check_box;
    QPushButton* m_paint_brush_tool_bttn;
    QPushButton* m_eraser_tool_bttn;
    QPushButton* m_coursor_tool_bttn;
    QPushButton* m_move_tool_bttn;
    QHBoxLayout* m_layout;

};

#endif // EDITORTOOLSWIDGET_H
