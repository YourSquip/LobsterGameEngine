#include "maptilefactory.h"

//MapTileFactory::MapTileFactory() {}

QVector<QString> MapTileFactory::names_of_tiles;
QHash<QString, CreateTileFunc> MapTileFactory::registered_tiles;
