#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>

class Viewport: public QGraphicsView
{
public:
    Viewport(QWidget* parent = nullptr):QGraphicsView(parent)
    {

    }
private:
    QGraphicsScene* m_curr_scene;
};

#endif // VIEWPORT_H
