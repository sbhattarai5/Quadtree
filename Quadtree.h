//Name: Saurav Bhattarai
//File: Quadtree.h

#ifndef QUADTREE_H
#define QUADTREE_H
#include "Node.h"

class Quadtree
{
public:
    Quadtree()
    : _root(NULL), _height(-1)
    {}

    void add_new_object(Game_object * gobj)
    {
        add(gobj);
        all_the_objects.push_back(gobj);
    }
    void add(Game_object * gobj)
    {
        if (gobj == NULL) return;
        if (_root == NULL)
        {
            _root = new Node();
        }
        _root->add(gobj);
    }
    void move()
    {
        for (int i = 0; i < all_the_objects.size(); ++i)
        {
            all_the_objects[i]->move();
        }
    }
    void draw(bool show_quadrants)
    {
        draw_info();
        if (_root == NULL) return;
        for (int i = 0; i < all_the_objects.size(); ++i)
        {
            all_the_objects[i]->draw();
        }
        if (show_quadrants) draw_lines();
        return;
    }
    void draw_info()
    {
        Font font("fonts/FreeSans.ttf", 24);
        std::stringstream out1;
        out1 << "Quadtree info | ";
        out1 << "Number of objects: " << all_the_objects.size();
        out1 << " | Height: " << height(); 
        Image image1(font.render(out1.str().c_str(), WHITE));
        Rect rect1 = image1.getRect();
        Game_object::_surface->put_image(image1, rect1);
        Game_object::_surface->put_line(0, 50, W - 1, 50, 255, 255, 255);
        return;
    }
    void draw_lines()
    {
        _root->draw_lines();
    }
    void clear()
    {
        if (_root == NULL) return;
        leaf_nodes.resize(0);
        _root->clear();
        Node::g_objs_on_line.resize(0);
        delete _root;
        _root = NULL;
        return;
    }
    void reinitialize()
    {
        for (int i = 0; i < all_the_objects.size(); ++i)
        {
            add(all_the_objects[i]);
        }
        return;
    }

    void regular_collision_check()
    {
        if (all_the_objects.size() == 0) return;
        for (int i = 0; i < all_the_objects.size() - 1; ++i)
        {
            for (int j = i + 1; j < all_the_objects.size(); ++j)
            {
                check_collision(all_the_objects[i], all_the_objects[j]);
            }
        }
        return;
    }

    void update_leaf_nodes()
    {
        if (_root == NULL) return;
        std::vector< Node * > to_be_checked;
        to_be_checked.push_back(_root);
        while (!to_be_checked.empty())
        {
            Node * node = to_be_checked.back();
            to_be_checked.pop_back();
            if (node->is_leaf())
            {
                leaf_nodes.push_back(node);
            }
            else
            {
                std::vector< Node * > & childrens = node->get_childrens();
                for (int i = 0; i < childrens.size(); ++i)
                {
                    to_be_checked.push_back(childrens[i]);
                }
            }
        }
        //std::cout << "size-on-line: " << Node::g_objs_on_line.size() << std::endl;
        return;
    }
    void quadtree_collision_check()
    {
        leaf_nodes.resize(0);
        update_leaf_nodes();
        for (int i = 0; i < leaf_nodes.size(); ++i)
        {
            std::vector< Game_object *> & gobjs = leaf_nodes[i]->get_objs();
            if (gobjs.size() == 0) continue;
            for (int j = 0; j < gobjs.size() - 1; ++j)
            {
                for (int k = j + 1; k < gobjs.size(); ++k)
                {
                    check_collision(gobjs[j], gobjs[k]);
                }
            }
            for (int j = 0; j < gobjs.size(); ++j)
            {
                for (int k = 0; k < Node::g_objs_on_line.size(); ++k)
                {
                    check_collision(gobjs[j], Node::g_objs_on_line[k]);
                }
            }
        }
        if (Node::g_objs_on_line.size() != 0)
        {
            for (int i = 0; i < Node::g_objs_on_line.size() - 1; ++i)
            {
                for (int j =  i + 1; j < Node::g_objs_on_line.size(); ++j)
                {
                    check_collision(Node::g_objs_on_line[i], Node::g_objs_on_line[j]);
                }
            }
        }
        return;
    }
    friend std::ostream & operator<<(std::ostream & cout, const Quadtree & quadtree)
    {
        if (quadtree._root == NULL) cout << "NULL";
        else
        {
            return std::cout << *(quadtree._root);
        }
        return cout;
    }
    
    
    int height()
    {
        if (_root == NULL) return -1;
        _root->height();
    }
    ~Quadtree()
    {
        clear();
    }
private:
    Node * _root;
    std::vector< Game_object * > all_the_objects;
    int _height;
    std::vector< Node * > leaf_nodes;
};
#endif

