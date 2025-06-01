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
#include <QElapsedTimer>

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
            if(m_game_object->get_name().contains("player"))
            {
                QPixmap pixmap("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/player.png");
                this->setPixmap(pixmap.scaled(32,32));
            }
            else if(m_game_object->get_name().contains("chest"))
            {
                QPixmap pixmap("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/chest.png");
                this->setPixmap(pixmap.scaled(32,32));
            }
            else if(m_game_object->get_name().contains("tree"))
            {
                QPixmap pixmap("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/tree_apples.png");
                this->setPixmap(pixmap.scaled(64,64));
            }
            else
            {
                QPixmap pixmap("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/icons/object.png");
                this->setPixmap(pixmap.scaled(32,32));
            }

            //this->setPixmap(pixmap.scaled(32,32));
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
        this->setFlag(QGraphicsItem::ItemIsFocusable,true);
        this->setAcceptDrops(true);
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if(Editor::get_instance()->get_editor_tool_type() == Coursor || Editor::get_instance()->get_editor_tool_type() == MoveObjectXY  )
        {
            this->setFlag(QGraphicsItem::ItemIsSelectable,true);
            this->setFlag(QGraphicsItem::ItemIsMovable,true);
            this->setAcceptDrops(true);
            QGraphicsPixmapItem::mousePressEvent(event);
        }
        else
        {
            this->setFlag(QGraphicsItem::ItemIsSelectable,false);
            this->setFlag(QGraphicsItem::ItemIsMovable,false);
            //this->setFlag(QGraphicsItem::Item);
            this->setAcceptDrops(false);
        }
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        if(m_game_object->get_name().contains("player"))
        {
            //QElapsedTimer timer;
            //timer.start();
            //timer.
            qreal x = this->pos().x();
            qreal y = this->pos().y();
            if(event->key() == Qt::Key_W)
            {
                this->setPos(x, y - COMPONENTS.velocities[m_game_object->get_id()].y);
                //Do something when 'R' key is pressed
            }
            if(event->key() == Qt::Key_A)
            {
                this->setPos(x - COMPONENTS.velocities[m_game_object->get_id()].x, y);
                //Do something when 'R' key is pressed
            }
            if(event->key() == Qt::Key_S)
            {
                 this->setPos(x, y + COMPONENTS.velocities[m_game_object->get_id()].y);
                //Do something when 'R' key is pressed
            }
            if(event->key() == Qt::Key_D)
            {
                this->setPos(x + COMPONENTS.velocities[m_game_object->get_id()].x, y);
                //Do something when 'R' key is pressed
            }
            QGraphicsItem::keyPressEvent(event);

        }


    }

private:
    QPointF m_dragStartPosition;
    GameObject* m_game_object;
};

class GameObjectLayer: public QGraphicsItemGroup
{

};

class GameObjectsLayerWidget:public QWidget
{
public:

    GameObjectsLayerWidget(Level* level):QWidget()
    {
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
        m_game_object_items.push_back(new GameObjectItem(game_object));
    }

    QGraphicsScene* add_objects_to_scene(QGraphicsScene* scene)
    {
        for(auto item: m_game_object_items)
        {
            scene->addItem(item);
        }
        return scene;
    }
public slots:
    void add_new_object_from_level(GameObject* game_object)
    {
        add_game_object_to_layer(game_object);
    }

private:
    QVector<GameObjectItem*> m_game_object_items;
    QVector<GameObject*> m_game_objects;
    Level* m_level;
};

#endif // GAMEOBJECTLAYER_H
