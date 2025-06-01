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
        //QPixmap pixmap("D:/QtProjects/LobsterGameEngineCopy/LobsterGameEngine/sprites/icons/object.png");
        //pixmap.scaled(32,32);
        //this->setPixmap(pixmap.scaled(32,32));
        //this->setOffset(5,5);
        //this->resi
        if(COMPONENTS.sprites.count(game_object->get_id()) != 0)
        {
            this->setPixmap(COMPONENTS.sprites[game_object->get_id()].pixmap);
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
            qDebug()<<"game objects being added in gameobject layer";
        }
    }
private:
    QVector<GameObject*> m_game_objects;
    Level* m_level;
};

#endif // GAMEOBJECTLAYER_H
