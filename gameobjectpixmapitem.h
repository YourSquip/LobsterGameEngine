#ifndef GAMEOBJECTPIXMAPITEM_H
#define GAMEOBJECTPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>

#include "gameobject.h"
#include "componentinfowidget.h"

class GameObjectPixmapItem: public QGraphicsPixmapItem
{
public:
    GameObjectPixmapItem(GameObject* game_object):QGraphicsPixmapItem()
    {
        m_game_object = game_object;
        QMap<QString,Component*> all_components = game_object->get_all_components();
        Sprite* sprite = dynamic_cast<Sprite*>(all_components["sprite"]);
        //m_sprite = new SpriteComponentInfoWidget(all_components["sprite"]);
        //m_pixmap = sprite->get_pixmap().scaled(32,32);
       // this->setPixmap(m_pixmap);
        //connect(m_sprite,m_sprite->pixmap_was_changed, this, this->update_pixmap);
    }

    ~GameObjectPixmapItem()
    {
        delete m_game_object;
    }
public slots:
    void update_pixmap()
    {
        //m_pixmap = m_sprite->get_sprite()->get_pixmap().scaled(32,32);
        //this->setPixmap(m_pixmap);
    }

private:
    GameObject* m_game_object;
    //SpriteComponentInfoWidget* m_sprite;
    QPixmap m_pixmap;
};

#endif // GAMEOBJECTPIXMAPITEM_H
