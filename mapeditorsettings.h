#ifndef MAPEDITORSETTINGS_H
#define MAPEDITORSETTINGS_H
#include <QPixmap>
#include <QString>

class MapEditorSettings
{
public:
    ~MapEditorSettings()
    {
        //delete m_game;
        // delete m_selected_game_obj;
    }

    static MapEditorSettings* get_instance()
    {
        if(instance) return  instance;
        instance = new MapEditorSettings();
        return instance;
    }
    QString get_paint_tile_pixmap_path()
    {
        return m_paint_tile_pixmap_path;
    }
    void set_paint_tile_pixmap_path(QString path)
    {
        m_paint_tile_pixmap_path = path;
    }


private:
    MapEditorSettings()
    {
        m_paint_tile_pixmap_path = ":/sprites/grass_tile.png";
    }
    static MapEditorSettings* instance;
    QString m_paint_tile_pixmap_path;

};

#endif // MAPEDITORSETTINGS_H
