#ifndef GAMEOBJECTPIXMAPITEM_H
#define GAMEOBJECTPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <QKeyEvent>

#include "gameobject.h"
#include "componentinfowidget.h"
#include "editor.h"


class GameObjectPixmapItem: public QGraphicsPixmapItem
{

public:
    GameObjectPixmapItem(GameObject* game_object):QGraphicsPixmapItem()
    {
        m_game_object = game_object;
        QMap<QString,Component*> all_components = m_game_object->get_all_components();
        Sprite* sprite = dynamic_cast<Sprite*>(all_components["sprite"]);
        this->setPixmap(sprite->get_pixmap().scaled(32,32));
        this->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->setFlag(QGraphicsItem::ItemIsMovable,true);
        this->setFlag(QGraphicsItem::ItemIsFocusable,true);
        this->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
        this->setAcceptDrops(true);
        m_current_in_scene = false;
    }

    bool get_current_in_scene()
    {
        if(this->get_game_object()->get_states()->m_controlable)
        {
            return true;
        }
        return false;
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {


        qDebug()<<"GameObjectPixmapItem:x_position_has_changed";
        qDebug()<<"GameObjectPixmapItem:y_position_has_changed";
        update_pixmap();
        if(Editor::get_instance()->get_editor_tool_type() == Coursor || Editor::get_instance()->get_editor_tool_type() == MoveXY  )
        {
            this->setFlag(QGraphicsItem::ItemIsSelectable,true);
            this->setFlag(QGraphicsItem::ItemIsMovable,true);
            this->setAcceptDrops(true);
            QGraphicsPixmapItem::mousePressEvent(event);
            //m_current_in_scene = true;
        }
        else
        {
            this->setFlag(QGraphicsItem::ItemIsSelectable,false);
            this->setFlag(QGraphicsItem::ItemIsMovable,false);
            this->setAcceptDrops(false);
        }

    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override
    {
        //update_pixmap();
        QGraphicsPixmapItem::mouseReleaseEvent(event);
    }

    ~GameObjectPixmapItem()
    {
        delete m_game_object;
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        this->setFlag(QGraphicsItem::ItemIsMovable,true);
        this->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->setAcceptDrops(true);
        QGraphicsItem::keyPressEvent(event);
    }

    GameObject* get_game_object()
    {
        return m_game_object;
    }

    void update_pixmap()
    {
        auto sprite_component = dynamic_cast<Sprite*>(m_game_object->get_all_components()["sprite"]);
        m_pixmap = sprite_component->get_pixmap().scaled(32,32);
        this->setPixmap(m_pixmap);
    }


private:
    GameObject* m_game_object;
    QPixmap m_pixmap;
    bool m_current_in_scene;
};



#endif // GAMEOBJECTPIXMAPITEM_H
