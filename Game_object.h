//Name: Saurav Bhattarai
//File: Game_object.h

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "Pos_vector.h"
#include <cmath>

//The object that we're trying to manupulate the collisions on
//In our case, it is a ball, hence, we have properties like "color", "radius"
class Game_object
{
public:
    Game_object(int x, int y)
        : _position(Pos_vector(x, y)), _color({255, 0, 0})
    {
        _dx = rand() % 3 - 1;
        if (_dx != 0)
        {
            _dy = rand() % 3 - 1;
        }
        else
        {
            if (rand() % 2 == 0) _dy = -1;
            else _dy = 1;
        }
    }
    void move()
    {
        _position.x() += _dx;
        _position.y() += _dy;
        //If the ball collides in the end of the surface with the walls, we change the direction
        if (_position.x() - _radius < 0)
        {
            _dx = -_dx;
            _position.x () = _radius;
            
        }
        if (_position.x() + _radius > W - 1)
        {
            _dx = -_dx;
            _position.x() = W - 1 - _radius;
        }
        if (_position.y() - _radius < 50)
        {
            _dy = -_dy;
            _position.y() = 50 +_radius;
        }
        if (_position.y() + _radius > H - 1)
        {
            _dy = -_dy;
            _position.y() = H - 1 - _radius;
        }
        return;
    }

    friend void check_collision(Game_object * obj1, Game_object * obj2)
    {
        Pos_vector &  pos1 = obj1->_position;
        Pos_vector & pos2 = obj2->_position;
        double distance = pow(pos2.y() - pos1.y(), 2) + pow(pos2.x() - pos1.x(), 2);

        if (distance == 4 * Game_object::_radius * Game_object::_radius)
        {
            if (obj1->_dx + obj2->_dx == 0)
            {
                obj1->_dx *= -1;
                obj2->_dx *= -1;
            }
            if (obj1->_dy + obj2->_dy == 0)
            {
                obj1->_dy *= -1;
                obj2->_dy *= -1;
            }
            obj1->_color = {0, 0, 255};
            obj2->_color = {0, 0, 255};
        }
        if (distance < 4 * Game_object::_radius * Game_object::_radius)
        {
            if (obj1->_dx + obj2->_dx == 0)
            {
                obj1->_dx *= -1;
                obj2->_dx *= -1;
            }
            if (obj1->_dy + obj2->_dy == 0)
            {
                obj1->_dy *= -1;
                obj2->_dy *= -1;
            }
            obj1->move();
            obj2->move();
            obj1->_color = {0, 0, 255};
            obj2->_color = {0, 0, 255};
            
        }
        return;
        
    }
    Pos_vector const & position() const
    {
        return _position;
    }
    Pos_vector & position()
    {
        return _position;
    }
    static int radius() { return _radius; }
    static void inc_radius() { ++_radius; if (_radius > 15) _radius = 15; } //Increases the radius of the game Game_object
    static void dec_radius() { --_radius; if (_radius < 2) _radius = 2; } //Decreases the radius of the game Game_object
    void draw()
    {
        _surface->put_circle(_position.x(), _position.y(), _radius, _color);
        return;
    }
    static int _radius;   //We have a ball which also has a property called radius
    static Surface * _surface;

private:
    Pos_vector _position;
    int _dx;       //Rate of change of x-coordinate
    int _dy;       //Rate of change of y-coordinate
    Color _color; //Has a color as well in our case

};

int Game_object::_radius = 2;
Surface * Game_object::_surface = NULL;

#endif
