#ifndef GAMEOBJECTSTREEWIDGET_H
#define GAMEOBJECTSTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

#include "level.h"

class GameObjectTreeItem: public QTreeWidgetItem
{
public:
    GameObject* m_game_object;
    virtual ~GameObjectTreeItem(){};
};


class GameObjectsTreeWidget: public QWidget
{
    Q_OBJECT
public:
    GameObjectsTreeWidget(QWidget* parent = nullptr):QWidget(parent)
    {

    }
    void init_tree(const Level* level)
    {
        m_tree_widget = new QTreeWidget(this);
        QObject::connect(m_tree_widget, &QTreeWidget::itemSelectionChanged, this, &GameObjectsTreeWidget::select_tree_item);

        m_tree_widget->resize(600, 400);
        m_tree_widget->setHeaderHidden(true);

        m_layout = new QVBoxLayout(this);
        m_layout->addWidget(m_tree_widget);


        m_level = level;
        for(int i =0; i < m_level->m_game_objects.size();i++)
        {
            GameObjectTreeItem* item = new GameObjetTreeItem();
            item->setText(0,);
            //m_tree_widget->insertTopLevelItem(0,Game);
        }
    }

    void select_tree_item()
    {
        if (!m_tree_widget->selectedItems().empty())
        {
            /*UsdPrimTreeItem* item = static_cast<UsdPrimTreeItem*>(get_tree_widget()->selectedItems().first());

            if (item != nullptr && item->m_path != SdfPath::EmptyPath())
            {
                SdfPath prim_path = item->m_path;

                if (find_prim_by_path(prim_path).IsValid())
                {
                    emit item_selected(find_prim_by_path(prim_path));
                    std::cout << "\nitem_selected" << std::endl;
                }
            }*/
        }
    }

    GameObject* get_selected_game_object()
    {
        return get_tree_widget()->selectedItems().front();
    }
private:

    Level* m_level;
    QTreeWidget* m_tree_widget;
    QVBoxLayout* m_layout;
};

#endif // GAMEOBJECTSTREEWIDGET_H
