//Name: Saurav Bhattarai
//File: Node.h

#ifndef NODE_H
#define NODE_H
#include "Constants.h"
#include "Game_object.h"
#include <iostream>
#include <vector>

int MAX_DEPTH = 4;
int MAX_OBJS_BEFORE_DIVISION = 8;

class Node
{
public:
    Node (int depth=0, Node * parent=NULL, int x_min=0, int x_max=W,
          int y_min=50, int y_max=H)
        : _depth(depth), _parent(parent), _x_min(x_min), _x_max(x_max), _y_min(y_min), _y_max(y_max)
    {}

public:
    int depth () const { return _depth; }
    void divide()
    {
        int half_x = (_x_min + _x_max) / 2;
        int half_y = (_y_min + _y_max) / 2;  //check the math //off by 1 error
        Node * child1 = new Node(_depth + 1, this, _x_min, half_x, _y_min, half_y);
        Node * child2 = new Node(_depth + 1, this, _x_min, half_x, half_y, _y_max);
        Node * child3 = new Node(_depth + 1, this, half_x, _x_max, _y_min, half_y);
        Node * child4 = new Node(_depth + 1, this, half_x, _x_max, half_y, _y_max);
        _children.push_back(child1);
        _children.push_back(child2);
        _children.push_back(child3);
        _children.push_back(child4);
        return;
    }
    int height() const
    {
        if (_children.size() == 0) return 0;
        int max_height = -1;
        for (int i = 0; i < _children.size(); ++i)
        {
            int height = _children[i]->height();
            if (height > max_height) max_height = height;
        }
        return max_height + 1;
    }
    void clear()
    {
        for (int i = 0; i < _children.size(); ++i)
        {
            _children[i]->clear();
            delete _children[i];
        }
        return;
    }
    void draw_lines()
    {
        Game_object::_surface->put_line(_x_min, _y_min, _x_max - 1, _y_min, 255, 255, 255);
        Game_object::_surface->put_line(_x_min, _y_min, _x_min, _y_max - 1, 255, 255, 255);
        Game_object::_surface->put_line(_x_min,_y_max - 1, _x_max - 1, _y_max - 1, 255, 255, 255);
        Game_object::_surface->put_line(_x_max - 1, _y_max - 1, _x_max - 1, _y_min, 255, 255, 255);
        for (int i = 0; i < _children.size(); ++i)
        {
            _children[i]->draw_lines();
        }
        return;
    }
    void add_to_children(Game_object * gobj)
    {
        Pos_vector pos = gobj->position();
        bool added = false;
        for (int i = 0; i < _children.size(); ++i)
        {
            if (pos.x() - Game_object::_radius > _children[i]->_x_min && pos.x() + Game_object::_radius < _children[i]->_x_max && pos.y() - Game_object::_radius > _children[i]->_y_min && pos.y() + Game_object::_radius < _children[i]->_y_max)
            {
                _children[i]->add(gobj);
                added = true;
                break;
            }
        }
        if (!added) g_objs_on_line.push_back(gobj);
        return;
    }
    void add(Game_object * gobj)
    {
        if (_children.size() == 0)
        {
            if(g_objs.size() >= MAX_OBJS_BEFORE_DIVISION && _depth != MAX_DEPTH)
            {
                divide();
                g_objs.push_back(gobj);
                
                for (int i = 0; i < g_objs.size(); ++i)
                {
                    add_to_children(g_objs[i]);
                }
                g_objs.resize(0);
            }
            else
            {
                g_objs.push_back(gobj);
            }
        }
        else
        {
            add_to_children(gobj);
        }
    }

    friend std::ostream & operator<<(std::ostream & cout, const Node & node)
    {
        cout << "<Node " << &node << " parent: " << node._parent
             << " depth: " << node.depth() << " gobjs.size(): " << node.g_objs.size() << '\n';
        for (int i = 0; i < node._children.size(); ++i)
        {
            std::cout << *(node._children[i]);
        }
        return cout;
    }

    bool is_leaf() const { return _children.size() == 0; }
    std::vector< Node * > & get_childrens() { return _children; }
    std::vector< Game_object *> & get_objs() { return g_objs; }
    static std::vector< Game_object * > g_objs_on_line; //all the objects that are on the line
private:
    int _depth;
    Node * _parent;
    std::vector< Game_object * > g_objs; //has game objects
    std::vector< Node *> _children;  //has atmost 4 childrens
    int _x_min;
    int _x_max;
    int _y_min;
    int _y_max;
};

std::vector< Game_object * > Node::g_objs_on_line;
#endif


