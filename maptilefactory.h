#ifndef MAPTILEFACTORY_H
#define MAPTILEFACTORY_H

#include <QVector>
#include "maptile.h"

typedef MapTile* (*CreateTileFunc)();

class MapTileFactory
{
public:
    static MapTileFactory& get_instance()
    {
        static MapTileFactory instance = MapTileFactory();
        return instance;

    }

    static void register_tile(QString p_tile_name, CreateTileFunc p_create_func)
    {
        if(!registered_tiles.contains(p_tile_name))
        {
            registered_tiles.emplace(p_tile_name,p_create_func);
            names_of_tiles.push_back(p_tile_name);
        }
    }

    MapTile* create_spec_tile(QString p_tile_name)
    {
        if(registered_tiles.contains(p_tile_name))
        {
            CreateTileFunc func = registered_tiles.find(p_tile_name).value();
            return func();
        }
        else
        {
            qDebug()<< "There's no such tile";
        }
        return nullptr;
    }

    static QVector<QString> get_all_tiles_names()
    {
        return names_of_tiles;
    }
private:

    MapTileFactory(){}
    ~MapTileFactory(){}
    static QHash<QString, CreateTileFunc> registered_tiles;
    static QVector<QString> names_of_tiles;

    MapTileFactory(MapTileFactory const&) = delete;
    MapTileFactory& operator= (MapTileFactory const&) = delete;
};

#endif // MAPTILEFACTORY_H
