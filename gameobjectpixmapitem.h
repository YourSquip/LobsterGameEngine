#ifndef GAMEOBJECTPIXMAPITEM_H
#define GAMEOBJECTPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>

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
        //m_sprite = new SpriteComponentInfoWidget(all_components["sprite"]);
        //pixmap = sprite->get_pixmap().scaled(32,32);
        this->setPixmap(sprite->get_pixmap().scaled(32,32));
        this->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->setFlag(QGraphicsItem::ItemIsMovable,true);
        this->setFlag(QGraphicsItem::ItemIsFocusable,true);
        this->setAcceptDrops(true);
        //connect(m_sprite,m_sprite->pixmap_was_changed, this, this->update_pixmap);
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        update_pixmap();
        if(Editor::get_instance()->get_editor_tool_type() == Coursor || Editor::get_instance()->get_editor_tool_type() == MoveXY  )
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
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override
    {
        //auto pos_component = dynamic_cast<Position*>(m_game_object->get_all_components()["position"]);
        m_game_object->get_all_components()["position"] = new Position(this->pos().x(),this->pos().y());
        QGraphicsPixmapItem::mouseReleaseEvent(event);
    }

    ~GameObjectPixmapItem()
    {
        delete m_game_object;
    }

    void update_pixmap()
    {
        //GameObject* selected_obj = Editor::get_instance()->get_selected_game_obj();
        auto sprite_component = dynamic_cast<Sprite*>(m_game_object->get_all_components()["sprite"]);
        auto pos_component = dynamic_cast<Position*>(m_game_object->get_all_components()["position"]);
        m_pixmap = sprite_component->get_pixmap().scaled(32,32);
        m_game_object->get_all_components()["position"] = new Position(this->pos().x(),this->pos().y());
        //this->setPos(pos_component->x(),pos_component->y());
        this->setPixmap(m_pixmap);
    }

private:
    GameObject* m_game_object;
    //SpriteComponentInfoWidget* m_sprite;
    QPixmap m_pixmap;
};

#endif // GAMEOBJECTPIXMAPITEM_H
