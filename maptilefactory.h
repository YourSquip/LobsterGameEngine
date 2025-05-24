#ifndef MAPTILEFACTORY_H
#define MAPTILEFACTORY_H

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

    void register_tile(QString p_tile_name, CreateTileFunc p_create_func)
    {
        if(!registered_tiles.contains(p_tile_name))
        {
            registered_tiles.emplace(p_tile_name,p_create_func);
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

private:

    MapTileFactory(){}
    ~MapTileFactory(){}
    QHash<QString, CreateTileFunc> registered_tiles;

    MapTileFactory(MapTileFactory const&) = delete;
    MapTileFactory& operator= (MapTileFactory const&) = delete;
};

#endif // MAPTILEFACTORY_H
