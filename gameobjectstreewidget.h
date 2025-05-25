#ifndef GAMEOBJECTSTREEWIDGET_H
#define GAMEOBJECTSTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <iostream>

#include "level.h"


class GameObjectTreeItem: public QTreeWidgetItem
{
public:
    GameObject* m_game_object;
    virtual ~GameObjectTreeItem(){}
};


class GameObjectsTreeWidget: public QWidget
{
    Q_OBJECT
public:
    GameObjectsTreeWidget( const Level* level , QWidget* parent = nullptr):QWidget(parent)
    {
        init_tree(level);
    }
    void init_tree(const Level* level)
    {
        m_tree_widget = new QTreeWidget(this);
        QObject::connect(m_tree_widget, &QTreeWidget::itemSelectionChanged, this, &GameObjectsTreeWidget::select_tree_item);

        m_tree_widget->resize(600, 400);
        m_tree_widget->setHeaderHidden(true);

        m_layout = new QVBoxLayout(this);
        m_layout->addWidget(m_tree_widget);
    }

    void create_game_object_tree_widget()
    {
        m_tree_widget->clear();
        for (auto game_object : m_level->get_all_game_objects())
        {
            if (game_object->get_parent() == nullptr)
            {
                GameObjectTreeItem* item = create_game_object_hierarchy(game_object);
                m_tree_widget->insertTopLevelItem(0, item);
            }
        }
    }

    QTreeWidget* get_tree_widget()
    {
        return m_tree_widget;
    }

    GameObject* get_selected_game_object()
    {
        GameObjectTreeItem* item = static_cast<GameObjectTreeItem*>(get_tree_widget()->selectedItems().front());
        return item->m_game_object;
    }

    GameObjectTreeItem* create_game_object_hierarchy(GameObject* game_object)
    {
        GameObjectTreeItem* item = new GameObjectTreeItem();
        item->setText(0, QString(game_object->get_name()));
        item->m_game_object = game_object;
        if (!game_object->get_all_children().empty())
        {
            for (auto child : game_object->get_all_children())
            {
                item->addChild(create_game_object_hierarchy(child));
            }
        }
        return item;
    }

signals:

    void item_selected(GameObject* game_object);

public slots:

    /*void build_tree_widget()
    {
        auto stage = open_usd_file();
        if (stage == nullptr)
            return;

        m_stage = stage;
        create_usd_tree_widget(stage);
    }*/

    void select_tree_item()
    {
        if (!get_tree_widget()->selectedItems().empty())
        {
            GameObjectTreeItem* item = static_cast<GameObjectTreeItem*>(get_tree_widget()->selectedItems().first());

            if (item != nullptr && item->m_game_object != nullptr)
            {
                GameObject* game_object = item->m_game_object;
                emit item_selected(game_object);
                std::cout << "\nitem_selected" << std::endl;
            }
        }
    }

private:

    Level* m_level;
    QTreeWidget* m_tree_widget;
    QVBoxLayout* m_layout;
};

#endif // GAMEOBJECTSTREEWIDGET_H
