#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>
#include <QCheckBox>

#include "centralview.h"

class Viewport : public QWidget
{
    //ui
    //режимы едитора переключалки
    //сцено переключалки
    //чекбокс решётки
    Q_OBJECT
public:
    explicit Viewport(QWidget *parent = nullptr)
    {
        this->setStyleSheet("background-color:grey;");

    }
private:

signals:
};

#endif // VIEWPORT_H
