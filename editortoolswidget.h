#ifndef EDITORTOOLSWIDGET_H
#define EDITORTOOLSWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>

#include "levelgraphicsview.h"

class EditorToolsWidget : public QWidget
{
    Q_OBJECT
public:
    EditorToolsWidget(LevelGraphicsView* level_view,QWidget *parent = nullptr)
    {
        m_level_view = level_view;
        m_show_grid_check_box = new QCheckBox("show grid",this);
        m_show_grid_check_box->setChecked(false);
        m_layout = new QVBoxLayout(this);
        m_layout->addWidget(m_show_grid_check_box);
        connect(m_show_grid_check_box,&QCheckBox::stateChanged, m_level_view,m_level_view->show_grid);
    }
signals:

private:
    LevelGraphicsView* m_level_view;
    QCheckBox* m_show_grid_check_box;
    QVBoxLayout* m_layout;
};

#endif // EDITORTOOLSWIDGET_H
