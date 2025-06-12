#ifndef GAMEOBJECTPIXMAPITEM_H
#define GAMEOBJECTPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <QKeyEvent>

#include "gameobject.h"
#include "componentinfowidget.h"
#include "editor.h"

class PixmapObjectUpdater:public QWidget
{
    Q_OBJECT
public:
    PixmapObjectUpdater()
    {

    }

signals:
    void x_position_has_changed(float x);
    void y_position_has_changed(float y);
};

class GameObjectPixmapItem: public QGraphicsPixmapItem
{

public:
    GameObjectPixmapItem(GameObject* game_object):QGraphicsPixmapItem()
    {
        m_game_object = game_object;
        QMap<QString,Component*> all_components = m_game_object->get_all_components();
        Sprite* sprite = dynamic_cast<Sprite*>(all_components["sprite"]);
        updater = new PixmapObjectUpdater();
        //m_game_object->get_all_components()
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


        emit updater->x_position_has_changed(this->pos().x());
        emit updater->y_position_has_changed(this->pos().y());
        qDebug()<<"GameObjectPixmapItem:x_position_has_changed";
        qDebug()<<"GameObjectPixmapItem:y_position_has_changed";
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
        //update_pixmap();
        //auto pos_component = dynamic_cast<Position*>(m_game_object->get_all_components()["position"]);
        //m_game_object->get_all_components()["position"] = new Position(this->pos().x(),this->pos().y());
        emit updater->x_position_has_changed(this->pos().x());
        emit updater->y_position_has_changed(this->pos().y());
        qDebug()<<"GameObjectPixmapItem:x_position_has_changed";
        qDebug()<<"GameObjectPixmapItem:y_position_has_changed";
        QGraphicsPixmapItem::mouseReleaseEvent(event);
    }

    ~GameObjectPixmapItem()
    {
        delete m_game_object;
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        //this->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->setFlag(QGraphicsItem::ItemIsMovable,true);
        this->setAcceptDrops(true);
        if(m_game_object->get_controlable())
        {
            qreal x = this->pos().x();
            qreal y = this->pos().y();
            //auto prev_time= Editor::get_instance()->get_game()->get_timer().elapsed();
            float velocity = 20;
            float new_x = x;
            float new_y = y;
            if(event->key() == Qt::Key_W)
            {
                new_x = x;
                new_y = y - velocity;
                this->setPos(new_x, new_x);
                emit updater->y_position_has_changed(new_y);
                qDebug()<<"GameObjectPixmapItem: y_position_has_changed";

            }
            if(event->key() == Qt::Key_A)
            {
                new_x = x - velocity;
                new_y = y;
                this->setPos(new_x, new_y);
                emit updater->x_position_has_changed(new_x);
                qDebug()<<"GameObjectPixmapItem:x_position_has_changed";
            }
            if(event->key() == Qt::Key_S)
            {
                new_x = x;
                new_y = y + velocity;
                this->setPos(new_x, new_y);
                emit updater->y_position_has_changed(new_y);
                qDebug()<<"GameObjectPixmapItem:y_position_has_changed";
            }
            if(event->key() == Qt::Key_D)
            {
                new_x = x + velocity;
                new_y = y;
                this->setPos(new_x, new_y);
                emit updater->x_position_has_changed(new_x);
                qDebug()<<"GameObjectPixmapItem:x_position_has_changed";
            }
            QGraphicsItem::keyPressEvent(event);

        }
    }

    void update_pixmap()
    {
        //GameObject* selected_obj = Editor::get_instance()->get_selected_game_obj();
        auto sprite_component = dynamic_cast<Sprite*>(m_game_object->get_all_components()["sprite"]);
        auto pos_component = dynamic_cast<Position*>(m_game_object->get_all_components()["position"]);
        m_pixmap = sprite_component->get_pixmap().scaled(32,32);
        //m_game_object->get_all_components()["position"] = new Position(this->pos().x(),this->pos().y());
        //qDebug()<<"this->pos().x(),this->pos().y()"<< this->pos().x()<<" "<<this->pos().y();
        //qDebug()<<"pos_component->x(),pos_component->y()"<< pos_component->x()<<" "<<pos_component->y();
        //this->setPos(pos_component->x(),pos_component->y());
        this->setPixmap(m_pixmap);
    }

    //void update
    PixmapObjectUpdater* get_updater()
    {
        return updater;
    }

    void set_updater(PixmapObjectUpdater* p_updater)
    {
        updater = p_updater;
    }

    void add_updater()
    {
        updater = new PixmapObjectUpdater();
    }
private:
    GameObject* m_game_object;
    //SpriteComponentInfoWidget* m_sprite;
    QPixmap m_pixmap;
    PixmapObjectUpdater* updater;
};



#endif // GAMEOBJECTPIXMAPITEM_H
