#ifndef EDITORTOOLSWIDGET_H
#define EDITORTOOLSWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>

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
        m_paint_brush_tool_bttn = new QPushButton("Paint brush", this);
        m_eraser_tool_bttn = new QPushButton("Eraser", this);
        m_layout = new QVBoxLayout(this);

        m_layout->addWidget(m_paint_brush_tool_bttn);
        m_layout->addWidget(m_eraser_tool_bttn);
        m_layout->addWidget(m_show_grid_check_box);
        connect(m_show_grid_check_box,&QCheckBox::stateChanged, m_level_view,m_level_view->show_grid);
        //connect(m_paint_brush_tool_bttn, );
        connect(m_paint_brush_tool_bttn,m_paint_brush_tool_bttn->clicked, this, take_paint_brush);
        connect(m_eraser_tool_bttn,m_eraser_tool_bttn->clicked, this, take_eraser);
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
signals:

private:
    LevelGraphicsView* m_level_view;
    QCheckBox* m_show_grid_check_box;
    QPushButton* m_paint_brush_tool_bttn;
    QPushButton* m_eraser_tool_bttn;
    QVBoxLayout* m_layout;

};

#endif // EDITORTOOLSWIDGET_H
