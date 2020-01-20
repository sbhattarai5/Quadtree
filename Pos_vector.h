//File: Pos_vector.h
//Name: Saurav Bhattarai
#ifndef POS_VECTOR_H
#define POS_VECTOR_H

//It's a vector to record all the positions and all the rate of changes of those positions
class Pos_vector
{
public:
    //Set x, y to random using the surface
    Pos_vector(int x=0, int y=0)
    : _x_pos(x), _y_pos(y)
    {}
    int x() const { return _x_pos; }
    int y() const { return _y_pos; }
    int & x() { return _x_pos; }
    int & y() { return _y_pos; }

private:
    int _x_pos;
    int _y_pos;
};

#endif

