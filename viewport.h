#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>

#include "levelgraphicsscene.h"
#include "editor.h"
#include "level.h"

class Viewport: public QGraphicsView
{
public:
    Viewport(QWidget* parent = nullptr):QGraphicsView(parent)
    {
        m_curr_scene = new LevelGraphicsScene();
        this->setScene(m_curr_scene);
        this->show();

        qDebug()<<"Viewport constructor";
    }
private:
    LevelGraphicsScene* m_curr_scene;
};

#endif // VIEWPORT_H
