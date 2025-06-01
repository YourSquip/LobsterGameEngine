#ifndef GAMEOBJECTLAYER_H
#define GAMEOBJECTLAYER_H

#include <QWidget>
#include <QApplication>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QDrag>
#include <QByteArray>
#include <QDataStream>
#include <QMouseEvent>
#include <QMimeData>
#include <QPoint>
#include <QPointF>
#include <QObject>
#include "level.h"
#include "editor.h"
#include "Components.h"

class GameObjectItem: public QGraphicsPixmapItem
{
public:
    GameObjectItem(GameObject* game_object, QGraphicsItem* parent = nullptr):QGraphicsPixmapItem(parent)
    {

        m_game_object = game_object;
        qDebug()<<"game object item:"<<m_game_object->get_name()<<m_game_object->get_id();

        //COMPONENTS.positions[m_game_object->get_id()] = Position{0.0f,0.0f};
        //QPixmap pixmap("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/icons/object.png");
        //pixmap.scaled(32,32);
        //this->setPixmap(pixmap.scaled(32,32));
        //this->setOffset(5,5);
        //this->resi

        /*for( auto comp: COMPONENTS.positions)
        {
            qDebug()<<"first:"<<comp.first;
            //qDebug()<<"second:"<comp.second->;
        }*/
        //this->setPixmap(COMPONENTS.sprites[game_object->get_id()].pixmap);
        if(COMPONENTS.positions.empty())
        {
            qDebug()<<"components are EMPTY in gameobjectitem";
        }
        else
        {
            QPixmap pixmap("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/icons/object.png");
            this->setPixmap(pixmap.scaled(32,32));
        }
        if(COMPONENTS.positions.count(game_object->get_id()) != 0)
        {
            this->setOffset(COMPONENTS.positions[game_object->get_id()].x,COMPONENTS.positions[game_object->get_id()].y);
        }
        else
        {
            this->setOffset(5,5);
        }

        this->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->setFlag(QGraphicsItem::ItemIsMovable,true);
        this->setAcceptDrops(true);
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_dragStartPosition = event->scenePos();
        }
        QGraphicsPixmapItem::mousePressEvent(event);
    }

   void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        if ((event->buttons() & Qt::LeftButton) &&
            (QLineF(event->scenePos(), m_dragStartPosition).length() > QApplication::startDragDistance())) {
            QDrag *drag = new QDrag(event->widget());
            QMimeData *mime = new QMimeData;

            drag->setMimeData(mime);
            drag->setPixmap(pixmap());
            drag->exec(Qt::MoveAction);
        }
        QGraphicsPixmapItem::mouseMoveEvent(event);
    }

private:
    QPointF m_dragStartPosition;
    GameObject* m_game_object;
};

class GameObjectLayer: public QGraphicsItemGroup
{
public:
    GameObjectLayer(Level* level,QGraphicsItem* parent = nullptr):QGraphicsItemGroup(parent)
    {
        this->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->setFlag(QGraphicsItem::ItemIsMovable,true);
        this->setAcceptDrops(true);

        m_level = level;

        m_game_objects = m_level->get_all_game_objects();
        for(auto game_object: m_game_objects)
        {
            add_game_object_to_layer(game_object);
        }
    }

    void add_game_object_to_layer(GameObject* game_object)
    {
        game_object->update_components();
        this->addToGroup(new GameObjectItem(game_object));
    }

private:
    QVector<GameObject*> m_game_objects;
    Level* m_level;
};

class GameObjectsLayerWidgetWrap:public QWidget
{
public:
    GameObjectsLayerWidgetWrap(GameObjectLayer* layer)
    {
        m_layer = layer;
    }
    GameObjectLayer* m_layer;
public slots:
    void add_new_object_from_level(GameObject* game_object)
    {
        m_layer->add_game_object_to_layer(game_object);
        m_layer->scene()->update();
    }
};

#endif // GAMEOBJECTLAYER_H
