#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include "editor.h"
#include "gameobjectstreewidget.h"

class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    EditorWidget(QWidget *parent = nullptr);
    Editor* get_editor()
    {
        return m_editor;
    }
signals:

private:
    Editor* m_editor;
    QHBoxLayout* m_layout;
};

#endif // EDITORWIDGET_H
