#ifndef DLA_H
#define DLA_H

#include <stdlib.h>
#include <iostream>
#include <random>
#include <vector>


struct mountain_point
{
    int x_coord;
    int y_coord;
    float height = 0.0f;
    bool is_endpoint;
    bool exists = false;
    mountain_point* parent_point;
};

mountain_point* GenerateBrownianTree(int size, float fill_amount);

#endif