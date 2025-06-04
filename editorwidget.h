#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>

#include "editor.h"

class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditorWidget(QWidget *parent = nullptr);

signals:
};

#endif // EDITORWIDGET_H
