#include "maptile.h"

//MapTile::MapTile() {}
//MapTileGraphicsFactory* MapTileGraphicsFactory::instance = nullptr;
QMap<QString,MapTileGraphics*> MapTileGraphicsFactory::m_registered_graphics;
