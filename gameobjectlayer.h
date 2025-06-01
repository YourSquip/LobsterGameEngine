#ifndef GAMEOBJECTLAYER_H
#define GAMEOBJECTLAYER_H


#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>

#include "level.h"
#include "editor.h"
#include "Components.h"

class GameObjectItem: public QGraphicsPixmapItem
{
public:
    GameObjectItem(GameObject* game_object, QGraphicsItem* parent = nullptr):QGraphicsPixmapItem(parent)
    {
        m_game_object = game_object;
        if(COMPONENTS.sprites.count(game_object->get_id()) != 0)
        {
            this->setPixmap(COMPONENTS.sprites[game_object->get_id()].pixmap);
        }
        else
        {
            QPixmap pixmap("D:/QtProjects/LobsterGameEngine/sprites/icons/object.png");
            this->setPixmap(pixmap);
        }
        if(COMPONENTS.positions.count(game_object->get_id()) != 0)
        {
            this->setOffset(COMPONENTS.positions[game_object->get_id()].x,COMPONENTS.positions[game_object->get_id()].y);
        }
        else
        {
            this->setOffset(0,0);
        }
    }
private:
    GameObject* m_game_object;
};

class GameObjectLayer: public QGraphicsItemGroup
{
public:
    GameObjectLayer(Level* level,QGraphicsItem* parent = nullptr):QGraphicsItemGroup(parent)
    {
        m_level = level;
        m_game_objects = m_level->get_all_game_objects();
        for(auto game_object: m_game_objects)
        {
            this->addToGroup(new GameObjectItem(game_object));
        }
    }
private:
    QVector<GameObject*> m_game_objects;
    Level* m_level;
};

#endif // GAMEOBJECTLAYER_H
